/*
 * Model_GS.cpp
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.184
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C++ source code generated on : Mon May 18 17:01:42 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "Model_GS.h"
#include "Model_GS_private.h"

/*
 * Output and update for atomic system:
 *    '<Root>/Int32 to Double'
 *    '<Root>/Int32 to Double6'
 */
void Model_GS_Int32toDouble(const int32_T rtu_u[3], B_Int32toDouble_Model_GS_T
  *localB)
{
  /* MATLAB Function 'Int32 to Double': '<S6>:1' */
  /* '<S6>:1:4' */
  localB->y[0] = rtu_u[0];
  localB->y[1] = rtu_u[1];
  localB->y[2] = rtu_u[2];
}

/*
 * Output and update for atomic system:
 *    '<Root>/Scaling WGS'
 *    '<Root>/Scaling WGS1'
 */
void Model_GS_ScalingWGS(const real_T rtu_WGS[3], B_ScalingWGS_Model_GS_T
  *localB)
{
  /* MATLAB Function 'Scaling WGS': '<S9>:1' */
  /* '<S9>:1:4' */
  /* to rad */
  /* '<S9>:1:5' */
  /* to rad */
  /* '<S9>:1:6' */
  /* mm to meters */
  /* '<S9>:1:8' */
  localB->WGS_scaled[0] = rtu_WGS[0] * 1.0E-7 * 3.1415926535897931 / 180.0;
  localB->WGS_scaled[1] = rtu_WGS[1] * 1.0E-7 * 3.1415926535897931 / 180.0;
  localB->WGS_scaled[2] = rtu_WGS[2] * 0.001;
}

/*
 * Output and update for atomic system:
 *    '<S20>/ ECEF to NED'
 *    '<S24>/ ECEF to NED'
 */
void Model_GS_ECEFtoNED(const real_T rtu_WGS_home[3], const real_T rtu_ECEF_in[3],
  const real_T rtu_ECEF_home[3], B_ECEFtoNED_Model_GS_T *localB)
{
  real_T dX;
  real_T dY;
  real_T dZ;

  /* MATLAB Function 'WGS2NED1/ECEF2NED/ ECEF to NED': '<S22>:1' */
  /* '<S22>:1:4' */
  /* lat */
  /* '<S22>:1:5' */
  /* lon */
  /* '<S22>:1:7' */
  dX = rtu_ECEF_in[0] - rtu_ECEF_home[0];

  /* '<S22>:1:8' */
  dY = rtu_ECEF_in[1] - rtu_ECEF_home[1];

  /* '<S22>:1:9' */
  dZ = rtu_ECEF_in[2] - rtu_ECEF_home[2];

  /* '<S22>:1:11' */
  localB->N = (-cos(rtu_WGS_home[1]) * sin(rtu_WGS_home[0]) * dX - sin
               (rtu_WGS_home[1]) * sin(rtu_WGS_home[0]) * dY) + cos
    (rtu_WGS_home[0]) * dZ;

  /* '<S22>:1:12' */
  localB->E = -sin(rtu_WGS_home[1]) * dX + cos(rtu_WGS_home[1]) * dY;

  /* '<S22>:1:13' */
  localB->D = (-cos(rtu_WGS_home[1]) * cos(rtu_WGS_home[0]) * dX - sin
               (rtu_WGS_home[1]) * cos(rtu_WGS_home[0]) * dY) - sin
    (rtu_WGS_home[0]) * dZ;
}

/*
 * Output and update for atomic system:
 *    '<S20>/MATLAB Function WGS84 TO ECEF'
 *    '<S11>/MATLAB Function WGS84 TO ECEF'
 *    '<S24>/MATLAB Function WGS84 TO ECEF'
 *    '<S12>/MATLAB Function WGS84 TO ECEF'
 */
void Model_MATLABFunctionWGS84TOECEF(const real_T rtu_WGS[3],
  B_MATLABFunctionWGS84TOECEF_M_T *localB)
{
  real_T Ne;

  /* MATLAB Function 'WGS2NED1/ECEF2NED/MATLAB Function WGS84 TO ECEF': '<S23>:1' */
  /* '<S23>:1:4' */
  /* '<S23>:1:5' */
  /* '<S23>:1:6' */
  /* '<S23>:1:8' */
  Ne = sin(rtu_WGS[0]);
  Ne = 6.378137E+6 / sqrt(1.0 - Ne * Ne * 0.0066943798522561);

  /* '<S23>:1:9' */
  /* '<S23>:1:10' */
  /* '<S23>:1:11' */
  /* '<S23>:1:13' */
  localB->ECEF[0] = (Ne + rtu_WGS[2]) * cos(rtu_WGS[0]) * cos(rtu_WGS[1]);
  localB->ECEF[1] = (Ne + rtu_WGS[2]) * cos(rtu_WGS[0]) * sin(rtu_WGS[1]);
  localB->ECEF[2] = (Ne * 0.99330562014774393 + rtu_WGS[2]) * sin(rtu_WGS[0]);
}

/*
 * Output and update for atomic system:
 *    '<Root>/single to double1'
 *    '<Root>/uint16 to double1'
 *    '<Root>/uint16 to double2'
 */
void Model_GS_singletodouble1(real32_T rtu_u, B_singletodouble1_Model_GS_T
  *localB)
{
  /* MATLAB Function 'single to double1': '<S14>:1' */
  /* '<S14>:1:4' */
  localB->y = rtu_u;
}

/* Model step function */
void Model_GSModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_Memory[3];
  real_T x;
  real_T y;
  real_T u_N;
  real_T rtb_y_a[9];
  int32_T i;
  real_T rtb_TmpSignalConversionAtSFun_0;
  real_T rtb_TmpSignalConversionAtSFun_1;
  real_T rtb_TmpSignalConversionAtSFun_2;

  /* MATLAB Function: '<Root>/uint16 to double1' incorporates:
   *  Inport: '<Root>/Actual_Yaw'
   */
  Model_GS_singletodouble1(Model_GS_U.Actual_Yaw, &Model_GS_B.sf_uint16todouble1);

  /* Memory: '<S5>/Memory' */
  rtb_Memory[0] = Model_GS_DW.Memory_PreviousInput[0];
  rtb_Memory[1] = Model_GS_DW.Memory_PreviousInput[1];
  rtb_Memory[2] = Model_GS_DW.Memory_PreviousInput[2];

  /* MATLAB Function: '<Root>/Int32 to Double6' incorporates:
   *  Inport: '<Root>/Actual_Pos '
   */
  Model_GS_Int32toDouble(Model_GS_U.Actual_Pos, &Model_GS_B.sf_Int32toDouble6);

  /* MATLAB Function: '<Root>/Scaling WGS' */
  Model_GS_ScalingWGS(Model_GS_B.sf_Int32toDouble6.y, &Model_GS_B.sf_ScalingWGS);

  /* MATLAB Function: '<S24>/MATLAB Function WGS84 TO ECEF' */
  Model_MATLABFunctionWGS84TOECEF(Model_GS_B.sf_ScalingWGS.WGS_scaled,
    &Model_GS_B.sf_MATLABFunctionWGS84TOECEF);

  /* MATLAB Function: '<S12>/MATLAB Function WGS84 TO ECEF' */
  Model_MATLABFunctionWGS84TOECEF(rtb_Memory,
    &Model_GS_B.sf_MATLABFunctionWGS84TOECEF_d);

  /* MATLAB Function: '<S24>/ ECEF to NED' */
  Model_GS_ECEFtoNED(rtb_Memory, Model_GS_B.sf_MATLABFunctionWGS84TOECEF.ECEF,
                     Model_GS_B.sf_MATLABFunctionWGS84TOECEF_d.ECEF,
                     &Model_GS_B.sf_ECEFtoNED);

  /* MATLAB Function: '<Root>/Int32 to Double' incorporates:
   *  Inport: '<Root>/Reference_Pos '
   */
  Model_GS_Int32toDouble(Model_GS_U.Reference_Pos, &Model_GS_B.sf_Int32toDouble);

  /* MATLAB Function: '<Root>/Scaling WGS1' */
  Model_GS_ScalingWGS(Model_GS_B.sf_Int32toDouble.y, &Model_GS_B.sf_ScalingWGS1);

  /* MATLAB Function: '<S20>/MATLAB Function WGS84 TO ECEF' */
  Model_MATLABFunctionWGS84TOECEF(Model_GS_B.sf_ScalingWGS1.WGS_scaled,
    &Model_GS_B.sf_MATLABFunctionWGS84TOECEF_e);

  /* MATLAB Function: '<S11>/MATLAB Function WGS84 TO ECEF' */
  Model_MATLABFunctionWGS84TOECEF(rtb_Memory,
    &Model_GS_B.sf_MATLABFunctionWGS84TOECEF_j);

  /* MATLAB Function: '<S20>/ ECEF to NED' */
  Model_GS_ECEFtoNED(rtb_Memory, Model_GS_B.sf_MATLABFunctionWGS84TOECEF_e.ECEF,
                     Model_GS_B.sf_MATLABFunctionWGS84TOECEF_j.ECEF,
                     &Model_GS_B.sf_ECEFtoNED_e);

  /* MATLAB Function: '<Root>/uint16 to double2' incorporates:
   *  Inport: '<Root>/Reference_Yaw'
   */
  Model_GS_singletodouble1(Model_GS_U.Reference_Yaw,
    &Model_GS_B.sf_uint16todouble2);

  /* MATLAB Function: '<Root>/Yaw_Check' */
  /* MATLAB Function 'Yaw_Check': '<S13>:1' */
  /* '<S13>:1:4' */
  x = Model_GS_B.sf_uint16todouble2.y / 6.2831853071795862;
  if (x < 0.0) {
    x = ceil(x);
  } else {
    x = floor(x);
  }

  /* se x==0 l'angolo è già nel range 0,2pi      */
  if (x == 0.0) {
    /* '<S13>:1:8' */
    /* '<S13>:1:9' */
    y = Model_GS_B.sf_uint16todouble2.y;
  } else {
    /* '<S13>:1:11' */
    y = Model_GS_B.sf_uint16todouble2.y - x * 2.0 * 3.1415926535897931;
  }

  if (y < 0.0) {
    /* '<S13>:1:14' */
    /* '<S13>:1:15' */
    y += 6.2831853071795862;
  }

  if (y > Model_GS_B.sf_uint16todouble1.y + 3.1415926535897931) {
    /* '<S13>:1:18' */
    /* '<S13>:1:19' */
    y -= 6.2831853071795862;
  } else {
    /* '<S13>:1:20' */
  }

  /* End of MATLAB Function: '<Root>/Yaw_Check' */

  /* MATLAB Function: '<Root>/single to double7' incorporates:
   *  Inport: '<Root>/Control_Param'
   */
  /* MATLAB Function 'single to double7': '<S15>:1' */
  /* '<S15>:1:4' */
  for (i = 0; i < 9; i++) {
    rtb_y_a[i] = Model_GS_U.Control_Param[i];
  }

  /* End of MATLAB Function: '<Root>/single to double7' */

  /* MATLAB Function: '<Root>/single to double1' incorporates:
   *  Inport: '<Root>/dt'
   */
  Model_GS_singletodouble1(Model_GS_U.dt, &Model_GS_B.sf_singletodouble1);

  /* MATLAB Function: '<Root>/Edge detector' incorporates:
   *  Inport: '<Root>/Trigger'
   */
  /* MATLAB Function 'Edge detector': '<S4>:1' */
  /* '<S4>:1:3' */
  i = 0;
  if ((Model_GS_DW.k == 0.0) && (Model_GS_U.Trigger == 1)) {
    /* '<S4>:1:9' */
    /* '<S4>:1:10' */
    Model_GS_DW.k = 1.0;

    /* '<S4>:1:11' */
    i = 1;
  }

  if ((Model_GS_DW.k == 1.0) && (Model_GS_U.Trigger == 0)) {
    /* '<S4>:1:13' */
    /* '<S4>:1:14' */
    Model_GS_DW.k = 0.0;
  }

  /* End of MATLAB Function: '<Root>/Edge detector' */

  /* MATLAB Function: '<Root>/Control Law NED' incorporates:
   *  SignalConversion: '<S2>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAt SFunction Inport2'
   */
  /* MATLAB Function 'Control Law NED': '<S2>:1' */
  /* PARAMETERS */
  /* '<S2>:1:6' */
  /* '<S2>:1:7' */
  /* '<S2>:1:8' */
  /* '<S2>:1:9' */
  /* '<S2>:1:10' */
  /* '<S2>:1:11' */
  /* '<S2>:1:12' */
  /* '<S2>:1:13' */
  /* ERROR */
  /* '<S2>:1:16' */
  /* '<S2>:1:17' */
  /* '<S2>:1:18' */
  /* '<S2>:1:19' */
  /* '<S2>:1:20' */
  /* '<S2>:1:21' */
  /* '<S2>:1:22' */
  x = Model_GS_B.sf_ECEFtoNED_e.N - Model_GS_B.sf_ECEFtoNED.N;

  /* '<S2>:1:23' */
  rtb_TmpSignalConversionAtSFun_1 = Model_GS_B.sf_ECEFtoNED_e.E -
    Model_GS_B.sf_ECEFtoNED.E;

  /* '<S2>:1:24' */
  rtb_TmpSignalConversionAtSFun_2 = Model_GS_B.sf_ECEFtoNED_e.D -
    Model_GS_B.sf_ECEFtoNED.D;

  /* '<S2>:1:25' */
  /* STATE */
  /* integral for Down to compensate midpoint RC_3 not 1500 in ardupilot */
  if (fabs(x) > rtb_y_a[6]) {
    /* '<S2>:1:33' */
    /* '<S2>:1:34' */
    u_N = rtb_y_a[3] * x;
  } else {
    /* '<S2>:1:36' */
    u_N = 0.0;
  }

  if (fabs(rtb_TmpSignalConversionAtSFun_1) > rtb_y_a[6]) {
    /* '<S2>:1:38' */
    /* '<S2>:1:39' */
    rtb_TmpSignalConversionAtSFun_1 *= rtb_y_a[3];
  } else {
    /* '<S2>:1:41' */
    rtb_TmpSignalConversionAtSFun_1 = 0.0;
  }

  if (i != 0) {
    /* '<S2>:1:44' */
    Model_GS_DW.u_D_I = 0.0;
  }

  if (fabs(rtb_TmpSignalConversionAtSFun_2) > rtb_y_a[7]) {
    /* '<S2>:1:46' */
    /* '<S2>:1:47' */
    Model_GS_DW.u_D_I += rtb_TmpSignalConversionAtSFun_2 * rtb_y_a[8] *
      Model_GS_B.sf_singletodouble1.y;

    /* integral */
    if (Model_GS_DW.u_D_I > rtb_y_a[1] / 2.0) {
      /* '<S2>:1:48' */
      /* antiwindup */
      /* '<S2>:1:49' */
      Model_GS_DW.u_D_I = rtb_y_a[1] / 2.0;
    } else {
      if (Model_GS_DW.u_D_I < -rtb_y_a[1] / 2.0) {
        /* '<S2>:1:50' */
        /* '<S2>:1:51' */
        Model_GS_DW.u_D_I = -rtb_y_a[1] / 2.0;
      }
    }

    /* '<S2>:1:54' */
    x = rtb_y_a[4] * rtb_TmpSignalConversionAtSFun_2 + Model_GS_DW.u_D_I;
  } else {
    /* '<S2>:1:56' */
    x = Model_GS_DW.u_D_I;
  }

  /* '<S2>:1:59' */
  y = (y - Model_GS_B.sf_uint16todouble1.y) * rtb_y_a[5];
  if (y > rtb_y_a[2]) {
    /* '<S2>:1:60' */
    /* '<S2>:1:61' */
    y = rtb_y_a[2];
  }

  if (y < -rtb_y_a[2]) {
    /* '<S2>:1:63' */
    /* '<S2>:1:64' */
    y = -rtb_y_a[2];
  }

  /* MATLAB Function: '<Root>/NED2BODY' incorporates:
   *  MATLAB Function: '<Root>/Control Law NED'
   */
  /* '<S2>:1:67' */
  /* MATLAB Function 'NED2BODY': '<S8>:1' */
  /* '<S8>:1:4' */
  /* '<S8>:1:5' */
  /* '<S8>:1:6' */
  /* '<S8>:1:8' */
  /* '<S8>:1:9' */
  /* '<S8>:1:12' */
  rtb_TmpSignalConversionAtSFun_0 = cos(Model_GS_B.sf_uint16todouble1.y) * u_N +
    sin(Model_GS_B.sf_uint16todouble1.y) * rtb_TmpSignalConversionAtSFun_1;
  rtb_TmpSignalConversionAtSFun_1 = -sin(Model_GS_B.sf_uint16todouble1.y) * u_N
    + cos(Model_GS_B.sf_uint16todouble1.y) * rtb_TmpSignalConversionAtSFun_1;
  rtb_TmpSignalConversionAtSFun_2 = x;

  /* MATLAB Function: '<Root>/Body Saturation' */
  /* MATLAB Function 'Body Saturation': '<S1>:1' */
  /* '<S1>:1:4' */
  /* '<S1>:1:5' */
  if (rtb_TmpSignalConversionAtSFun_0 > rtb_y_a[0]) {
    /* '<S1>:1:7' */
    /* '<S1>:1:8' */
    x = rtb_y_a[0];
  } else if (rtb_TmpSignalConversionAtSFun_0 < -rtb_y_a[0]) {
    /* '<S1>:1:9' */
    /* '<S1>:1:10' */
    x = -rtb_y_a[0];
  } else {
    /* '<S1>:1:12' */
    x = rtb_TmpSignalConversionAtSFun_0;
  }

  if (rtb_TmpSignalConversionAtSFun_1 > rtb_y_a[0]) {
    /* '<S1>:1:15' */
    /* '<S1>:1:16' */
    rtb_TmpSignalConversionAtSFun_1 = rtb_y_a[0];
  } else if (rtb_TmpSignalConversionAtSFun_1 < -rtb_y_a[0]) {
    /* '<S1>:1:17' */
    /* '<S1>:1:18' */
    rtb_TmpSignalConversionAtSFun_1 = -rtb_y_a[0];
  } else {
    /* '<S1>:1:20' */
  }

  if (rtb_TmpSignalConversionAtSFun_2 > rtb_y_a[1]) {
    /* '<S1>:1:23' */
    /* '<S1>:1:24' */
    rtb_TmpSignalConversionAtSFun_2 = rtb_y_a[1];
  } else if (rtb_TmpSignalConversionAtSFun_2 < -rtb_y_a[1]) {
    /* '<S1>:1:25' */
    /* '<S1>:1:26' */
    rtb_TmpSignalConversionAtSFun_2 = -rtb_y_a[1];
  } else {
    /* '<S1>:1:28' */
  }

  /* Outport: '<Root>/FakeDirective' incorporates:
   *  MATLAB Function: '<Root>/Body Saturation'
   *  MATLAB Function: '<Root>/Control Law NED'
   *  MATLAB Function: '<Root>/Double to Single'
   */
  /* '<S1>:1:31' */
  /* MATLAB Function 'Double to Single': '<S3>:1' */
  /* '<S3>:1:4' */
  Model_GS_Y.FakeDirective[0] = (real32_T)x;
  Model_GS_Y.FakeDirective[1] = (real32_T)rtb_TmpSignalConversionAtSFun_1;
  Model_GS_Y.FakeDirective[2] = (real32_T)rtb_TmpSignalConversionAtSFun_2;
  Model_GS_Y.FakeDirective[3] = (real32_T)y;

  /* MATLAB Function: '<S5>/trigger' */
  /* MATLAB Function 'Home/trigger': '<S19>:1' */
  if (i != 0) {
    /* Update for Memory: '<S5>/Memory' */
    /* '<S19>:1:6' */
    Model_GS_DW.Memory_PreviousInput[0] = Model_GS_B.sf_ScalingWGS.WGS_scaled[0];
    Model_GS_DW.Memory_PreviousInput[1] = Model_GS_B.sf_ScalingWGS.WGS_scaled[1];
    Model_GS_DW.Memory_PreviousInput[2] = Model_GS_B.sf_ScalingWGS.WGS_scaled[2];
  } else {
    /* Update for Memory: '<S5>/Memory' */
    /* '<S19>:1:8' */
    Model_GS_DW.Memory_PreviousInput[0] = rtb_Memory[0];
    Model_GS_DW.Memory_PreviousInput[1] = rtb_Memory[1];
    Model_GS_DW.Memory_PreviousInput[2] = rtb_Memory[2];
  }

  /* End of MATLAB Function: '<S5>/trigger' */
  /* MATLAB Function 'uint32 to double': '<S18>:1' */
  /* '<S18>:1:4' */
}

/* Model initialize function */
void Model_GSModelClass::initialize()
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus((&Model_GS_M), (NULL));

  /* block I/O */
  (void) memset(((void *) &Model_GS_B), 0,
                sizeof(B_Model_GS_T));

  /* states (dwork) */
  (void) memset((void *)&Model_GS_DW, 0,
                sizeof(DW_Model_GS_T));

  /* external inputs */
  (void) memset((void *)&Model_GS_U, 0,
                sizeof(ExtU_Model_GS_T));

  /* external outputs */
  (void) memset(&Model_GS_Y.FakeDirective[0], 0,
                4U*sizeof(real32_T));

  /* InitializeConditions for Memory: '<S5>/Memory' */
  Model_GS_DW.Memory_PreviousInput[0] = Model_GS_P.Memory_X0[0];
  Model_GS_DW.Memory_PreviousInput[1] = Model_GS_P.Memory_X0[1];
  Model_GS_DW.Memory_PreviousInput[2] = Model_GS_P.Memory_X0[2];

  /* InitializeConditions for MATLAB Function: '<Root>/Edge detector' */
  Model_GS_DW.k = 0.0;

  /* InitializeConditions for MATLAB Function: '<Root>/Control Law NED' */
  Model_GS_DW.u_D_I = 0.0;
}

/* Model terminate function */
void Model_GSModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Model_GSModelClass::Model_GSModelClass()
{
  P_Model_GS_T Model_GS_P_temp = {
    /*  Expression: [0 0 0]
     * Referenced by: '<S5>/Memory'
     */
    { 0.0, 0.0, 0.0 }
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Model_GS_P = Model_GS_P_temp;
}

/* Destructor */
Model_GSModelClass::~Model_GSModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Model_GS_T * Model_GSModelClass::getRTM()
{
  return (&Model_GS_M);
}
