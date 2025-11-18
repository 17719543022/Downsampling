/*
 * File: _coder_RationalApproximation_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 17-Nov-2025 15:40:00
 */

#ifndef _CODER_RATIONALAPPROXIMATION_API_H
#define _CODER_RATIONALAPPROXIMATION_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void RationalApproximation(real_T X, real_T tol, real_T *N, real_T *D);
  void RationalApproximation_api(const mxArray * const prhs[2], int32_T nlhs,
    const mxArray *plhs[2]);
  void RationalApproximation_atexit(void);
  void RationalApproximation_initialize(void);
  void RationalApproximation_terminate(void);
  void RationalApproximation_xil_shutdown(void);
  void RationalApproximation_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_RationalApproximation_api.h
 *
 * [EOF]
 */
