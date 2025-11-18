/*
 * File: _coder_FIRWithLeastSquares_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Nov-2025 16:53:22
 */

#ifndef _CODER_FIRWITHLEASTSQUARES_API_H
#define _CODER_FIRWITHLEASTSQUARES_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void FIRWithLeastSquares(int32_T N, real_T freq[4], real_T amp[4],
    emxArray_real_T *h);
  void FIRWithLeastSquares_api(const mxArray * const prhs[3], const mxArray
    *plhs[1]);
  void FIRWithLeastSquares_atexit(void);
  void FIRWithLeastSquares_initialize(void);
  void FIRWithLeastSquares_terminate(void);
  void FIRWithLeastSquares_xil_shutdown(void);
  void FIRWithLeastSquares_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_FIRWithLeastSquares_api.h
 *
 * [EOF]
 */
