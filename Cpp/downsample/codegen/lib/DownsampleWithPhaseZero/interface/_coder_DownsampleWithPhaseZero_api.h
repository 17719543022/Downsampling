/*
 * File: _coder_DownsampleWithPhaseZero_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2025 15:22:02
 */

#ifndef _CODER_DOWNSAMPLEWITHPHASEZERO_API_H
#define _CODER_DOWNSAMPLEWITHPHASEZERO_API_H

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
  void DownsampleWithPhaseZero(emxArray_real_T *x, real_T N, emxArray_real_T *y);
  void DownsampleWithPhaseZero_api(const mxArray * const prhs[2], const mxArray *
    plhs[1]);
  void DownsampleWithPhaseZero_atexit(void);
  void DownsampleWithPhaseZero_initialize(void);
  void DownsampleWithPhaseZero_terminate(void);
  void DownsampleWithPhaseZero_xil_shutdown(void);
  void DownsampleWithPhaseZero_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_DownsampleWithPhaseZero_api.h
 *
 * [EOF]
 */
