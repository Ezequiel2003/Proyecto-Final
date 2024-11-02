/*
 * q_rotpen_mdl_student_dt.h
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
  { (char_T *)(&q_rotpen_mdl_student_B.uV), 0, 0, 3 }
  ,

  { (char_T *)(&q_rotpen_mdl_student_DW.HILInitialize_AIMinimums[0]), 0, 0, 48 },

  { (char_T *)(&q_rotpen_mdl_student_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&q_rotpen_mdl_student_DW.HILReadEncoder_PWORK), 11, 0, 6 },

  { (char_T *)(&q_rotpen_mdl_student_DW.HILInitialize_DOStates[0]), 6, 0, 34 },

  { (char_T *)(&q_rotpen_mdl_student_DW.HILInitialize_DOBits[0]), 8, 0, 16 },

  { (char_T *)(&q_rotpen_mdl_student_DW.HILWriteDigital_Buffer[0]), 15, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_rotpen_mdl_student_P.K_AMP), 0, 0, 2 },

  { (char_T *)(&q_rotpen_mdl_student_P.HILReadEncoder_channels[0]), 7, 0, 7 },

  { (char_T *)(&q_rotpen_mdl_student_P.HILInitialize_OOTerminate), 0, 0, 27 },

  { (char_T *)(&q_rotpen_mdl_student_P.HILInitialize_CKChannels[0]), 6, 0, 7 },

  { (char_T *)(&q_rotpen_mdl_student_P.HILInitialize_AIChannels[0]), 7, 0, 57 },

  { (char_T *)(&q_rotpen_mdl_student_P.HILInitialize_Active), 8, 0, 38 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  6U,
  rtPTransitions
};

/* [EOF] q_rotpen_mdl_student_dt.h */
