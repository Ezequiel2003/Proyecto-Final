/*
 * q_rotpen_bal_student00_data.c
 *
 * Code generation for model "q_rotpen_bal_student00".
 *
 * Model version              : 1.366
 * Simulink Coder version : 8.2 (R2012a) 29-Dec-2011
 * C source code generated on : Tue Nov 15 09:44:50 2016
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "q_rotpen_bal_student00.h"
#include "q_rotpen_bal_student00_private.h"

/* Block parameters (auto storage) */
Parameters_q_rotpen_bal_student q_rotpen_bal_student00_P = {
  /*  Expression:  K
   * Referenced by: '<Root>/Control  Gain'
   */
  { -5.2611594041473984, 28.156796760038027, -2.7575720928684229,
    3.219026488196238 },
  0.0,                                 /* Expression: set_other_outputs_at_start
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: set_other_outputs_at_switch_in
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: set_other_outputs_at_terminate
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: set_other_outputs_at_switch_out
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  10.0,                                /* Expression: analog_input_maximums
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  -10.0,                               /* Expression: analog_input_minimums
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  10.0,                                /* Expression: analog_output_maximums
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  -10.0,                               /* Expression: analog_output_minimums
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: initial_analog_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: final_analog_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: watchdog_analog_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  24305.934065934067,                  /* Expression: pwm_frequency
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: pwm_leading_deadband
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: pwm_trailing_deadband
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: initial_pwm_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: final_pwm_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: watchdog_pwm_outputs
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0.0015339807878856412,               /* Expression: K_ENC
                                        * Referenced by: '<S5>/Encoder Calibration  (rad//count)'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S7>/Mod Angle  (rad)'
                                        */
  -3.1415926535897931,                 /* Expression: -pi
                                        * Referenced by: '<S7>/Offset Angle  (rad)'
                                        */
  0.20943951023931953,                 /* Expression: const
                                        * Referenced by: '<S2>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/u = 0V'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  0.1,                                 /* Expression: 0.1
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<Root>/Amplitude (deg)'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S1>/Gain1'
                                        */

  /*  Expression: [1,0,0,0]
   * Referenced by: '<Root>/Convert to  Vector State'
   */
  { 1.0, 0.0, 0.0, 0.0 },
  -62.831853071795862,                 /* Computed Parameter: HPFtheta_dotrads_A
                                        * Referenced by: '<S3>/HPF: theta_dot (rad//s)'
                                        */
  -3947.8417604357433,                 /* Computed Parameter: HPFtheta_dotrads_C
                                        * Referenced by: '<S3>/HPF: theta_dot (rad//s)'
                                        */
  62.831853071795862,                  /* Computed Parameter: HPFtheta_dotrads_D
                                        * Referenced by: '<S3>/HPF: theta_dot (rad//s)'
                                        */
  -62.831853071795862,                 /* Computed Parameter: HPFalpha_dotrads_A
                                        * Referenced by: '<S3>/HPF: alpha_dot (rad//s)'
                                        */
  -3947.8417604357433,                 /* Computed Parameter: HPFalpha_dotrads_C
                                        * Referenced by: '<S3>/HPF: alpha_dot (rad//s)'
                                        */
  62.831853071795862,                  /* Computed Parameter: HPFalpha_dotrads_D
                                        * Referenced by: '<S3>/HPF: alpha_dot (rad//s)'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S5>/Direction Convention: (Right-Hand) system'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S5>/Amplifier  Saturation (V)'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<S5>/Amplifier  Saturation (V)'
                                        */
  1.0,                                 /* Expression: 1/K_AMP
                                        * Referenced by: '<S5>/Inverse Amplifier  Gain (V//V)'
                                        */

  /*  Expression: [1 1 1 1]
   * Referenced by: '<S5>/Enable VoltPAQ-X2,X4'
   */
  { 1.0, 1.0, 1.0, 1.0 },
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<S8>/Gain'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<S9>/Gain'
                                        */

  /*  Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0, 1, 2 },
  0,                                   /* Computed Parameter: HILInitialize_DOWatchdog
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_EIInitial
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POModes
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POConfiguration
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POAlignment
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_POPolarity
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */

  /*  Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Computed Parameter: HILInitialize_DOChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },
  4U,                                  /* Computed Parameter: HILInitialize_EIQuadrature
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */

  /*  Computed Parameter: HILInitialize_POChannels
   * Referenced by: '<S5>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Computed Parameter: HILReadEncoder_Channels
   * Referenced by: '<S5>/HIL Read Encoder'
   */
  { 0U, 1U },
  0U,                                  /* Computed Parameter: HILWriteAnalog_Channels
                                        * Referenced by: '<S5>/HIL Write Analog'
                                        */

  /*  Computed Parameter: HILWriteDigital_Channels
   * Referenced by: '<S5>/HIL Write Digital'
   */
  { 0U, 1U, 2U, 3U },
  0,                                   /* Computed Parameter: HILInitialize_Active
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_CKPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_CKPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_CKStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_CKEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_AIPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_AIPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_AOPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_AOPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_AOStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_AOEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_AOTerminate
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_AOExit
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_AOReset
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_DOStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_DOTerminate
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOExit
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOReset
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_EIPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_EIPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_EIStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_EIEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_POPStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POPEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_POStart
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POEnter
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILInitialize_POTerminate
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POExit
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_POReset
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_OOReset
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOInitial
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  0,                                   /* Computed Parameter: HILInitialize_DOFinal
                                        * Referenced by: '<S5>/HIL Initialize'
                                        */
  1,                                   /* Computed Parameter: HILReadEncoder_Active
                                        * Referenced by: '<S5>/HIL Read Encoder'
                                        */
  0,                                   /* Computed Parameter: HILWriteAnalog_Active
                                        * Referenced by: '<S5>/HIL Write Analog'
                                        */
  0                                    /* Computed Parameter: HILWriteDigital_Active
                                        * Referenced by: '<S5>/HIL Write Digital'
                                        */
};
