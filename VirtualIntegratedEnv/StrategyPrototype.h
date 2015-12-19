////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    StrategyPrototype.h
/// @brief   控制策略原型类的头文件    
///
/// 本文件用于注册新的策略原型，有扩展需求的用于可以按照本文件的格式注册自己
/// 编写的控制策略
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _STRATEGYPROTOTYPE_H_
#define _STRATEGYPROTOTYPE_H_

#include "CCS_EMGClassifierStr.h"
#include "CCS_Keyboard.h"
#include "EDS_DataGlove.h"
#include "EDS_MatlabBarrett.h"

class StrategyPrototype
{
public:
	static void RegisterStrategy();
};

void StrategyPrototype::RegisterStrategy()
{
	MAKE_CCS_PROTOTYPE(CCS_EMGClassifierStr)
	MAKE_CCS_PROTOTYPE(CCS_Keyboard)
	MAKE_EDS_PROTOTYPE(EDS_DataGlove)
	MAKE_EDS_PROTOTYPE(EDS_MatlabBarrett)
}

#endif //_STRATEGYPROTOTYPE_H_