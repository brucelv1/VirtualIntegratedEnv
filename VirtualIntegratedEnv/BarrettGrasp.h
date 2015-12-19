////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    BarrettGrasp.h    
/// @brief   控制Barrett虚拟手的抓取算法文件  
///  
/// 本文件是由Matlab算法文件编译生成的，包含算法的使用接口 
/// MATLAB Compiler: 5.2 (R2014b)
/// Date: Thu May 28 15:43:51 2015
/// Arguments: "-B" "macro_default" "-W" "cpplib:BarrettGrasp" "-T" "link:lib"
/// "barrett_angle_generation.m" "barrett_cal_energy.m" 
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef __BarrettGrasp_h
#define __BarrettGrasp_h 1

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

#ifdef EXPORTING_BarrettGrasp
#define PUBLIC_BarrettGrasp_C_API __global
#else
#define PUBLIC_BarrettGrasp_C_API /* No import statement needed. */
#endif

#define LIB_BarrettGrasp_C_API PUBLIC_BarrettGrasp_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_BarrettGrasp
#define PUBLIC_BarrettGrasp_C_API __declspec(dllexport)
#else
#define PUBLIC_BarrettGrasp_C_API __declspec(dllimport)
#endif

#define LIB_BarrettGrasp_C_API PUBLIC_BarrettGrasp_C_API


#else

#define LIB_BarrettGrasp_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_BarrettGrasp_C_API 
#define LIB_BarrettGrasp_C_API /* No special import/export declaration */
#endif

extern LIB_BarrettGrasp_C_API 
bool MW_CALL_CONV BarrettGraspInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_BarrettGrasp_C_API 
bool MW_CALL_CONV BarrettGraspInitialize(void);

extern LIB_BarrettGrasp_C_API 
void MW_CALL_CONV BarrettGraspTerminate(void);



extern LIB_BarrettGrasp_C_API 
void MW_CALL_CONV BarrettGraspPrintStackTrace(void);

extern LIB_BarrettGrasp_C_API 
bool MW_CALL_CONV mlxBarrett_angle_generation(int nlhs, mxArray *plhs[], int nrhs, 
                                              mxArray *prhs[]);

extern LIB_BarrettGrasp_C_API 
bool MW_CALL_CONV mlxBarrett_cal_energy(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                        *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_BarrettGrasp
#define PUBLIC_BarrettGrasp_CPP_API __declspec(dllexport)
#else
#define PUBLIC_BarrettGrasp_CPP_API __declspec(dllimport)
#endif

#define LIB_BarrettGrasp_CPP_API PUBLIC_BarrettGrasp_CPP_API

#else

#if !defined(LIB_BarrettGrasp_CPP_API)
#if defined(LIB_BarrettGrasp_C_API)
#define LIB_BarrettGrasp_CPP_API LIB_BarrettGrasp_C_API
#else
#define LIB_BarrettGrasp_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_BarrettGrasp_CPP_API void MW_CALL_CONV barrett_angle_generation(int nargout, mwArray& Jonit_values, mwArray& end_move, mwArray& Num, const mwArray& finger_move, const mwArray& joint_values0, const mwArray& num);

extern LIB_BarrettGrasp_CPP_API void MW_CALL_CONV barrett_cal_energy(int nargout, mwArray& P_energy, const mwArray& joint_values, const mwArray& num);

#endif
#endif
