//
// File: UpsampleWithZero.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 19-Nov-2025 10:53:48
//

// Include Files
#include "UpsampleWithZero.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const coder::array<double, 1U> &x
//                double N
//                coder::array<double, 1U> &y
// Return Type  : void
//
void UpsampleWithZero(const coder::array<double, 1U> &x, double N, coder::array<
                      double, 1U> &y)
{
  int i;
  int loop_ub;
  y.set_size((static_cast<int>(static_cast<double>(x.size(0)) * N)));
  loop_ub = static_cast<int>(static_cast<double>(x.size(0)) * N);
  for (i = 0; i < loop_ub; i++) {
    y[i] = 0.0;
  }

  //  Perform the upsample
  if ((N == 0.0) || (((N > 0.0) && (1 > static_cast<int>(static_cast<double>
          (x.size(0)) * N))) || ((0.0 > N) && (static_cast<int>(static_cast<
          double>(x.size(0)) * N) > 1)))) {
    i = 1;
  } else {
    i = static_cast<int>(N);
  }

  loop_ub = x.size(0);
  for (int i1 = 0; i1 < loop_ub; i1++) {
    y[i * i1] = x[i1];
  }

  //  [EOF]
}

//
// File trailer for UpsampleWithZero.cpp
//
// [EOF]
//
