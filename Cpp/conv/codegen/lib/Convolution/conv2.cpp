//
// File: conv2.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 19-Nov-2025 14:07:45
//

// Include Files
#include "conv2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                const ::coder::array<double, 1U> &b
//                ::coder::array<double, 1U> &c
// Return Type  : void
//
namespace coder
{
  void conv2NonSeparable(const ::coder::array<double, 1U> &a, const ::coder::
    array<double, 1U> &b, ::coder::array<double, 1U> &c)
  {
    int i;
    int ma;
    int mb;
    int mc;
    ma = a.size(0);
    mb = b.size(0) - 1;
    if ((a.size(0) == 0) || (b.size(0) == 0)) {
      mc = a.size(0) + b.size(0);
    } else {
      mc = (a.size(0) + b.size(0)) - 1;
    }

    c.set_size(mc);
    for (i = 0; i < mc; i++) {
      c[i] = 0.0;
    }

    if ((a.size(0) != 0) && (b.size(0) != 0) && (mc != 0)) {
      i = b.size(0) - 1;
      for (int ib = 0; ib <= i; ib++) {
        double bij;
        int ia;
        mc = mb - ib;
        bij = b[mc];
        ia = 0;
        for (int b_i = 0; b_i < ma; b_i++) {
          c[mc] = c[mc] + bij * a[ia];
          mc++;
          ia++;
        }
      }
    }
  }
}

//
// File trailer for conv2.cpp
//
// [EOF]
//
