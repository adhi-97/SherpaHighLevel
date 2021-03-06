//#include <mavros/RCIn.h>
#include <mavros/mavros_plugin.h>
#include <pluginlib/class_list_macros.h>

#include "mavros/OverrideRCIn.h"

#include <guidance_node/Directive.h>
#include "guidance_node/Position.h"

namespace mavplugin {
/**
 * @brief Mavros plugin
 */
class UniboControllerPlugin : public MavRosPlugin {
public:
	UniboControllerPlugin() :
		nodeHandle(),
		uas(nullptr),
		safetyOn(true),
		v_xy_max(3.0),
		v_z_max(1.5),
		v_psi_max(3.14)
	{};

	void initialize(UAS &uas_)
	{
		uas = &uas_;

		directive_sub = nodeHandle.subscribe("/directive", 10, &UniboControllerPlugin::directive_cb, this);
		position_pub = nodeHandle.advertise<guidance_node::Position>("/position", 10);

		velocity_publisher_=nodeHandle.advertise<mavros::OverrideRCIn>("mavros/rc/override", 10);

		nodeHandle.param("guidance_node/param/sat_xy", v_xy_max, 3.0);
		nodeHandle.param("guidance_node/param/sat_z", v_z_max, 1.5);
		nodeHandle.param("guidance_node/param/sat_yaw", v_psi_max, 3.14);

		//DEBUG
//		ROS_INFO("INITIALIZE UNIBO PLUGIN");
	}

	//should be logic mapping between id number and message type
	const message_map get_rx_handlers() {
		return {
			MESSAGE_HANDLER(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, &UniboControllerPlugin::handle_global_position_int),
			MESSAGE_HANDLER(MAVLINK_MSG_ID_ATTITUDE, &UniboControllerPlugin::handle_attitude),
			MESSAGE_HANDLER(MAVLINK_MSG_ID_RC_CHANNELS_RAW, &UniboControllerPlugin::handle_rc_channels_raw)
		};
	}

private:
	ros::NodeHandle nodeHandle;
	UAS *uas;

	ros::Publisher position_pub;
	ros::Subscriber directive_sub;
	ros::Publisher velocity_publisher_;

	//message to move the quadcopter
	mavros::OverrideRCIn velocity_;

	//common message to join data from handles
	guidance_node::Position commonMessage;

	//safety flag
	bool safetyOn;

	//saturation parameters
	/*
	 * Questi tipi di dato sono matlab per specifiche ros del param server.
	 * Nel nodo "guidance_node" sono convertiti a float perchè la legge di guida matlab ha come input
	 * dei float. Adesso non sono convertiti perchè tanto possono essere usati così
	 */
	double v_xy_max, v_z_max, v_psi_max;

	//check if safety is on
	void handle_rc_channels_raw(const mavlink_message_t *msg, uint8_t sysid, uint8_t compid) {

		mavlink_rc_channels_raw_t channels_raw;
		mavlink_msg_rc_channels_raw_decode(msg,&channels_raw);

		/*
		 * If safety is on, chan5_raw must be less than 1200
		 */
		//DEBUG
		ROS_INFO("CHANNEL 6 IS: %u",channels_raw.chan6_raw);
		if(channels_raw.chan6_raw > 1800){
			safetyOn = false;
			commonMessage.Safety = 0;
		}
		else {
			safetyOn=true;
			commonMessage.Safety= 1;
		}

		//DEBUG
//		ROS_INFO("HANDLE RC RAW");

	}

	void handle_attitude(const mavlink_message_t *msg, uint8_t sysid, uint8_t compid) {

		mavlink_attitude_t attitude;
		mavlink_msg_attitude_decode(msg, &attitude);

		auto position_msg = boost::make_shared<guidance_node::Position>();

		//getting new data
		position_msg->Yawangle=attitude.yaw;

		//copying data from commonMessage
		position_msg->Timestamp=commonMessage.Timestamp;
		position_msg->AltitudeRelative=commonMessage.AltitudeRelative;
		position_msg->Latitude=commonMessage.Latitude;
		position_msg->Longitude=commonMessage.Longitude;
		position_msg->Safety = commonMessage.Safety;

		//saving data
		commonMessage.Yawangle=attitude.yaw;

		//DEBUG
//		ROS_INFO("%f", commonMessage.Yawangle);

		position_pub.publish(position_msg);
	}

	void handle_global_position_int(const mavlink_message_t *msg, uint8_t sysid, uint8_t compid) {

		mavlink_global_position_int_t global_position;
		mavlink_msg_global_position_int_decode(msg, &global_position);

		auto position_msg = boost::make_shared<guidance_node::Position>();

		//getting new data
		position_msg->Timestamp=global_position.time_boot_ms;
		position_msg->AltitudeRelative=global_position.relative_alt;
		position_msg->Latitude=global_position.lat;
		position_msg->Longitude=global_position.lon;

		//copying data from commonMessage
		position_msg->Yawangle=commonMessage.Yawangle;
		position_msg->Safety = commonMessage.Safety;

		//saving data
		commonMessage.Timestamp=global_position.time_boot_ms;
		commonMessage.AltitudeRelative=global_position.relative_alt;
		commonMessage.Latitude=global_position.lat;
		commonMessage.Longitude=global_position.lon;

		//DEBUG
//		ROS_INFO("HANDLE POSITION");


		position_pub.publish(position_msg);
	}

	/*
	 * From directive to RC
	 */
	void directive_cb(const guidance_node::Directive::ConstPtr msg){

		/*
		 * Initializing values, if safety is on, these values will remain
		 */
			velocity_.channels[0]=0;
			velocity_.channels[1]=0;
			velocity_.channels[2]=0;
			velocity_.channels[3]=0;
			velocity_.channels[4]=0;
			velocity_.channels[5]=0;
			velocity_.channels[6]=0;
			velocity_.channels[7]=0;

		if(!safetyOn){
			/*
			 * If safety is off, I translate velocity in RC values
			 */
			uint16_t vx_RC= (uint16_t)400.0f*(-msg->vxBody)/v_xy_max + 1520;
			uint16_t vy_RC=(uint16_t)400.0f*(msg->vyBody)/v_xy_max + 1520;
			/*
			 * it seems it loiters with 1420 instead of 1500...
			 */
			uint16_t vz_RC= 1420;
			if (msg->vzBody > 0){ //going down, mapped only in 420us
				vz_RC = vz_RC + (uint16_t)300.0f*(-msg->vzBody)/v_z_max;        //was 420
			} else {        //going up, mapped in 580us
				vz_RC = vz_RC + (uint16_t)500.0f*(-msg->vzBody)/v_z_max;     // was 580
			}
			uint16_t v_psi_RC = (uint16_t)400.0f*(msg->yawRate)/v_psi_max + 1520;

			velocity_.channels[0]=vy_RC;
			velocity_.channels[1]=vx_RC;
			velocity_.channels[2]=vz_RC;
			velocity_.channels[3]=v_psi_RC;


		}

		//DEBUG
		ROS_INFO("RC_OVERRIDE: [CH1:%u, CH2:%u, CH3:%u, CH4:%u, CH5:%u, CH6:%u, CH7:%u, CH8:%u]",
				velocity_.channels[0], velocity_.channels[1],
				velocity_.channels[2], velocity_.channels[3],
				velocity_.channels[4], velocity_.channels[5],
				velocity_.channels[6], velocity_.channels[7]);

		velocity_publisher_.publish(velocity_);

	}
};
};	// namespace mavplugin

PLUGINLIB_EXPORT_CLASS(mavplugin::UniboControllerPlugin, mavplugin::MavRosPlugin)
