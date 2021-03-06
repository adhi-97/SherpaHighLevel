/*
 * Model_GS.h
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.199
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C++ source code generated on : Wed Feb 03 10:38:35 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Model_GS_h_
#define RTW_HEADER_Model_GS_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Model_GS_COMMON_INCLUDES_
# define Model_GS_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Model_GS_COMMON_INCLUDES_ */

#include "Model_GS_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block signals for system '<Root>/Any2[-pi;pi]' */
typedef struct {
  real_T output;                       /* '<Root>/Any2[-pi;pi]' */
} B_Any2pipi_Model_GS_T;

/* Block signals for system '<Root>/Int32 to Double' */
typedef struct {
  real_T y[3];                         /* '<Root>/Int32 to Double' */
} B_Int32toDouble_Model_GS_T;

/* Block signals for system '<Root>/Scaling WGS' */
typedef struct {
  real_T WGS_scaled[3];                /* '<Root>/Scaling WGS' */
} B_ScalingWGS_Model_GS_T;

/* Block signals for system '<S22>/ ECEF to NED' */
typedef struct {
  real_T N;                            /* '<S22>/ ECEF to NED' */
  real_T E;                            /* '<S22>/ ECEF to NED' */
  real_T D;                            /* '<S22>/ ECEF to NED' */
} B_ECEFtoNED_Model_GS_T;

/* Block signals for system '<S22>/MATLAB Function WGS84 TO ECEF' */
typedef struct {
  real_T ECEF[3];                      /* '<S22>/MATLAB Function WGS84 TO ECEF' */
} B_MATLABFunctionWGS84TOECEF_M_T;

/* Block signals for system '<Root>/single to double1' */
typedef struct {
  real_T y;                            /* '<Root>/single to double1' */
} B_singletodouble1_Model_GS_T;

/* Block signals (auto storage) */
typedef struct {
  B_singletodouble1_Model_GS_T sf_uint16todouble2;/* '<Root>/uint16 to double2' */
  B_singletodouble1_Model_GS_T sf_uint16todouble1;/* '<Root>/uint16 to double1' */
  B_singletodouble1_Model_GS_T sf_singletodouble1;/* '<Root>/single to double1' */
  B_MATLABFunctionWGS84TOECEF_M_T sf_MATLABFunctionWGS84TOECEF_d;/* '<S14>/MATLAB Function WGS84 TO ECEF' */
  B_MATLABFunctionWGS84TOECEF_M_T sf_MATLABFunctionWGS84TOECEF;/* '<S26>/MATLAB Function WGS84 TO ECEF' */
  B_ECEFtoNED_Model_GS_T sf_ECEFtoNED; /* '<S26>/ ECEF to NED' */
  B_MATLABFunctionWGS84TOECEF_M_T sf_MATLABFunctionWGS84TOECEF_j;/* '<S13>/MATLAB Function WGS84 TO ECEF' */
  B_MATLABFunctionWGS84TOECEF_M_T sf_MATLABFunctionWGS84TOECEF_e;/* '<S22>/MATLAB Function WGS84 TO ECEF' */
  B_ECEFtoNED_Model_GS_T sf_ECEFtoNED_e;/* '<S22>/ ECEF to NED' */
  B_ScalingWGS_Model_GS_T sf_ScalingWGS1;/* '<Root>/Scaling WGS1' */
  B_ScalingWGS_Model_GS_T sf_ScalingWGS;/* '<Root>/Scaling WGS' */
  B_Int32toDouble_Model_GS_T sf_Int32toDouble6;/* '<Root>/Int32 to Double6' */
  B_Int32toDouble_Model_GS_T sf_Int32toDouble;/* '<Root>/Int32 to Double' */
  B_Any2pipi_Model_GS_T sf_Any2pipi1;  /* '<Root>/Any2[-pi;pi]1' */
  B_Any2pipi_Model_GS_T sf_Any2pipi;   /* '<Root>/Any2[-pi;pi]' */
} B_Model_GS_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput[3];      /* '<S7>/Memory' */
  real_T k;                            /* '<Root>/Edge detector' */
  real_T u_D_I;                        /* '<Root>/Control Law NED' */
} DW_Model_GS_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  int32_T Actual_Pos[3];               /* '<Root>/Actual_Pos ' */
  real32_T Actual_Yaw;                 /* '<Root>/Actual_Yaw' */
  boolean_T Trigger;                   /* '<Root>/Trigger' */
  int32_T Reference_Pos[3];            /* '<Root>/Reference_Pos ' */
  real32_T Reference_Speed[4];         /* '<Root>/Reference_Speed' */
  real32_T Reference_Yaw;              /* '<Root>/Reference_Yaw' */
  uint32_T Time;                       /* '<Root>/Time' */
  real32_T Control_Param[9];           /* '<Root>/Control_Param' */
  real32_T dt;                         /* '<Root>/dt' */
} ExtU_Model_GS_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T BodySpeedInput[4];          /* '<Root>/BodySpeedInput' */
} ExtY_Model_GS_T;

/* Parameters (auto storage) */
struct P_Model_GS_T_ {
  real_T Memory_X0[3];                 /* Expression: [0 0 0]
                                        * Referenced by: '<S7>/Memory'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Model_GS_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model Model_GS */
class Model_GSModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_Model_GS_T Model_GS_U;

  /* External outputs */
  ExtY_Model_GS_T Model_GS_Y;

  /* Model entry point functions */

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  Model_GSModelClass();

  /* Destructor */
  ~Model_GSModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Model_GS_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_Model_GS_T Model_GS_P;

  /* Block signals */
  B_Model_GS_T Model_GS_B;

  /* Block states */
  DW_Model_GS_T Model_GS_DW;

  /* Real-Time Model */
  RT_MODEL_Model_GS_T Model_GS_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model_GS'
 * '<S1>'   : 'Model_GS/Any2[-pi;pi]'
 * '<S2>'   : 'Model_GS/Any2[-pi;pi]1'
 * '<S3>'   : 'Model_GS/Body Saturation'
 * '<S4>'   : 'Model_GS/Control Law NED'
 * '<S5>'   : 'Model_GS/Double to Single'
 * '<S6>'   : 'Model_GS/Edge detector'
 * '<S7>'   : 'Model_GS/Home'
 * '<S8>'   : 'Model_GS/Int32 to Double'
 * '<S9>'   : 'Model_GS/Int32 to Double6'
 * '<S10>'  : 'Model_GS/NED2BODY'
 * '<S11>'  : 'Model_GS/Scaling WGS'
 * '<S12>'  : 'Model_GS/Scaling WGS1'
 * '<S13>'  : 'Model_GS/WGS2NED1'
 * '<S14>'  : 'Model_GS/WGS2NED2'
 * '<S15>'  : 'Model_GS/single to double1'
 * '<S16>'  : 'Model_GS/single to double2'
 * '<S17>'  : 'Model_GS/single to double7'
 * '<S18>'  : 'Model_GS/uint16 to double1'
 * '<S19>'  : 'Model_GS/uint16 to double2'
 * '<S20>'  : 'Model_GS/uint32 to double'
 * '<S21>'  : 'Model_GS/Home/trigger'
 * '<S22>'  : 'Model_GS/WGS2NED1/ECEF2NED'
 * '<S23>'  : 'Model_GS/WGS2NED1/MATLAB Function WGS84 TO ECEF'
 * '<S24>'  : 'Model_GS/WGS2NED1/ECEF2NED/ ECEF to NED'
 * '<S25>'  : 'Model_GS/WGS2NED1/ECEF2NED/MATLAB Function WGS84 TO ECEF'
 * '<S26>'  : 'Model_GS/WGS2NED2/ECEF2NED'
 * '<S27>'  : 'Model_GS/WGS2NED2/MATLAB Function WGS84 TO ECEF'
 * '<S28>'  : 'Model_GS/WGS2NED2/ECEF2NED/ ECEF to NED'
 * '<S29>'  : 'Model_GS/WGS2NED2/ECEF2NED/MATLAB Function WGS84 TO ECEF'
 */
#endif                                 /* RTW_HEADER_Model_GS_h_ */
