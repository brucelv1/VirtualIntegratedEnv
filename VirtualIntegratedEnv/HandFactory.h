////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    HandFactory.h
/// @brief   �����ֹ������ͷ�ļ�    
/// 
/// ��̬����createHand�������ɸ���������
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _VIE_HANDFACTORY_H_
#define _VIE_HANDFACTORY_H_

#include <string>
#include "IHand.h"
#include "Hand_SJT_6.h"
#include "Hand_SJT_3.h"
#include "Hand_Barrett.h"
#include "Hand_Human.h"
#include "Hand_Custom.h"

class HandFactory
{
public:
	static IHand* createHand(const std::string& _name, float _scale, const std::string& _filePath="")
	{
		if (_name == "SJT_3")
			return new Hand_SJT_3(_scale, "SJT3AsmInfo.txt");
		if (_name == "SJT_6")
			return new Hand_SJT_6(_scale, "SJT6AsmInfo.txt");
		if (_name == "Barrett")
			return new Hand_Barrett(_scale/100, "BarrettAsmInfo.txt");
		if (_name == "HumanHand")
			return new Hand_Human(_scale/10, "HumanAsmInfo.txt");
		if (_name == "UserCustom")
			return new Hand_Custom(_scale/100, _filePath);
		
		return NULL;
	}
};

#endif //_VIE_HANDFACTORY_H_