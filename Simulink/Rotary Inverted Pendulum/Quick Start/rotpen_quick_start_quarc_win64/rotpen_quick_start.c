/*
 * rotpen_quick_start.c
 *
 * Code generation for model "rotpen_quick_start".
 *
 * Model version              : 1.48
 * Simulink Coder version : 8.2 (R2012a) 29-Dec-2011
 * C source code generated on : Fri Nov 10 09:32:03 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "rotpen_quick_start.h"
#include "rotpen_quick_start_private.h"
#include "rotpen_quick_start_dt.h"

/* Block signals (auto storage) */
BlockIO_rotpen_quick_start rotpen_quick_start_B;

/* Continuous states */
ContinuousStates_rotpen_quick_s rotpen_quick_start_X;

/* Block states (auto storage) */
D_Work_rotpen_quick_start rotpen_quick_start_DWork;

/* Real-time model */
RT_MODEL_rotpen_quick_start rotpen_quick_start_M_;
RT_MODEL_rotpen_quick_start *const rotpen_quick_start_M = &rotpen_quick_start_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  rotpen_quick_start_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = -0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  if (u1 == 0.0) {
    y = u0;
  } else if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf
                (u1))))) {
    y = (rtNaN);
  } else {
    tmp = u0 / u1;
    if (u1 <= floor(u1)) {
      y = u0 - floor(tmp) * u1;
    } else if (fabs(tmp - rt_roundd_snf(tmp)) <= DBL_EPSILON * fabs(tmp)) {
      y = 0.0;
    } else {
      y = (tmp - floor(tmp)) * u1;
    }
  }

  return y;
}

/* Model output function */
void rotpen_quick_start_output(void)
{
  /* local block i/o variables */
  real_T rtb_ServoVelocity;
  real_T rtb_PendulumVelocity;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_Abs;
  real_T rtb_EnableBalanceControlSwitch;
  if (rtmIsMajorTimeStep(rotpen_quick_start_M)) {
    /* set solver stop time */
    if (!(rotpen_quick_start_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&rotpen_quick_start_M->solverInfo,
                            ((rotpen_quick_start_M->Timing.clockTickH0 + 1) *
        rotpen_quick_start_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&rotpen_quick_start_M->solverInfo,
                            ((rotpen_quick_start_M->Timing.clockTick0 + 1) *
        rotpen_quick_start_M->Timing.stepSize0 +
        rotpen_quick_start_M->Timing.clockTickH0 *
        rotpen_quick_start_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rotpen_quick_start_M)) {
    rotpen_quick_start_M->Timing.t[0] = rtsiGetT
      (&rotpen_quick_start_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(rotpen_quick_start_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: rotpen_quick_start/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (rotpen_quick_start_DWork.HILReadEncoderTimebase_Task, 1,
         &rotpen_quick_start_DWork.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          rotpen_quick_start_DWork.HILReadEncoderTimebase_Buffer[0];
        rtb_Abs = rotpen_quick_start_DWork.HILReadEncoderTimebase_Buffer[1];
      }
    }

    /* Gain: '<Root>/pendulum:  counts to rad' */
    rtb_Abs *= rotpen_quick_start_P.pendulumcountstorad_Gain;

    /* Math: '<Root>/Math Function' incorporates:
     *  Constant: '<Root>/Mod Angle  (rad)'
     */
    rtb_Abs = rt_modd_snf(rtb_Abs, rotpen_quick_start_P.ModAnglerad_Value);

    /* Bias: '<Root>/Offset Angle (rad)' */
    rotpen_quick_start_B.OffsetAnglerad = rtb_Abs +
      rotpen_quick_start_P.OffsetAnglerad_Bias;

    /* Abs: '<Root>/Abs' */
    rtb_Abs = fabs(rotpen_quick_start_B.OffsetAnglerad);

    /* RelationalOperator: '<S1>/Compare' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rotpen_quick_start_B.Compare = (uint8_T)(rtb_Abs <=
      rotpen_quick_start_P.Constant_Value);

    /* Gain: '<Root>/servo:  counts to rad' */
    rotpen_quick_start_B.servocountstorad =
      rotpen_quick_start_P.servocountstorad_Gain * rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<Root>/Servo Velocity' */
  rtb_ServoVelocity = rotpen_quick_start_P.ServoVelocity_D*
    rotpen_quick_start_B.servocountstorad;
  rtb_ServoVelocity += rotpen_quick_start_P.ServoVelocity_C*
    rotpen_quick_start_X.ServoVelocity_CSTATE;

  /* TransferFcn: '<Root>/Pendulum Velocity' */
  rtb_PendulumVelocity = rotpen_quick_start_P.PendulumVelocity_D*
    rotpen_quick_start_B.OffsetAnglerad;
  rtb_PendulumVelocity += rotpen_quick_start_P.PendulumVelocity_C*
    rotpen_quick_start_X.PendulumVelocity_CSTATE;

  /* MultiPortSwitch: '<Root>/Enable Balance Control Switch' incorporates:
   *  Constant: '<Root>/Control OFF'
   *  Constant: '<Root>/Setpoint'
   *  Gain: '<Root>/Control gain'
   *  Sum: '<Root>/Sum1'
   */
  if (rotpen_quick_start_B.Compare == 0) {
    rtb_EnableBalanceControlSwitch = rotpen_quick_start_P.ControlOFF_Value;
  } else {
    rtb_EnableBalanceControlSwitch = (((rotpen_quick_start_P.Setpoint_Value[0] -
      rotpen_quick_start_B.servocountstorad) *
      rotpen_quick_start_P.Controlgain_Gain[0] +
      (rotpen_quick_start_P.Setpoint_Value[1] -
       rotpen_quick_start_B.OffsetAnglerad) *
      rotpen_quick_start_P.Controlgain_Gain[1]) +
      (rotpen_quick_start_P.Setpoint_Value[2] - rtb_ServoVelocity) *
      rotpen_quick_start_P.Controlgain_Gain[2]) +
      (rotpen_quick_start_P.Setpoint_Value[3] - rtb_PendulumVelocity) *
      rotpen_quick_start_P.Controlgain_Gain[3];
  }

  /* End of MultiPortSwitch: '<Root>/Enable Balance Control Switch' */

  /* Gain: '<Root>/Motor Direction ' */
  rotpen_quick_start_B.MotorDirection = rotpen_quick_start_P.MotorDirection_Gain
    * rtb_EnableBalanceControlSwitch;
  if (rtmIsMajorTimeStep(rotpen_quick_start_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: rotpen_quick_start/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(rotpen_quick_start_DWork.HILInitialize_Card,
        &rotpen_quick_start_P.HILWriteAnalog_Channels, 1,
        &rotpen_quick_start_B.MotorDirection);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
      }
    }

    /* Gain: '<S2>/Gain' */
    rotpen_quick_start_B.Gain = rotpen_quick_start_P.Gain_Gain *
      rotpen_quick_start_B.OffsetAnglerad;

    /* Gain: '<S3>/Gain' */
    rotpen_quick_start_B.Gain_f = rotpen_quick_start_P.Gain_Gain_c *
      rotpen_quick_start_B.servocountstorad;
  }
}

/* Model update function */
void rotpen_quick_start_update(void)
{
  if (rtmIsMajorTimeStep(rotpen_quick_start_M)) {
    rt_ertODEUpdateContinuousStates(&rotpen_quick_start_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++rotpen_quick_start_M->Timing.clockTick0)) {
    ++rotpen_quick_start_M->Timing.clockTickH0;
  }

  rotpen_quick_start_M->Timing.t[0] = rtsiGetSolverStopTime
    (&rotpen_quick_start_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++rotpen_quick_start_M->Timing.clockTick1)) {
      ++rotpen_quick_start_M->Timing.clockTickH1;
    }

    rotpen_quick_start_M->Timing.t[1] = rotpen_quick_start_M->Timing.clockTick1 *
      rotpen_quick_start_M->Timing.stepSize1 +
      rotpen_quick_start_M->Timing.clockTickH1 *
      rotpen_quick_start_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void rotpen_quick_start_derivatives(void)
{
  /* Derivatives for TransferFcn: '<Root>/Servo Velocity' */
  {
    ((StateDerivatives_rotpen_quick_s *) rotpen_quick_start_M->ModelData.derivs
      )->ServoVelocity_CSTATE = rotpen_quick_start_B.servocountstorad;
    ((StateDerivatives_rotpen_quick_s *) rotpen_quick_start_M->ModelData.derivs
      )->ServoVelocity_CSTATE += (rotpen_quick_start_P.ServoVelocity_A)*
      rotpen_quick_start_X.ServoVelocity_CSTATE;
  }

  /* Derivatives for TransferFcn: '<Root>/Pendulum Velocity' */
  {
    ((StateDerivatives_rotpen_quick_s *) rotpen_quick_start_M->ModelData.derivs
      )->PendulumVelocity_CSTATE = rotpen_quick_start_B.OffsetAnglerad;
    ((StateDerivatives_rotpen_quick_s *) rotpen_quick_start_M->ModelData.derivs
      )->PendulumVelocity_CSTATE += (rotpen_quick_start_P.PendulumVelocity_A)*
      rotpen_quick_start_X.PendulumVelocity_CSTATE;
  }
}

/* Model initialize function */
void rotpen_quick_start_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: rotpen_quick_start/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &rotpen_quick_start_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (rotpen_quick_start_DWork.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(rotpen_quick_start_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
      return;
    }

    if ((rotpen_quick_start_P.HILInitialize_AIPStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &rotpen_quick_start_DWork.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = rotpen_quick_start_P.HILInitialize_AILow;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &rotpen_quick_start_DWork.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = rotpen_quick_start_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_AIChannels, 8U,
         &rotpen_quick_start_DWork.HILInitialize_AIMinimums[0],
         &rotpen_quick_start_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_AOPStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &rotpen_quick_start_DWork.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = rotpen_quick_start_P.HILInitialize_AOLow;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &rotpen_quick_start_DWork.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = rotpen_quick_start_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_AOChannels, 8U,
         &rotpen_quick_start_DWork.HILInitialize_AOMinimums[0],
         &rotpen_quick_start_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_AOStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = rotpen_quick_start_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(rotpen_quick_start_DWork.HILInitialize_Card,
        rotpen_quick_start_P.HILInitialize_AOChannels, 8U,
        &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if (rotpen_quick_start_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = rotpen_quick_start_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_AOChannels, 8U,
         &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_EIPStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &rotpen_quick_start_DWork.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            rotpen_quick_start_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &rotpen_quick_start_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_EIStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &rotpen_quick_start_DWork.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = rotpen_quick_start_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_EIChannels, 8U,
         &rotpen_quick_start_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_POPStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &rotpen_quick_start_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = rotpen_quick_start_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(rotpen_quick_start_DWork.HILInitialize_Card,
        rotpen_quick_start_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &rotpen_quick_start_DWork.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          rotpen_quick_start_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &rotpen_quick_start_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            rotpen_quick_start_DWork.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = rotpen_quick_start_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            rotpen_quick_start_DWork.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              rotpen_quick_start_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (rotpen_quick_start_DWork.HILInitialize_Card,
           &rotpen_quick_start_DWork.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (rotpen_quick_start_DWork.HILInitialize_Card,
           &rotpen_quick_start_DWork.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &rotpen_quick_start_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            rotpen_quick_start_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &rotpen_quick_start_DWork.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = rotpen_quick_start_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &rotpen_quick_start_DWork.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = rotpen_quick_start_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_POChannels, 8U,
         (t_pwm_configuration *)
         &rotpen_quick_start_DWork.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &rotpen_quick_start_DWork.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &rotpen_quick_start_DWork.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = rotpen_quick_start_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &rotpen_quick_start_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = rotpen_quick_start_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(rotpen_quick_start_DWork.HILInitialize_Card,
        rotpen_quick_start_P.HILInitialize_POChannels, 8U,
        &rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[0],
        &rotpen_quick_start_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((rotpen_quick_start_P.HILInitialize_POStart && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &rotpen_quick_start_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = rotpen_quick_start_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(rotpen_quick_start_DWork.HILInitialize_Card,
        rotpen_quick_start_P.HILInitialize_POChannels, 8U,
        &rotpen_quick_start_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }

    if (rotpen_quick_start_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &rotpen_quick_start_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = rotpen_quick_start_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (rotpen_quick_start_DWork.HILInitialize_Card,
         rotpen_quick_start_P.HILInitialize_POChannels, 8U,
         &rotpen_quick_start_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: rotpen_quick_start/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (rotpen_quick_start_DWork.HILInitialize_Card,
       rotpen_quick_start_P.HILReadEncoderTimebase_SamplesI,
       rotpen_quick_start_P.HILReadEncoderTimebase_Channels, 2,
       &rotpen_quick_start_DWork.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
    }
  }

  /* InitializeConditions for TransferFcn: '<Root>/Servo Velocity' */
  rotpen_quick_start_X.ServoVelocity_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Pendulum Velocity' */
  rotpen_quick_start_X.PendulumVelocity_CSTATE = 0.0;
}

/* Model terminate function */
void rotpen_quick_start_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: rotpen_quick_start/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(rotpen_quick_start_DWork.HILInitialize_Card);
    hil_monitor_stop_all(rotpen_quick_start_DWork.HILInitialize_Card);
    is_switching = false;
    if ((rotpen_quick_start_P.HILInitialize_AOTerminate && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = rotpen_quick_start_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((rotpen_quick_start_P.HILInitialize_POTerminate && !is_switching) ||
        (rotpen_quick_start_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &rotpen_quick_start_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = rotpen_quick_start_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(rotpen_quick_start_DWork.HILInitialize_Card
                         , rotpen_quick_start_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , rotpen_quick_start_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0]
                         , &rotpen_quick_start_DWork.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (rotpen_quick_start_DWork.HILInitialize_Card,
             rotpen_quick_start_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &rotpen_quick_start_DWork.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (rotpen_quick_start_DWork.HILInitialize_Card,
             rotpen_quick_start_P.HILInitialize_POChannels,
             num_final_pwm_outputs,
             &rotpen_quick_start_DWork.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(rotpen_quick_start_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(rotpen_quick_start_DWork.HILInitialize_Card);
    hil_monitor_delete_all(rotpen_quick_start_DWork.HILInitialize_Card);
    hil_close(rotpen_quick_start_DWork.HILInitialize_Card);
    rotpen_quick_start_DWork.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  rotpen_quick_start_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  rotpen_quick_start_update();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  rotpen_quick_start_initialize();
}

void MdlTerminate(void)
{
  rotpen_quick_start_terminate();
}

RT_MODEL_rotpen_quick_start *rotpen_quick_start(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)rotpen_quick_start_M, 0,
                sizeof(RT_MODEL_rotpen_quick_start));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rotpen_quick_start_M->solverInfo,
                          &rotpen_quick_start_M->Timing.simTimeStep);
    rtsiSetTPtr(&rotpen_quick_start_M->solverInfo, &rtmGetTPtr
                (rotpen_quick_start_M));
    rtsiSetStepSizePtr(&rotpen_quick_start_M->solverInfo,
                       &rotpen_quick_start_M->Timing.stepSize0);
    rtsiSetdXPtr(&rotpen_quick_start_M->solverInfo,
                 &rotpen_quick_start_M->ModelData.derivs);
    rtsiSetContStatesPtr(&rotpen_quick_start_M->solverInfo,
                         &rotpen_quick_start_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&rotpen_quick_start_M->solverInfo,
      &rotpen_quick_start_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&rotpen_quick_start_M->solverInfo, (&rtmGetErrorStatus
                           (rotpen_quick_start_M)));
    rtsiSetRTModelPtr(&rotpen_quick_start_M->solverInfo, rotpen_quick_start_M);
  }

  rtsiSetSimTimeStep(&rotpen_quick_start_M->solverInfo, MAJOR_TIME_STEP);
  rotpen_quick_start_M->ModelData.intgData.f[0] =
    rotpen_quick_start_M->ModelData.odeF[0];
  rotpen_quick_start_M->ModelData.contStates = ((real_T *) &rotpen_quick_start_X);
  rtsiSetSolverData(&rotpen_quick_start_M->solverInfo, (void *)
                    &rotpen_quick_start_M->ModelData.intgData);
  rtsiSetSolverName(&rotpen_quick_start_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = rotpen_quick_start_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    rotpen_quick_start_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rotpen_quick_start_M->Timing.sampleTimes =
      (&rotpen_quick_start_M->Timing.sampleTimesArray[0]);
    rotpen_quick_start_M->Timing.offsetTimes =
      (&rotpen_quick_start_M->Timing.offsetTimesArray[0]);

    /* task periods */
    rotpen_quick_start_M->Timing.sampleTimes[0] = (0.0);
    rotpen_quick_start_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    rotpen_quick_start_M->Timing.offsetTimes[0] = (0.0);
    rotpen_quick_start_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(rotpen_quick_start_M, &rotpen_quick_start_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = rotpen_quick_start_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    rotpen_quick_start_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(rotpen_quick_start_M, -1);
  rotpen_quick_start_M->Timing.stepSize0 = 0.002;
  rotpen_quick_start_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  rotpen_quick_start_M->Sizes.checksums[0] = (1564027675U);
  rotpen_quick_start_M->Sizes.checksums[1] = (1396097501U);
  rotpen_quick_start_M->Sizes.checksums[2] = (1065466621U);
  rotpen_quick_start_M->Sizes.checksums[3] = (311668803U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    rotpen_quick_start_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rotpen_quick_start_M->extModeInfo,
      &rotpen_quick_start_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rotpen_quick_start_M->extModeInfo,
                        rotpen_quick_start_M->Sizes.checksums);
    rteiSetTPtr(rotpen_quick_start_M->extModeInfo, rtmGetTPtr
                (rotpen_quick_start_M));
  }

  rotpen_quick_start_M->solverInfoPtr = (&rotpen_quick_start_M->solverInfo);
  rotpen_quick_start_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&rotpen_quick_start_M->solverInfo, 0.002);
  rtsiSetSolverMode(&rotpen_quick_start_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  rotpen_quick_start_M->ModelData.blockIO = ((void *) &rotpen_quick_start_B);
  (void) memset(((void *) &rotpen_quick_start_B), 0,
                sizeof(BlockIO_rotpen_quick_start));

  {
    rotpen_quick_start_B.OffsetAnglerad = 0.0;
    rotpen_quick_start_B.servocountstorad = 0.0;
    rotpen_quick_start_B.MotorDirection = 0.0;
    rotpen_quick_start_B.Gain = 0.0;
    rotpen_quick_start_B.Gain_f = 0.0;
  }

  /* parameters */
  rotpen_quick_start_M->ModelData.defaultParam = ((real_T *)
    &rotpen_quick_start_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &rotpen_quick_start_X;
    rotpen_quick_start_M->ModelData.contStates = (x);
    (void) memset((void *)&rotpen_quick_start_X, 0,
                  sizeof(ContinuousStates_rotpen_quick_s));
  }

  /* states (dwork) */
  rotpen_quick_start_M->Work.dwork = ((void *) &rotpen_quick_start_DWork);
  (void) memset((void *)&rotpen_quick_start_DWork, 0,
                sizeof(D_Work_rotpen_quick_start));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      rotpen_quick_start_DWork.HILInitialize_POValues[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    rotpen_quick_start_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  rotpen_quick_start_M->Sizes.numContStates = (2);/* Number of continuous states */
  rotpen_quick_start_M->Sizes.numY = (0);/* Number of model outputs */
  rotpen_quick_start_M->Sizes.numU = (0);/* Number of model inputs */
  rotpen_quick_start_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  rotpen_quick_start_M->Sizes.numSampTimes = (2);/* Number of sample times */
  rotpen_quick_start_M->Sizes.numBlocks = (25);/* Number of blocks */
  rotpen_quick_start_M->Sizes.numBlockIO = (6);/* Number of block outputs */
  rotpen_quick_start_M->Sizes.numBlockPrms = (124);/* Sum of parameter "widths" */
  return rotpen_quick_start_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
