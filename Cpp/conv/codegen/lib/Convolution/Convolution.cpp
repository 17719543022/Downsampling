//
// File: Convolution.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 19-Nov-2025 14:07:45
//

// Include Files
#include "Convolution.h"
#include "conv2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const coder::array<double, 1U> &a
//                const coder::array<double, 1U> &b
//                coder::array<double, 1U> &c
// Return Type  : void
//
void Convolution(const coder::array<double, 1U> &a, const coder::array<double,
                 1U> &b, coder::array<double, 1U> &c)
{
  //  compute as if both inputs are column vectors
  //  c = conv2(a(:),b(:),shape);
  if ((a.size(0) == 1) && (b.size(0) == 1)) {
    c.set_size(1);
    c[0] = b[0] * a[0];
  } else if (b.size(0) > a.size(0)) {
    coder::conv2NonSeparable(b, a, c);
  } else {
    coder::conv2NonSeparable(a, b, c);
  }

  //  restore orientation
  //  if shape(1) == 'f' || shape(1) == 'F'  %  shape 'full'
  //      if length(a) > length(b)
  //          if size(a,1) == 1 %row vector
  //              c = c.';
  //          end
  //      else
  //          if size(b,1) == 1 %row vector
  //              c = c.';
  //          end
  //      end
  //  else
  //      if size(a,1) == 1 %row vector
  //          c = c.';
  //      end
  //  end
}

//
// File trailer for Convolution.cpp
//
// [EOF]
//
