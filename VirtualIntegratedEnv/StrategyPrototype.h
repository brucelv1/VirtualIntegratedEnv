////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    StrategyPrototype.h
/// @brief   ���Ʋ���ԭ�����ͷ�ļ�    
///
/// ���ļ�����ע���µĲ���ԭ�ͣ�����չ��������ڿ��԰��ձ��ļ��ĸ�ʽע���Լ�
/// ��д�Ŀ��Ʋ���
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _STRATEGYPROTOTYPE_H_
#define _STRATEGYPROTOTYPE_H_

#include "CCS_EMGClassifierStr.h"
#include "CCS_Keyboard.h"
#include "EDS_DataGlove.h"
#include "EDS_MatlabBarrett.h"
#include "EDS_GraspRegionAnalysis.h"
#include "EDS_MatlabYangFan.h"

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
	MAKE_EDS_PROTOTYPE(EDS_GraspRegionAnalysis)
	MAKE_EDS_PROTOTYPE(EDS_MatlabYangFan)
}

#endif //_STRATEGYPROTOTYPE_H_