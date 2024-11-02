/*
 * q_rotpen_bal_student01.c
 *
 * Code generation for model "q_rotpen_bal_student01".
 *
 * Model version              : 1.368
 * Simulink Coder version : 8.2 (R2012a) 29-Dec-2011
 * C source code generated on : Tue Nov 15 16:09:51 2016
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "q_rotpen_bal_student01.h"
#include "q_rotpen_bal_student01_private.h"
#include "q_rotpen_bal_student01_dt.h"

/* Block signals (auto storage) */
BlockIO_q_rotpen_bal_student01 q_rotpen_bal_student01_B;

/* Continuous states */
ContinuousStates_q_rotpen_bal_s q_rotpen_bal_student01_X;

/* Block states (auto storage) */
D_Work_q_rotpen_bal_student01 q_rotpen_bal_student01_DWork;

/* Real-time model */
RT_MODEL_q_rotpen_bal_student01 q_rotpen_bal_student01_M_;
RT_MODEL_q_rotpen_bal_student01 *const q_rotpen_bal_student01_M =
  &q_rotpen_bal_student01_M_;

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
  q_rotpen_bal_student01_derivatives();
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
void q_rotpen_bal_student01_output(void)
{
  /* local block i/o variables */
  real_T rtb_HPFtheta_dotrads;
  real_T rtb_HPFalpha_dotrads;
  real_T rtb_HILReadEncoder[2];
  real_T rtb_Gain1;
  real_T rtb_ConverttoVectorState_idx;
  real_T rtb_ConverttoVectorState_idx_0;
  real_T rtb_ConverttoVectorState_idx_1;
  if (rtmIsMajorTimeStep(q_rotpen_bal_student01_M)) {
    /* set solver stop time */
    if (!(q_rotpen_bal_student01_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_rotpen_bal_student01_M->solverInfo,
                            ((q_rotpen_bal_student01_M->Timing.clockTickH0 + 1) *
        q_rotpen_bal_student01_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_rotpen_bal_student01_M->solverInfo,
                            ((q_rotpen_bal_student01_M->Timing.clockTick0 + 1) *
        q_rotpen_bal_student01_M->Timing.stepSize0 +
        q_rotpen_bal_student01_M->Timing.clockTickH0 *
        q_rotpen_bal_student01_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_rotpen_bal_student01_M)) {
    q_rotpen_bal_student01_M->Timing.t[0] = rtsiGetT
      (&q_rotpen_bal_student01_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(q_rotpen_bal_student01_M)) {
    /* S-Function (hil_read_encoder_block): '<S5>/HIL Read Encoder' */

    /* S-Function Block: q_rotpen_bal_student01/SRV02-ET+ROTPEN-E/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILReadEncoder_Channels, 2,
         &q_rotpen_bal_student01_DWork.HILReadEncoder_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder[0] =
          q_rotpen_bal_student01_DWork.HILReadEncoder_Buffer[0];
        rtb_HILReadEncoder[1] =
          q_rotpen_bal_student01_DWork.HILReadEncoder_Buffer[1];
      }
    }

    /* Gain: '<S5>/Encoder Calibration  (rad//count)' */
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[0] =
      q_rotpen_bal_student01_P.EncoderCalibrationradcount_Gain *
      rtb_HILReadEncoder[0];
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[1] =
      q_rotpen_bal_student01_P.EncoderCalibrationradcount_Gain *
      rtb_HILReadEncoder[1];

    /* Sum: '<S7>/Sum' incorporates:
     *  Constant: '<S7>/Mod Angle  (rad)'
     *  Constant: '<S7>/Offset Angle  (rad)'
     *  Math: '<S7>/Math Function'
     */
    q_rotpen_bal_student01_B.Sum = rt_modd_snf
      (q_rotpen_bal_student01_B.EncoderCalibrationradcount[1],
       q_rotpen_bal_student01_P.ModAnglerad_Value) +
      q_rotpen_bal_student01_P.OffsetAnglerad_Value;

    /* RelationalOperator: '<S2>/Compare' incorporates:
     *  Abs: '<Root>/|alpha|'
     *  Constant: '<S2>/Constant'
     */
    q_rotpen_bal_student01_B.Compare = (uint8_T)(fabs
      (q_rotpen_bal_student01_B.Sum) <= q_rotpen_bal_student01_P.Constant_Value);
  }

  /* SignalGenerator: '<Root>/Signal Generator' */
  rtb_Gain1 = q_rotpen_bal_student01_P.SignalGenerator_Frequency *
    q_rotpen_bal_student01_M->Timing.t[0];
  if (rtb_Gain1 - floor(rtb_Gain1) >= 0.5) {
    rtb_Gain1 = q_rotpen_bal_student01_P.SignalGenerator_Amplitude;
  } else {
    rtb_Gain1 = -q_rotpen_bal_student01_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Gain: '<S1>/Gain1' incorporates:
   *  Gain: '<Root>/Amplitude (deg)'
   */
  rtb_Gain1 = q_rotpen_bal_student01_P.Amplitudedeg_Gain * rtb_Gain1 *
    q_rotpen_bal_student01_P.Gain1_Gain;

  /* Gain: '<Root>/Convert to  Vector State' */
  rtb_ConverttoVectorState_idx =
    q_rotpen_bal_student01_P.ConverttoVectorState_Gain[0] * rtb_Gain1;
  rtb_ConverttoVectorState_idx_0 =
    q_rotpen_bal_student01_P.ConverttoVectorState_Gain[1] * rtb_Gain1;
  rtb_ConverttoVectorState_idx_1 =
    q_rotpen_bal_student01_P.ConverttoVectorState_Gain[2] * rtb_Gain1;
  rtb_Gain1 *= q_rotpen_bal_student01_P.ConverttoVectorState_Gain[3];

  /* TransferFcn: '<S3>/HPF: theta_dot (rad//s)' */
  rtb_HPFtheta_dotrads = q_rotpen_bal_student01_P.HPFtheta_dotrads_D*
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[0];
  rtb_HPFtheta_dotrads += q_rotpen_bal_student01_P.HPFtheta_dotrads_C*
    q_rotpen_bal_student01_X.HPFtheta_dotrads_CSTATE;

  /* TransferFcn: '<S3>/HPF: alpha_dot (rad//s)' */
  rtb_HPFalpha_dotrads = q_rotpen_bal_student01_P.HPFalpha_dotrads_D*
    q_rotpen_bal_student01_B.Sum;
  rtb_HPFalpha_dotrads += q_rotpen_bal_student01_P.HPFalpha_dotrads_C*
    q_rotpen_bal_student01_X.HPFalpha_dotrads_CSTATE;

  /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
   *  Constant: '<Root>/u = 0V'
   *  Gain: '<Root>/Control  Gain'
   *  Sum: '<Root>/Sum'
   */
  if (q_rotpen_bal_student01_B.Compare == 0) {
    q_rotpen_bal_student01_B.MultiportSwitch =
      q_rotpen_bal_student01_P.u0V_Value;
  } else {
    q_rotpen_bal_student01_B.MultiportSwitch = (((rtb_ConverttoVectorState_idx -
      q_rotpen_bal_student01_B.EncoderCalibrationradcount[0]) *
      q_rotpen_bal_student01_P.ControlGain_Gain[0] +
      (rtb_ConverttoVectorState_idx_0 - q_rotpen_bal_student01_B.Sum) *
      q_rotpen_bal_student01_P.ControlGain_Gain[1]) +
      (rtb_ConverttoVectorState_idx_1 - rtb_HPFtheta_dotrads) *
      q_rotpen_bal_student01_P.ControlGain_Gain[2]) + (rtb_Gain1 -
      rtb_HPFalpha_dotrads) * q_rotpen_bal_student01_P.ControlGain_Gain[3];
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* Gain: '<S5>/Direction Convention: (Right-Hand) system' */
  rtb_Gain1 = q_rotpen_bal_student01_P.DirectionConventionRightHandsys *
    q_rotpen_bal_student01_B.MultiportSwitch;

  /* Saturate: '<S5>/Amplifier  Saturation (V)' */
  if (rtb_Gain1 >= q_rotpen_bal_student01_P.AmplifierSaturationV_UpperSat) {
    rtb_Gain1 = q_rotpen_bal_student01_P.AmplifierSaturationV_UpperSat;
  } else {
    if (rtb_Gain1 <= q_rotpen_bal_student01_P.AmplifierSaturationV_LowerSat) {
      rtb_Gain1 = q_rotpen_bal_student01_P.AmplifierSaturationV_LowerSat;
    }
  }

  /* Gain: '<S5>/Inverse Amplifier  Gain (V//V)' incorporates:
   *  Saturate: '<S5>/Amplifier  Saturation (V)'
   */
  q_rotpen_bal_student01_B.InverseAmplifierGainVV =
    q_rotpen_bal_student01_P.InverseAmplifierGainVV_Gain * rtb_Gain1;
  if (rtmIsMajorTimeStep(q_rotpen_bal_student01_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: q_rotpen_bal_student01/SRV02-ET+ROTPEN-E/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        &q_rotpen_bal_student01_P.HILWriteAnalog_Channels, 1,
        &q_rotpen_bal_student01_B.InverseAmplifierGainVV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      }
    }

    /* S-Function (hil_write_digital_block): '<S5>/HIL Write Digital' */

    /* S-Function Block: q_rotpen_bal_student01/SRV02-ET+ROTPEN-E/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      q_rotpen_bal_student01_DWork.HILWriteDigital_Buffer[0] =
        (q_rotpen_bal_student01_P.EnableVoltPAQX2X4_Value[0] != 0);
      q_rotpen_bal_student01_DWork.HILWriteDigital_Buffer[1] =
        (q_rotpen_bal_student01_P.EnableVoltPAQX2X4_Value[1] != 0);
      q_rotpen_bal_student01_DWork.HILWriteDigital_Buffer[2] =
        (q_rotpen_bal_student01_P.EnableVoltPAQX2X4_Value[2] != 0);
      q_rotpen_bal_student01_DWork.HILWriteDigital_Buffer[3] =
        (q_rotpen_bal_student01_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        q_rotpen_bal_student01_P.HILWriteDigital_Channels, 4,
        &q_rotpen_bal_student01_DWork.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      }
    }

    /* Gain: '<S8>/Gain' */
    q_rotpen_bal_student01_B.Gain = q_rotpen_bal_student01_P.Gain_Gain *
      q_rotpen_bal_student01_B.Sum;
  }

  /* Gain: '<S9>/Gain' */
  q_rotpen_bal_student01_B.Gain_a[0] = q_rotpen_bal_student01_P.Gain_Gain_n *
    rtb_ConverttoVectorState_idx;
  q_rotpen_bal_student01_B.Gain_a[1] = q_rotpen_bal_student01_P.Gain_Gain_n *
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[0];
  if (rtmIsMajorTimeStep(q_rotpen_bal_student01_M)) {
  }
}

/* Model update function */
void q_rotpen_bal_student01_update(void)
{
  if (rtmIsMajorTimeStep(q_rotpen_bal_student01_M)) {
    rt_ertODEUpdateContinuousStates(&q_rotpen_bal_student01_M->solverInfo);
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
  if (!(++q_rotpen_bal_student01_M->Timing.clockTick0)) {
    ++q_rotpen_bal_student01_M->Timing.clockTickH0;
  }

  q_rotpen_bal_student01_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_rotpen_bal_student01_M->solverInfo);

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
    if (!(++q_rotpen_bal_student01_M->Timing.clockTick1)) {
      ++q_rotpen_bal_student01_M->Timing.clockTickH1;
    }

    q_rotpen_bal_student01_M->Timing.t[1] =
      q_rotpen_bal_student01_M->Timing.clockTick1 *
      q_rotpen_bal_student01_M->Timing.stepSize1 +
      q_rotpen_bal_student01_M->Timing.clockTickH1 *
      q_rotpen_bal_student01_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_rotpen_bal_student01_derivatives(void)
{
  /* Derivatives for TransferFcn: '<S3>/HPF: theta_dot (rad//s)' */
  {
    ((StateDerivatives_q_rotpen_bal_s *)
      q_rotpen_bal_student01_M->ModelData.derivs)->HPFtheta_dotrads_CSTATE =
      q_rotpen_bal_student01_B.EncoderCalibrationradcount[0];
    ((StateDerivatives_q_rotpen_bal_s *)
      q_rotpen_bal_student01_M->ModelData.derivs)->HPFtheta_dotrads_CSTATE +=
      (q_rotpen_bal_student01_P.HPFtheta_dotrads_A)*
      q_rotpen_bal_student01_X.HPFtheta_dotrads_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S3>/HPF: alpha_dot (rad//s)' */
  {
    ((StateDerivatives_q_rotpen_bal_s *)
      q_rotpen_bal_student01_M->ModelData.derivs)->HPFalpha_dotrads_CSTATE =
      q_rotpen_bal_student01_B.Sum;
    ((StateDerivatives_q_rotpen_bal_s *)
      q_rotpen_bal_student01_M->ModelData.derivs)->HPFalpha_dotrads_CSTATE +=
      (q_rotpen_bal_student01_P.HPFalpha_dotrads_A)*
      q_rotpen_bal_student01_X.HPFalpha_dotrads_CSTATE;
  }
}

/* Model initialize function */
void q_rotpen_bal_student01_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S5>/HIL Initialize' */

  /* S-Function Block: q_rotpen_bal_student01/SRV02-ET+ROTPEN-E/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &q_rotpen_bal_student01_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (q_rotpen_bal_student01_DWork.HILInitialize_Card, "update_rate=normal", 19);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      return;
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_AIPStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &q_rotpen_bal_student01_DWork.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = q_rotpen_bal_student01_P.HILInitialize_AILow;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &q_rotpen_bal_student01_DWork.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = q_rotpen_bal_student01_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_AIChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_AIMinimums[0],
         &q_rotpen_bal_student01_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_AOPStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &q_rotpen_bal_student01_DWork.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = q_rotpen_bal_student01_P.HILInitialize_AOLow;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &q_rotpen_bal_student01_DWork.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = q_rotpen_bal_student01_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_AOChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_AOMinimums[0],
         &q_rotpen_bal_student01_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_AOStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_bal_student01_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        q_rotpen_bal_student01_P.HILInitialize_AOChannels, 8U,
        &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if (q_rotpen_bal_student01_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_bal_student01_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_AOChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (q_rotpen_bal_student01_DWork.HILInitialize_Card, NULL, 0U,
       q_rotpen_bal_student01_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
      return;
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_DOStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits =
          &q_rotpen_bal_student01_DWork.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_rotpen_bal_student01_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        q_rotpen_bal_student01_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &q_rotpen_bal_student01_DWork.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if (q_rotpen_bal_student01_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates =
          &q_rotpen_bal_student01_DWork.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = q_rotpen_bal_student01_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *)
         &q_rotpen_bal_student01_DWork.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_EIPStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &q_rotpen_bal_student01_DWork.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            q_rotpen_bal_student01_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &q_rotpen_bal_student01_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_EIStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &q_rotpen_bal_student01_DWork.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            q_rotpen_bal_student01_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_EIChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_POPStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = q_rotpen_bal_student01_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        q_rotpen_bal_student01_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &q_rotpen_bal_student01_DWork.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          q_rotpen_bal_student01_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            q_rotpen_bal_student01_DWork.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = q_rotpen_bal_student01_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            q_rotpen_bal_student01_DWork.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              q_rotpen_bal_student01_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (q_rotpen_bal_student01_DWork.HILInitialize_Card,
           &q_rotpen_bal_student01_DWork.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (q_rotpen_bal_student01_DWork.HILInitialize_Card,
           &q_rotpen_bal_student01_DWork.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            q_rotpen_bal_student01_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            q_rotpen_bal_student01_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &q_rotpen_bal_student01_DWork.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            q_rotpen_bal_student01_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_POChannels, 8U,
         (t_pwm_configuration *)
         &q_rotpen_bal_student01_DWork.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &q_rotpen_bal_student01_DWork.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &q_rotpen_bal_student01_DWork.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            q_rotpen_bal_student01_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_rotpen_bal_student01_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_POChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[0],
         &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_POStart && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_rotpen_bal_student01_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(q_rotpen_bal_student01_DWork.HILInitialize_Card,
        q_rotpen_bal_student01_P.HILInitialize_POChannels, 8U,
        &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }

    if (q_rotpen_bal_student01_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_rotpen_bal_student01_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (q_rotpen_bal_student01_DWork.HILInitialize_Card,
         q_rotpen_bal_student01_P.HILInitialize_POChannels, 8U,
         &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S3>/HPF: theta_dot (rad//s)' */
  q_rotpen_bal_student01_X.HPFtheta_dotrads_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/HPF: alpha_dot (rad//s)' */
  q_rotpen_bal_student01_X.HPFalpha_dotrads_CSTATE = 0.0;
}

/* Model terminate function */
void q_rotpen_bal_student01_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S5>/HIL Initialize' */

  /* S-Function Block: q_rotpen_bal_student01/SRV02-ET+ROTPEN-E/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    hil_monitor_stop_all(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    is_switching = false;
    if ((q_rotpen_bal_student01_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_bal_student01_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_DOTerminate && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits =
          &q_rotpen_bal_student01_DWork.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_rotpen_bal_student01_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 8U;
    }

    if ((q_rotpen_bal_student01_P.HILInitialize_POTerminate && !is_switching) ||
        (q_rotpen_bal_student01_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_rotpen_bal_student01_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_rotpen_bal_student01_DWork.HILInitialize_Card
                         , q_rotpen_bal_student01_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , q_rotpen_bal_student01_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , q_rotpen_bal_student01_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         ,
                         &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages
                         [0]
                         , &q_rotpen_bal_student01_DWork.HILInitialize_POValues
                         [0]
                         , (t_boolean *)
                         &q_rotpen_bal_student01_DWork.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_rotpen_bal_student01_DWork.HILInitialize_Card,
             q_rotpen_bal_student01_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (q_rotpen_bal_student01_DWork.HILInitialize_Card,
             q_rotpen_bal_student01_P.HILInitialize_POChannels,
             num_final_pwm_outputs,
             &q_rotpen_bal_student01_DWork.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (q_rotpen_bal_student01_DWork.HILInitialize_Card,
             q_rotpen_bal_student01_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &q_rotpen_bal_student01_DWork.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_rotpen_bal_student01_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    hil_monitor_delete_all(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    hil_close(q_rotpen_bal_student01_DWork.HILInitialize_Card);
    q_rotpen_bal_student01_DWork.HILInitialize_Card = NULL;
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
  q_rotpen_bal_student01_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_rotpen_bal_student01_update();

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
  q_rotpen_bal_student01_initialize();
}

void MdlTerminate(void)
{
  q_rotpen_bal_student01_terminate();
}

RT_MODEL_q_rotpen_bal_student01 *q_rotpen_bal_student01(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_rotpen_bal_student01_M, 0,
                sizeof(RT_MODEL_q_rotpen_bal_student01));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_rotpen_bal_student01_M->solverInfo,
                          &q_rotpen_bal_student01_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_rotpen_bal_student01_M->solverInfo, &rtmGetTPtr
                (q_rotpen_bal_student01_M));
    rtsiSetStepSizePtr(&q_rotpen_bal_student01_M->solverInfo,
                       &q_rotpen_bal_student01_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_rotpen_bal_student01_M->solverInfo,
                 &q_rotpen_bal_student01_M->ModelData.derivs);
    rtsiSetContStatesPtr(&q_rotpen_bal_student01_M->solverInfo,
                         &q_rotpen_bal_student01_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&q_rotpen_bal_student01_M->solverInfo,
      &q_rotpen_bal_student01_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&q_rotpen_bal_student01_M->solverInfo,
                          (&rtmGetErrorStatus(q_rotpen_bal_student01_M)));
    rtsiSetRTModelPtr(&q_rotpen_bal_student01_M->solverInfo,
                      q_rotpen_bal_student01_M);
  }

  rtsiSetSimTimeStep(&q_rotpen_bal_student01_M->solverInfo, MAJOR_TIME_STEP);
  q_rotpen_bal_student01_M->ModelData.intgData.f[0] =
    q_rotpen_bal_student01_M->ModelData.odeF[0];
  q_rotpen_bal_student01_M->ModelData.contStates = ((real_T *)
    &q_rotpen_bal_student01_X);
  rtsiSetSolverData(&q_rotpen_bal_student01_M->solverInfo, (void *)
                    &q_rotpen_bal_student01_M->ModelData.intgData);
  rtsiSetSolverName(&q_rotpen_bal_student01_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_rotpen_bal_student01_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_rotpen_bal_student01_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_rotpen_bal_student01_M->Timing.sampleTimes =
      (&q_rotpen_bal_student01_M->Timing.sampleTimesArray[0]);
    q_rotpen_bal_student01_M->Timing.offsetTimes =
      (&q_rotpen_bal_student01_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_rotpen_bal_student01_M->Timing.sampleTimes[0] = (0.0);
    q_rotpen_bal_student01_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_rotpen_bal_student01_M->Timing.offsetTimes[0] = (0.0);
    q_rotpen_bal_student01_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_rotpen_bal_student01_M, &q_rotpen_bal_student01_M->Timing.tArray
             [0]);

  {
    int_T *mdlSampleHits = q_rotpen_bal_student01_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_rotpen_bal_student01_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_rotpen_bal_student01_M, -1);
  q_rotpen_bal_student01_M->Timing.stepSize0 = 0.002;
  q_rotpen_bal_student01_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  q_rotpen_bal_student01_M->Sizes.checksums[0] = (3394023988U);
  q_rotpen_bal_student01_M->Sizes.checksums[1] = (154910477U);
  q_rotpen_bal_student01_M->Sizes.checksums[2] = (2469534246U);
  q_rotpen_bal_student01_M->Sizes.checksums[3] = (487944424U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    q_rotpen_bal_student01_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_rotpen_bal_student01_M->extModeInfo,
      &q_rotpen_bal_student01_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_rotpen_bal_student01_M->extModeInfo,
                        q_rotpen_bal_student01_M->Sizes.checksums);
    rteiSetTPtr(q_rotpen_bal_student01_M->extModeInfo, rtmGetTPtr
                (q_rotpen_bal_student01_M));
  }

  q_rotpen_bal_student01_M->solverInfoPtr =
    (&q_rotpen_bal_student01_M->solverInfo);
  q_rotpen_bal_student01_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_rotpen_bal_student01_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_rotpen_bal_student01_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_rotpen_bal_student01_M->ModelData.blockIO = ((void *)
    &q_rotpen_bal_student01_B);
  (void) memset(((void *) &q_rotpen_bal_student01_B), 0,
                sizeof(BlockIO_q_rotpen_bal_student01));

  {
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[0] = 0.0;
    q_rotpen_bal_student01_B.EncoderCalibrationradcount[1] = 0.0;
    q_rotpen_bal_student01_B.Sum = 0.0;
    q_rotpen_bal_student01_B.MultiportSwitch = 0.0;
    q_rotpen_bal_student01_B.InverseAmplifierGainVV = 0.0;
    q_rotpen_bal_student01_B.Gain = 0.0;
    q_rotpen_bal_student01_B.Gain_a[0] = 0.0;
    q_rotpen_bal_student01_B.Gain_a[1] = 0.0;
  }

  /* parameters */
  q_rotpen_bal_student01_M->ModelData.defaultParam = ((real_T *)
    &q_rotpen_bal_student01_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_rotpen_bal_student01_X;
    q_rotpen_bal_student01_M->ModelData.contStates = (x);
    (void) memset((void *)&q_rotpen_bal_student01_X, 0,
                  sizeof(ContinuousStates_q_rotpen_bal_s));
  }

  /* states (dwork) */
  q_rotpen_bal_student01_M->Work.dwork = ((void *) &q_rotpen_bal_student01_DWork);
  (void) memset((void *)&q_rotpen_bal_student01_DWork, 0,
                sizeof(D_Work_q_rotpen_bal_student01));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_bal_student01_DWork.HILInitialize_POValues[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_rotpen_bal_student01_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_rotpen_bal_student01_M->Sizes.numContStates = (2);/* Number of continuous states */
  q_rotpen_bal_student01_M->Sizes.numY = (0);/* Number of model outputs */
  q_rotpen_bal_student01_M->Sizes.numU = (0);/* Number of model inputs */
  q_rotpen_bal_student01_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_rotpen_bal_student01_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_rotpen_bal_student01_M->Sizes.numBlocks = (32);/* Number of blocks */
  q_rotpen_bal_student01_M->Sizes.numBlockIO = (7);/* Number of block outputs */
  q_rotpen_bal_student01_M->Sizes.numBlockPrms = (145);/* Sum of parameter "widths" */
  return q_rotpen_bal_student01_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
