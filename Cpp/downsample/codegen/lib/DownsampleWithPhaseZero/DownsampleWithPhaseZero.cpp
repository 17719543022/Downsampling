//
// File: DownsampleWithPhaseZero.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 19-Nov-2025 15:22:02
//

// Include Files
#include "DownsampleWithPhaseZero.h"
#include "coder_array.h"

// Function Declarations
static int div_s32_floor(int numerator, int denominator);

// Function Definitions
//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_floor(int numerator, int denominator)
{
  unsigned int absNumerator;
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int absDenominator;
    unsigned int tempAbsQuotient;
    boolean_T quotientNeedsNegation;
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

//
// Arguments    : const coder::array<double, 1U> &x
//                double N
//                coder::array<double, 2U> &y
// Return Type  : void
//
void DownsampleWithPhaseZero(const coder::array<double, 1U> &x, double N, coder::
  array<double, 2U> &y)
{
  int i;
  int i1;
  int loop_ub;
  unsigned int sizeX_idx_0;

  //  Downsample on the leading non-singleton dimension
  if ((N == 0.0) || (((N > 0.0) && (1 > x.size(0))) || ((0.0 > N) && (x.size(0) >
         1)))) {
    i = 1;
    i1 = 0;
  } else {
    i = static_cast<int>(N);
    i1 = x.size(0);
  }

  //  Update the new downsampled dimension
  sizeX_idx_0 = static_cast<unsigned int>(div_s32_floor(i1 - 1, i) + 1);

  //  Restore to the original N-D dimensions
  y.set_size((static_cast<int>(sizeX_idx_0)), 1);
  loop_ub = static_cast<int>(sizeX_idx_0);
  for (i1 = 0; i1 < loop_ub; i1++) {
    y[i1] = x[i * i1];
  }

  //  [EOF]
  //  LocalWords:  downsamples th lockdown downsampled
}

//
// File trailer for DownsampleWithPhaseZero.cpp
//
// [EOF]
//
