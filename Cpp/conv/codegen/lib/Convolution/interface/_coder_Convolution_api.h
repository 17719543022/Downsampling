/*
 * File: _coder_Convolution_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2025 14:07:45
 */

#ifndef _CODER_CONVOLUTION_API_H
#define _CODER_CONVOLUTION_API_H

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
  void Convolution(emxArray_real_T *a, emxArray_real_T *b, emxArray_real_T *c);
  void Convolution_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
  void Convolution_atexit(void);
  void Convolution_initialize(void);
  void Convolution_terminate(void);
  void Convolution_xil_shutdown(void);
  void Convolution_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_Convolution_api.h
 *
 * [EOF]
 */
