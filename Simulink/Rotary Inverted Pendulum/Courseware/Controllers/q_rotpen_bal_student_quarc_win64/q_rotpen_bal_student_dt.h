/*
 * q_rotpen_bal_student_dt.h
 *
 * Code generation for model "q_rotpen_bal_student".
 *
 * Model version              : 1.395
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Thu Nov 16 09:31:37 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card),
  sizeof(t_boolean)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card",
  "t_boolean"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&q_rotpen_bal_student_B.EncoderCalibrationradcount[0]), 0, 0, 8 },

  { (char_T *)(&q_rotpen_bal_student_B.Compare), 3, 0, 1 }
  ,

  { (char_T *)(&q_rotpen_bal_student_DW.HILInitialize_AIMinimums[0]), 0, 0, 64 },

  { (char_T *)(&q_rotpen_bal_student_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&q_rotpen_bal_student_DW.HILReadEncoder_PWORK), 11, 0, 6 },

  { (char_T *)(&q_rotpen_bal_student_DW.HILInitialize_ClockModes[0]), 6, 0, 53 },

  { (char_T *)(&q_rotpen_bal_student_DW.HILInitialize_POSortedChans[0]), 7, 0, 8
  },

  { (char_T *)(&q_rotpen_bal_student_DW.HILInitialize_DOBits[0]), 8, 0, 8 },

  { (char_T *)(&q_rotpen_bal_student_DW.HILWriteDigital_Buffer[0]), 15, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_rotpen_bal_student_P.K[0]), 0, 0, 7 },

  { (char_T *)(&q_rotpen_bal_student_P.HILReadEncoder_channels[0]), 7, 0, 7 },

  { (char_T *)(&q_rotpen_bal_student_P.HILInitialize_OOTerminate), 0, 0, 43 },

  { (char_T *)(&q_rotpen_bal_student_P.HILInitialize_CKChannels[0]), 6, 0, 9 },

  { (char_T *)(&q_rotpen_bal_student_P.HILInitialize_AIChannels[0]), 7, 0, 41 },

  { (char_T *)(&q_rotpen_bal_student_P.HILInitialize_Active), 8, 0, 38 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  6U,
  rtPTransitions
};

/* [EOF] q_rotpen_bal_student_dt.h */
