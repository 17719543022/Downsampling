//
// File: FIRWithLeastSquares.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 19-Nov-2025 10:20:56
//

// Include Files
#include "FIRWithLeastSquares.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cfloat>
#include <cmath>

// Function Declarations
static int div_s32_floor(int numerator, int denominator);
static double rt_remd_snf(double u0, double u1);

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
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    double b_u1;
    if (u1 < 0.0) {
      b_u1 = std::ceil(u1);
    } else {
      b_u1 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      b_u1 = std::abs(u0 / u1);
      if (!(std::abs(b_u1 - std::floor(b_u1 + 0.5)) > DBL_EPSILON * b_u1)) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

//
// Cast to enforce precision rules N, F and A
// Arguments    : double N
//                const double freq[4]
//                const double amp[4]
//                coder::array<double, 2U> &h
// Return Type  : void
//
void FIRWithLeastSquares(double N, const double freq[4], const double amp[4],
  coder::array<double, 2U> &h)
{
  coder::array<double, 2U> m;
  coder::array<double, 1U> b;
  coder::array<double, 1U> k;
  coder::array<double, 1U> y;
  coder::array<double, 1U> y_tmp;
  double b0;
  double m_s;
  double max_freq;
  double min_freq;
  int i;
  int idx;
  int md2;
  boolean_T Nodd;
  boolean_T exitg1;

  //  validate ftype
  //  filter length
  N++;
  Nodd = rtIsNaN(freq[0]);
  if (!Nodd) {
    idx = 1;
  } else {
    idx = 0;
    md2 = 2;
    exitg1 = false;
    while ((!exitg1) && (md2 < 5)) {
      if (!rtIsNaN(freq[md2 - 1])) {
        idx = md2;
        exitg1 = true;
      } else {
        md2++;
      }
    }
  }

  if (idx == 0) {
    max_freq = freq[0];
  } else {
    max_freq = freq[idx - 1];
    i = idx + 1;
    for (md2 = i; md2 < 5; md2++) {
      m_s = freq[md2 - 1];
      if (max_freq < m_s) {
        max_freq = m_s;
      }
    }
  }

  if (!Nodd) {
    idx = 1;
  } else {
    idx = 0;
    md2 = 2;
    exitg1 = false;
    while ((!exitg1) && (md2 < 5)) {
      if (!rtIsNaN(freq[md2 - 1])) {
        idx = md2;
        exitg1 = true;
      } else {
        md2++;
      }
    }
  }

  if (idx == 0) {
    min_freq = freq[0];
  } else {
    min_freq = freq[idx - 1];
    i = idx + 1;
    for (md2 = i; md2 < 5; md2++) {
      m_s = freq[md2 - 1];
      if (min_freq > m_s) {
        min_freq = m_s;
      }
    }
  }

  //  check validity of input F and A
  if ((max_freq > 1.0) || (min_freq < 0.0)) {
    int loop_ub;
    h.set_size(1, (static_cast<int>(N)));
    loop_ub = static_cast<int>(N);
    for (i = 0; i < loop_ub; i++) {
      h[i] = 0.0;
    }
  } else {
    double F_idx_0;
    double F_idx_2;
    double F_idx_3;
    double L;
    double a;
    double b1;
    double b1_tmp;
    int b_loop_ub;
    int loop_ub;
    F_idx_0 = freq[0] / 2.0;
    min_freq = freq[1] / 2.0;
    F_idx_2 = freq[2] / 2.0;
    F_idx_3 = freq[3] / 2.0;

    //  find the order
    L = (N - 1.0) / 2.0;

    //  odd order
    Nodd = (rt_remd_snf(N, 2.0) == 1.0);

    //  initialize b0
    b0 = 0.0;

    //  Type I linear phase FIR
    //  Basis vectors are cos(2*pi*m*f)
    if (!Nodd) {
      if (rtIsNaN(L)) {
        m.set_size(1, 1);
        m[0] = rtNaN;
      } else if (L < 0.0) {
        m.set_size(1, 0);
      } else if (rtIsInf(L) && (0.0 == L)) {
        m.set_size(1, 1);
        m[0] = rtNaN;
      } else {
        loop_ub = static_cast<int>(std::floor(L));
        m.set_size(1, (loop_ub + 1));
        for (i = 0; i <= loop_ub; i++) {
          m[i] = i;
        }
      }

      i = m.size(0) * m.size(1);
      m.set_size(1, m.size(1));
      loop_ub = i - 1;
      for (i = 0; i <= loop_ub; i++) {
        m[i] = m[i] + 0.5;
      }

      //  type II
    } else {
      if (rtIsNaN(L)) {
        m.set_size(1, 1);
        m[0] = rtNaN;
      } else if (L < 0.0) {
        m.set_size(1, 0);
      } else if (rtIsInf(L) && (0.0 == L)) {
        m.set_size(1, 1);
        m[0] = rtNaN;
      } else {
        loop_ub = static_cast<int>(std::floor(L));
        m.set_size(1, (loop_ub + 1));
        for (i = 0; i <= loop_ub; i++) {
          m[i] = i;
        }
      }

      //  type I
    }

    k.set_size(m.size(1));
    loop_ub = m.size(1);
    for (i = 0; i < loop_ub; i++) {
      k[i] = m[i];
    }

    if (Nodd) {
      if (2 > k.size(0)) {
        i = 0;
        md2 = 0;
      } else {
        i = 1;
        md2 = k.size(0);
      }

      loop_ub = md2 - i;
      b.set_size(loop_ub);
      for (md2 = 0; md2 < loop_ub; md2++) {
        b[md2] = k[i + md2];
      }

      k.set_size(b.size(0));
      loop_ub = b.size(0);
      for (i = 0; i < loop_ub; i++) {
        k[i] = b[i];
      }

      //   first entry must be handled separately (where k(1)=0)
    }

    //  preallocate b matrix
    b.set_size(k.size(0));
    loop_ub = k.size(0);
    for (i = 0; i < loop_ub; i++) {
      b[i] = 0.0;
    }

    loop_ub = k.size(0);
    b_loop_ub = k.size(0);
    max_freq = min_freq - F_idx_0;
    m_s = (amp[1] - amp[0]) / max_freq;

    //   slope
    b1_tmp = m_s * F_idx_0;
    b1 = amp[0] - b1_tmp;

    //   y-intercept
    if (Nodd) {
      b0 = b1 * max_freq + m_s / 2.0 * (min_freq * min_freq - F_idx_0 * F_idx_0);
    }

    y_tmp.set_size(k.size(0));
    for (i = 0; i < loop_ub; i++) {
      y_tmp[i] = 6.2831853071795862 * k[i];
    }

    y.set_size(y_tmp.size(0));
    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y[i] = y_tmp[i] * min_freq;
    }

    idx = y.size(0);
    for (md2 = 0; md2 < idx; md2++) {
      y[md2] = std::cos(y[md2]);
    }

    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y_tmp[i] = y_tmp[i] * F_idx_0;
    }

    idx = y_tmp.size(0);
    for (md2 = 0; md2 < idx; md2++) {
      y_tmp[md2] = std::cos(y_tmp[md2]);
    }

    a = m_s / 39.478417604357432;
    idx = b.size(0);
    for (i = 0; i < idx; i++) {
      b[i] = b[i] + a * (y[i] - y_tmp[i]) / (k[i] * k[i]);
    }

    y_tmp.set_size(k.size(0));
    for (i = 0; i < b_loop_ub; i++) {
      y_tmp[i] = 2.0 * k[i];
    }

    y.set_size(y_tmp.size(0));
    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y[i] = y_tmp[i] * min_freq;
    }

    a = min_freq * (m_s * min_freq + b1);
    i = y.size(0);
    for (md2 = 0; md2 < i; md2++) {
      if (std::abs(y[md2]) < 1.0020841800044864E-292) {
        y[md2] = 1.0;
      } else {
        m_s = 3.1415926535897931 * y[md2];
        m_s = std::sin(m_s) / m_s;
        y[md2] = m_s;
      }
    }

    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y_tmp[i] = y_tmp[i] * F_idx_0;
    }

    max_freq = F_idx_0 * (b1_tmp + b1);
    i = y_tmp.size(0);
    for (md2 = 0; md2 < i; md2++) {
      if (std::abs(y_tmp[md2]) < 1.0020841800044864E-292) {
        y_tmp[md2] = 1.0;
      } else {
        m_s = 3.1415926535897931 * y_tmp[md2];
        m_s = std::sin(m_s) / m_s;
        y_tmp[md2] = m_s;
      }
    }

    idx = b.size(0);
    for (i = 0; i < idx; i++) {
      b[i] = b[i] + (a * y[i] - max_freq * y_tmp[i]);
    }

    max_freq = F_idx_3 - F_idx_2;
    m_s = (amp[3] - amp[2]) / max_freq;

    //   slope
    b1_tmp = m_s * F_idx_2;
    b1 = amp[2] - b1_tmp;

    //   y-intercept
    if (Nodd) {
      b0 += b1 * max_freq + m_s / 2.0 * (F_idx_3 * F_idx_3 - F_idx_2 * F_idx_2);
    }

    y_tmp.set_size(k.size(0));
    for (i = 0; i < loop_ub; i++) {
      y_tmp[i] = 6.2831853071795862 * k[i];
    }

    y.set_size(y_tmp.size(0));
    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y[i] = y_tmp[i] * F_idx_3;
    }

    idx = y.size(0);
    for (md2 = 0; md2 < idx; md2++) {
      y[md2] = std::cos(y[md2]);
    }

    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y_tmp[i] = y_tmp[i] * F_idx_2;
    }

    idx = y_tmp.size(0);
    for (md2 = 0; md2 < idx; md2++) {
      y_tmp[md2] = std::cos(y_tmp[md2]);
    }

    a = m_s / 39.478417604357432;
    idx = b.size(0);
    for (i = 0; i < idx; i++) {
      b[i] = b[i] + a * (y[i] - y_tmp[i]) / (k[i] * k[i]);
    }

    y_tmp.set_size(k.size(0));
    for (i = 0; i < b_loop_ub; i++) {
      y_tmp[i] = 2.0 * k[i];
    }

    y.set_size(y_tmp.size(0));
    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y[i] = y_tmp[i] * F_idx_3;
    }

    a = F_idx_3 * (m_s * F_idx_3 + b1);
    i = y.size(0);
    for (md2 = 0; md2 < i; md2++) {
      if (std::abs(y[md2]) < 1.0020841800044864E-292) {
        y[md2] = 1.0;
      } else {
        m_s = 3.1415926535897931 * y[md2];
        m_s = std::sin(m_s) / m_s;
        y[md2] = m_s;
      }
    }

    idx = y_tmp.size(0);
    for (i = 0; i < idx; i++) {
      y_tmp[i] = y_tmp[i] * F_idx_2;
    }

    max_freq = F_idx_2 * (b1_tmp + b1);
    i = y_tmp.size(0);
    for (md2 = 0; md2 < i; md2++) {
      if (std::abs(y_tmp[md2]) < 1.0020841800044864E-292) {
        y_tmp[md2] = 1.0;
      } else {
        m_s = 3.1415926535897931 * y_tmp[md2];
        m_s = std::sin(m_s) / m_s;
        y_tmp[md2] = m_s;
      }
    }

    idx = b.size(0);
    for (i = 0; i < idx; i++) {
      b[i] = b[i] + (a * y[i] - max_freq * y_tmp[i]);
    }

    if (Nodd) {
      k.set_size((b.size(0) + 1));
      k[0] = b0;
      loop_ub = b.size(0);
      for (i = 0; i < loop_ub; i++) {
        k[i + 1] = b[i];
      }

      b.set_size(k.size(0));
      loop_ub = k.size(0);
      for (i = 0; i < loop_ub; i++) {
        b[i] = k[i];
      }
    }

    loop_ub = b.size(0);
    for (i = 0; i < loop_ub; i++) {
      b[i] = 4.0 * b[i];
    }

    if (Nodd) {
      int b_i;
      int i1;
      b[0] = b[0] / 2.0;
      if (2.0 > L + 1.0) {
        i = 0;
        md2 = 1;
        b_i = -1;
        i1 = 0;
        idx = 0;
      } else {
        i = static_cast<int>(L + 1.0) - 1;
        md2 = -1;
        b_i = 1;
        i1 = 1;
        idx = static_cast<int>(L + 1.0);
      }

      loop_ub = div_s32_floor(b_i - i, md2);
      h.set_size(1, (((loop_ub + idx) - i1) + 2));
      for (b_i = 0; b_i <= loop_ub; b_i++) {
        h[b_i] = b[i + md2 * b_i] / 2.0;
      }

      h[loop_ub + 1] = b[0];
      b_loop_ub = idx - i1;
      for (i = 0; i < b_loop_ub; i++) {
        h[(i + loop_ub) + 2] = b[i1 + i] / 2.0;
      }
    } else {
      y_tmp.set_size(b.size(0));
      loop_ub = b.size(0);
      for (i = 0; i < loop_ub; i++) {
        y_tmp[i] = b[i];
      }

      idx = b.size(0) - 1;
      md2 = b.size(0) >> 1;
      for (int b_i = 0; b_i < md2; b_i++) {
        max_freq = y_tmp[b_i];
        b_loop_ub = idx - b_i;
        y_tmp[b_i] = y_tmp[b_loop_ub];
        y_tmp[b_loop_ub] = max_freq;
      }

      h.set_size(1, (y_tmp.size(0) + b.size(0)));
      loop_ub = y_tmp.size(0);
      for (i = 0; i < loop_ub; i++) {
        h[i] = 0.5 * y_tmp[i];
      }

      loop_ub = b.size(0);
      for (i = 0; i < loop_ub; i++) {
        h[i + y_tmp.size(0)] = 0.5 * b[i];
      }
    }
  }
}

//
// File trailer for FIRWithLeastSquares.cpp
//
// [EOF]
//
