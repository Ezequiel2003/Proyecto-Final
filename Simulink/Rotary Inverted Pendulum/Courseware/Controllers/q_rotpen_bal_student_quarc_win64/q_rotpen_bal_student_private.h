/*
 * q_rotpen_bal_student_private.h
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

#ifndef RTW_HEADER_q_rotpen_bal_student_private_h_
#define RTW_HEADER_q_rotpen_bal_student_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"

/* A global buffer for storing error messages (defined in quanser_common library) */
EXTERN char _rt_error_message[512];
extern real_T rt_modd_snf(real_T u0, real_T u1);

/* private model entry point functions */
extern void q_rotpen_bal_student_derivatives(void);

#endif                                 /* RTW_HEADER_q_rotpen_bal_student_private_h_ */
