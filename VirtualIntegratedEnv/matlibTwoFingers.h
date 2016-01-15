//
// MATLAB Compiler: 5.2 (R2014b)
// Date: Tue Jan 12 19:02:54 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:matlibTwoFingers" "-T"
// "link:lib" "GetObjForce.m" 
//

#ifndef __matlibTwoFingers_h
#define __matlibTwoFingers_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_matlibTwoFingers
#define PUBLIC_matlibTwoFingers_C_API __global
#else
#define PUBLIC_matlibTwoFingers_C_API /* No import statement needed. */
#endif

#define LIB_matlibTwoFingers_C_API PUBLIC_matlibTwoFingers_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_matlibTwoFingers
#define PUBLIC_matlibTwoFingers_C_API __declspec(dllexport)
#else
#define PUBLIC_matlibTwoFingers_C_API __declspec(dllimport)
#endif

#define LIB_matlibTwoFingers_C_API PUBLIC_matlibTwoFingers_C_API


#else

#define LIB_matlibTwoFingers_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_matlibTwoFingers_C_API 
#define LIB_matlibTwoFingers_C_API /* No special import/export declaration */
#endif

extern LIB_matlibTwoFingers_C_API 
bool MW_CALL_CONV matlibTwoFingersInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_matlibTwoFingers_C_API 
bool MW_CALL_CONV matlibTwoFingersInitialize(void);

extern LIB_matlibTwoFingers_C_API 
void MW_CALL_CONV matlibTwoFingersTerminate(void);



extern LIB_matlibTwoFingers_C_API 
void MW_CALL_CONV matlibTwoFingersPrintStackTrace(void);

extern LIB_matlibTwoFingers_C_API 
bool MW_CALL_CONV mlxGetObjForce(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_matlibTwoFingers
#define PUBLIC_matlibTwoFingers_CPP_API __declspec(dllexport)
#else
#define PUBLIC_matlibTwoFingers_CPP_API __declspec(dllimport)
#endif

#define LIB_matlibTwoFingers_CPP_API PUBLIC_matlibTwoFingers_CPP_API

#else

#if !defined(LIB_matlibTwoFingers_CPP_API)
#if defined(LIB_matlibTwoFingers_C_API)
#define LIB_matlibTwoFingers_CPP_API LIB_matlibTwoFingers_C_API
#else
#define LIB_matlibTwoFingers_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_matlibTwoFingers_CPP_API void MW_CALL_CONV GetObjForce(int nargout, mwArray& F_result_X, mwArray& F_result_Y, const mwArray& Angle, const mwArray& ContactPos, const mwArray& P_norms);

#endif
#endif
