/*
 * q_rotpen_mdl_student.c
 *
 * Code generation for model "q_rotpen_mdl_student".
 *
 * Model version              : 1.370
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Thu Nov 29 15:02:48 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_rotpen_mdl_student.h"
#include "q_rotpen_mdl_student_private.h"
#include "q_rotpen_mdl_student_dt.h"

/* Block signals (auto storage) */
B_q_rotpen_mdl_student_T q_rotpen_mdl_student_B;

/* Block states (auto storage) */
DW_q_rotpen_mdl_student_T q_rotpen_mdl_student_DW;

/* Real-time model */
RT_MODEL_q_rotpen_mdl_student_T q_rotpen_mdl_student_M_;
RT_MODEL_q_rotpen_mdl_student_T *const q_rotpen_mdl_student_M =
  &q_rotpen_mdl_student_M_;
real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  boolean_T yEq;
  real_T q;
  y = u0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    if (u1 != 0.0) {
      y = (rtNaN);
    }
  } else if (u0 == 0.0) {
    y = u1 * 0.0;
  } else {
    if (u1 != 0.0) {
      y = fmod(u0, u1);
      yEq = (y == 0.0);
      if ((!yEq) && (u1 > floor(u1))) {
        q = fabs(u0 / u1);
        yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
      }

      if (yEq) {
        y = u1 * 0.0;
      } else {
        if ((u0 < 0.0) != (u1 < 0.0)) {
          y += u1;
        }
      }
    }
  }

  return y;
}

/* Model output function */
void q_rotpen_mdl_student_output(void)
{
  /* local block i/o variables */
  real_T rtb_InverseAmplifierGainVV;
  real_T rtb_EncoderCalibrationradcount[2];
  real_T rtb_Sum;
  real_T tmp;

  /* S-Function (hil_read_encoder_block): '<S4>/HIL Read Encoder' */

  /* S-Function Block: q_rotpen_mdl_student/SRV02-ET+ROTPEN-E/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(q_rotpen_mdl_student_DW.HILInitialize_Card,
      q_rotpen_mdl_student_P.HILReadEncoder_channels, 2,
      &q_rotpen_mdl_student_DW.HILReadEncoder_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
    } else {
      rtb_EncoderCalibrationradcount[0] =
        q_rotpen_mdl_student_DW.HILReadEncoder_Buffer[0];
      rtb_EncoderCalibrationradcount[1] =
        q_rotpen_mdl_student_DW.HILReadEncoder_Buffer[1];
    }
  }

  /* Gain: '<S4>/Encoder Calibration  (rad//count)' */
  rtb_EncoderCalibrationradcount[0] *= q_rotpen_mdl_student_P.K_ENC;
  rtb_EncoderCalibrationradcount[1] *= q_rotpen_mdl_student_P.K_ENC;

  /* Math: '<S5>/Math Function' incorporates:
   *  Constant: '<S5>/Mod Angle  (rad)'
   */
  rtb_InverseAmplifierGainVV = rt_modd_snf(rtb_EncoderCalibrationradcount[1],
    q_rotpen_mdl_student_P.ModAnglerad_Value);

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/Offset Angle  (rad)'
   */
  rtb_Sum = rtb_InverseAmplifierGainVV +
    q_rotpen_mdl_student_P.OffsetAnglerad_Value;

  /* Constant: '<Root>/u (V)' */
  q_rotpen_mdl_student_B.uV = q_rotpen_mdl_student_P.uV_Value;

  /* Gain: '<S4>/Direction Convention: arm CCW when u>0' */
  rtb_InverseAmplifierGainVV =
    q_rotpen_mdl_student_P.DirectionConventionarmCCWwhenu0 *
    q_rotpen_mdl_student_B.uV;

  /* Saturate: '<S4>/Amplifier  Saturation (V)' */
  if (rtb_InverseAmplifierGainVV >
      q_rotpen_mdl_student_P.AmplifierSaturationV_UpperSat) {
    tmp = q_rotpen_mdl_student_P.AmplifierSaturationV_UpperSat;
  } else if (rtb_InverseAmplifierGainVV <
             q_rotpen_mdl_student_P.AmplifierSaturationV_LowerSat) {
    tmp = q_rotpen_mdl_student_P.AmplifierSaturationV_LowerSat;
  } else {
    tmp = rtb_InverseAmplifierGainVV;
  }

  /* End of Saturate: '<S4>/Amplifier  Saturation (V)' */

  /* Gain: '<S4>/Inverse Amplifier  Gain (V//V)' */
  rtb_InverseAmplifierGainVV = 1.0 / q_rotpen_mdl_student_P.K_AMP * tmp;

  /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

  /* S-Function Block: q_rotpen_mdl_student/SRV02-ET+ROTPEN-E/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(q_rotpen_mdl_student_DW.HILInitialize_Card,
      &q_rotpen_mdl_student_P.HILWriteAnalog_channels, 1,
      &rtb_InverseAmplifierGainVV);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S4>/HIL Write Digital' incorporates:
   *  Constant: '<S4>/Enable VoltPAQ-X2,X4'
   */

  /* S-Function Block: q_rotpen_mdl_student/SRV02-ET+ROTPEN-E/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[0] =
      (q_rotpen_mdl_student_P.EnableVoltPAQX2X4_Value[0] != 0);
    q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[1] =
      (q_rotpen_mdl_student_P.EnableVoltPAQX2X4_Value[1] != 0);
    q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[2] =
      (q_rotpen_mdl_student_P.EnableVoltPAQX2X4_Value[2] != 0);
    q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[3] =
      (q_rotpen_mdl_student_P.EnableVoltPAQX2X4_Value[3] != 0);
    result = hil_write_digital(q_rotpen_mdl_student_DW.HILInitialize_Card,
      q_rotpen_mdl_student_P.HILWriteDigital_channels, 4,
      &q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
    }
  }

  /* Gain: '<S3>/Gain' */
  q_rotpen_mdl_student_B.Gain = q_rotpen_mdl_student_P.Gain_Gain * rtb_Sum;

  /* Gain: '<S2>/Gain' */
  q_rotpen_mdl_student_B.Gain_k = q_rotpen_mdl_student_P.Gain_Gain_b *
    rtb_EncoderCalibrationradcount[0];
}

/* Model update function */
void q_rotpen_mdl_student_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++q_rotpen_mdl_student_M->Timing.clockTick0)) {
    ++q_rotpen_mdl_student_M->Timing.clockTickH0;
  }

  q_rotpen_mdl_student_M->Timing.t[0] =
    q_rotpen_mdl_student_M->Timing.clockTick0 *
    q_rotpen_mdl_student_M->Timing.stepSize0 +
    q_rotpen_mdl_student_M->Timing.clockTickH0 *
    q_rotpen_mdl_student_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void q_rotpen_mdl_student_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S4>/HIL Initialize' */

  /* S-Function Block: q_rotpen_mdl_student/SRV02-ET+ROTPEN-E/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &q_rotpen_mdl_student_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (q_rotpen_mdl_student_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
      return;
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_CKPStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(q_rotpen_mdl_student_DW.HILInitialize_Card,
        (t_clock *) q_rotpen_mdl_student_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) q_rotpen_mdl_student_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(q_rotpen_mdl_student_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
      return;
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_AIPStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &q_rotpen_mdl_student_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (q_rotpen_mdl_student_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &q_rotpen_mdl_student_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = q_rotpen_mdl_student_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_AIChannels, 8U,
         &q_rotpen_mdl_student_DW.HILInitialize_AIMinimums[0],
         &q_rotpen_mdl_student_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_AOPStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &q_rotpen_mdl_student_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (q_rotpen_mdl_student_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &q_rotpen_mdl_student_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = q_rotpen_mdl_student_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_AOChannels, 8U,
         &q_rotpen_mdl_student_DW.HILInitialize_AOMinimums[0],
         &q_rotpen_mdl_student_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_AOStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_mdl_student_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(q_rotpen_mdl_student_DW.HILInitialize_Card,
        q_rotpen_mdl_student_P.HILInitialize_AOChannels, 8U,
        &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if (q_rotpen_mdl_student_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_mdl_student_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_AOChannels, 8U,
         &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (q_rotpen_mdl_student_DW.HILInitialize_Card,
       q_rotpen_mdl_student_P.HILInitialize_DIChannels, 16U,
       q_rotpen_mdl_student_P.HILInitialize_DOChannels, 16U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
      return;
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_DOStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_rotpen_mdl_student_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 16; i1++) {
          dw_DOBits[i1] = q_rotpen_mdl_student_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(q_rotpen_mdl_student_DW.HILInitialize_Card,
        q_rotpen_mdl_student_P.HILInitialize_DOChannels, 16U, (t_boolean *)
        &q_rotpen_mdl_student_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if (q_rotpen_mdl_student_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &q_rotpen_mdl_student_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 16; i1++) {
          dw_DOStates[i1] = q_rotpen_mdl_student_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_DOChannels, 16U, (const
          t_digital_state *) &q_rotpen_mdl_student_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_EIPStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &q_rotpen_mdl_student_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            q_rotpen_mdl_student_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &q_rotpen_mdl_student_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &q_rotpen_mdl_student_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] =
            q_rotpen_mdl_student_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (q_rotpen_mdl_student_DW.HILInitialize_Card,
         q_rotpen_mdl_student_P.HILInitialize_EIChannels, 8U,
         &q_rotpen_mdl_student_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_EIStart && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &q_rotpen_mdl_student_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            q_rotpen_mdl_student_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(q_rotpen_mdl_student_DW.HILInitialize_Card,
        q_rotpen_mdl_student_P.HILInitialize_EIChannels, 8U,
        &q_rotpen_mdl_student_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        return;
      }
    }
  }
}

/* Model terminate function */
void q_rotpen_mdl_student_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S4>/HIL Initialize' */

  /* S-Function Block: q_rotpen_mdl_student/SRV02-ET+ROTPEN-E/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(q_rotpen_mdl_student_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_rotpen_mdl_student_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_rotpen_mdl_student_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_rotpen_mdl_student_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((q_rotpen_mdl_student_P.HILInitialize_DOTerminate && !is_switching) ||
        (q_rotpen_mdl_student_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_rotpen_mdl_student_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 16; i1++) {
          dw_DOBits[i1] = q_rotpen_mdl_student_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 16U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_rotpen_mdl_student_DW.HILInitialize_Card
                         , q_rotpen_mdl_student_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , q_rotpen_mdl_student_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &q_rotpen_mdl_student_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_rotpen_mdl_student_DW.HILInitialize_Card,
             q_rotpen_mdl_student_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (q_rotpen_mdl_student_DW.HILInitialize_Card,
             q_rotpen_mdl_student_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &q_rotpen_mdl_student_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_rotpen_mdl_student_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_rotpen_mdl_student_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_rotpen_mdl_student_DW.HILInitialize_Card);
    hil_close(q_rotpen_mdl_student_DW.HILInitialize_Card);
    q_rotpen_mdl_student_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  q_rotpen_mdl_student_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_rotpen_mdl_student_update();
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
  q_rotpen_mdl_student_initialize();
}

void MdlTerminate(void)
{
  q_rotpen_mdl_student_terminate();
}

/* Registration function */
RT_MODEL_q_rotpen_mdl_student_T *q_rotpen_mdl_student(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_rotpen_mdl_student_M, 0,
                sizeof(RT_MODEL_q_rotpen_mdl_student_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_rotpen_mdl_student_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    q_rotpen_mdl_student_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_rotpen_mdl_student_M->Timing.sampleTimes =
      (&q_rotpen_mdl_student_M->Timing.sampleTimesArray[0]);
    q_rotpen_mdl_student_M->Timing.offsetTimes =
      (&q_rotpen_mdl_student_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_rotpen_mdl_student_M->Timing.sampleTimes[0] = (0.002);

    /* task offsets */
    q_rotpen_mdl_student_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(q_rotpen_mdl_student_M, &q_rotpen_mdl_student_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_rotpen_mdl_student_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    q_rotpen_mdl_student_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_rotpen_mdl_student_M, -1);
  q_rotpen_mdl_student_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  q_rotpen_mdl_student_M->Sizes.checksums[0] = (1068545676U);
  q_rotpen_mdl_student_M->Sizes.checksums[1] = (2535232326U);
  q_rotpen_mdl_student_M->Sizes.checksums[2] = (3632313029U);
  q_rotpen_mdl_student_M->Sizes.checksums[3] = (977778930U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    q_rotpen_mdl_student_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_rotpen_mdl_student_M->extModeInfo,
      &q_rotpen_mdl_student_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_rotpen_mdl_student_M->extModeInfo,
                        q_rotpen_mdl_student_M->Sizes.checksums);
    rteiSetTPtr(q_rotpen_mdl_student_M->extModeInfo, rtmGetTPtr
                (q_rotpen_mdl_student_M));
  }

  q_rotpen_mdl_student_M->solverInfoPtr = (&q_rotpen_mdl_student_M->solverInfo);
  q_rotpen_mdl_student_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_rotpen_mdl_student_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_rotpen_mdl_student_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_rotpen_mdl_student_M->blockIO = ((void *) &q_rotpen_mdl_student_B);

  {
    q_rotpen_mdl_student_B.uV = 0.0;
    q_rotpen_mdl_student_B.Gain = 0.0;
    q_rotpen_mdl_student_B.Gain_k = 0.0;
  }

  /* parameters */
  q_rotpen_mdl_student_M->defaultParam = ((real_T *)&q_rotpen_mdl_student_P);

  /* states (dwork) */
  q_rotpen_mdl_student_M->dwork = ((void *) &q_rotpen_mdl_student_DW);
  (void) memset((void *)&q_rotpen_mdl_student_DW, 0,
                sizeof(DW_q_rotpen_mdl_student_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_rotpen_mdl_student_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_rotpen_mdl_student_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_rotpen_mdl_student_M->Sizes.numContStates = (0);/* Number of continuous states */
  q_rotpen_mdl_student_M->Sizes.numY = (0);/* Number of model outputs */
  q_rotpen_mdl_student_M->Sizes.numU = (0);/* Number of model inputs */
  q_rotpen_mdl_student_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_rotpen_mdl_student_M->Sizes.numSampTimes = (1);/* Number of sample times */
  q_rotpen_mdl_student_M->Sizes.numBlocks = (19);/* Number of blocks */
  q_rotpen_mdl_student_M->Sizes.numBlockIO = (3);/* Number of block outputs */
  q_rotpen_mdl_student_M->Sizes.numBlockPrms = (138);/* Sum of parameter "widths" */
  return q_rotpen_mdl_student_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
