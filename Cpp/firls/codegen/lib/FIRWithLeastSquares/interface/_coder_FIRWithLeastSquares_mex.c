/*
 * File: _coder_FIRWithLeastSquares_mex.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Nov-2025 16:53:22
 */

/* Include Files */
#include "_coder_FIRWithLeastSquares_mex.h"
#include "_coder_FIRWithLeastSquares_api.h"

/* Function Definitions */
/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void FIRWithLeastSquares_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[3])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  const mxArray *outputs[1];
  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        19, "FIRWithLeastSquares");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 19,
                        "FIRWithLeastSquares");
  }

  /* Call the function. */
  FIRWithLeastSquares_api(prhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&FIRWithLeastSquares_atexit);

  /* Module initialization. */
  FIRWithLeastSquares_initialize();
  try {
    emlrtShouldCleanupOnError(emlrtRootTLSGlobal, false);

    /* Dispatch the entry-point. */
    FIRWithLeastSquares_mexFunction(nlhs, plhs, nrhs, prhs);

    /* Module termination. */
    FIRWithLeastSquares_terminate();
  } catch (...) {
    emlrtCleanupOnException(emlrtRootTLSGlobal);
    throw;
  }
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_FIRWithLeastSquares_mex.c
 *
 * [EOF]
 */
