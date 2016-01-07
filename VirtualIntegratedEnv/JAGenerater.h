//
// MATLAB Compiler: 5.2 (R2014b)
// Date: Thu Jan 07 16:24:32 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:JAGenerater" "-T" "link:lib"
// "joint_angle_generater" 
//

#ifndef __JAGenerater_h
#define __JAGenerater_h 1

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

#ifdef EXPORTING_JAGenerater
#define PUBLIC_JAGenerater_C_API __global
#else
#define PUBLIC_JAGenerater_C_API /* No import statement needed. */
#endif

#define LIB_JAGenerater_C_API PUBLIC_JAGenerater_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_JAGenerater
#define PUBLIC_JAGenerater_C_API __declspec(dllexport)
#else
#define PUBLIC_JAGenerater_C_API __declspec(dllimport)
#endif

#define LIB_JAGenerater_C_API PUBLIC_JAGenerater_C_API


#else

#define LIB_JAGenerater_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_JAGenerater_C_API 
#define LIB_JAGenerater_C_API /* No special import/export declaration */
#endif

extern LIB_JAGenerater_C_API 
bool MW_CALL_CONV JAGeneraterInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_JAGenerater_C_API 
bool MW_CALL_CONV JAGeneraterInitialize(void);

extern LIB_JAGenerater_C_API 
void MW_CALL_CONV JAGeneraterTerminate(void);



extern LIB_JAGenerater_C_API 
void MW_CALL_CONV JAGeneraterPrintStackTrace(void);

extern LIB_JAGenerater_C_API 
bool MW_CALL_CONV mlxJoint_angle_generater(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                           *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_JAGenerater
#define PUBLIC_JAGenerater_CPP_API __declspec(dllexport)
#else
#define PUBLIC_JAGenerater_CPP_API __declspec(dllimport)
#endif

#define LIB_JAGenerater_CPP_API PUBLIC_JAGenerater_CPP_API

#else

#if !defined(LIB_JAGenerater_CPP_API)
#if defined(LIB_JAGenerater_C_API)
#define LIB_JAGenerater_CPP_API LIB_JAGenerater_C_API
#else
#define LIB_JAGenerater_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_JAGenerater_CPP_API void MW_CALL_CONV joint_angle_generater(int nargout, mwArray& L_joint_angle, mwArray& R_joint_angle, mwArray& M_joint_angle, mwArray& I_joint_angle, mwArray& T_joint_angle, mwArray& d, const mwArray& d_in1);

#endif
#endif
