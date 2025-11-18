//
// File: main.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 18-Nov-2025 16:53:22
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "main.h"
#include "FIRWithLeastSquares.h"
#include "FIRWithLeastSquares_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Declarations
static void argInit_1x4_real_T(double result[4]);
static int argInit_int32_T();
static double argInit_real_T();
static void main_FIRWithLeastSquares();

// Function Definitions
//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_1x4_real_T(double result[4])
{
  // Loop over the array to initialize each element.
  for (int idx1 = 0; idx1 < 4; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : int
//
static int argInit_int32_T()
{
  return 0;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_FIRWithLeastSquares()
{
  coder::array<double, 2U> h;
  double freq_tmp[4];

  // Initialize function 'FIRWithLeastSquares' input arguments.
  // Initialize function input argument 'freq'.
  argInit_1x4_real_T(freq_tmp);

  // Initialize function input argument 'amp'.
  // Call the entry-point 'FIRWithLeastSquares'.
  FIRWithLeastSquares(argInit_int32_T(), freq_tmp, freq_tmp, h);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. 
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_FIRWithLeastSquares();

  // Terminate the application.
  // You do not need to do this more than one time.
  FIRWithLeastSquares_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
