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
	static IHand* createHand(const std::string& _name, float _scale, const std::string& _filePath, bool useCollision=true)
	{
		IHand* hand = NULL;

		if (_name == "SJT_3")
			hand = new Hand_SJT_3(_name, _scale, _filePath, useCollision);
		if (_name == "SJT_6")
			hand = new Hand_SJT_6(_name, _scale, _filePath, useCollision);
		if (_name == "Barrett")
			hand = new Hand_Barrett(_name, _scale/100, _filePath, useCollision);
		if (_name == "HumanHand")
			hand = new Hand_Human(_name, _scale/10, _filePath, useCollision);
		if (_name == "UserCustom")
			hand = new Hand_Custom(_name, _scale/100, _filePath, useCollision);

		if(1 == hand->ConfigureHand())
			return hand;

		return NULL;
	}
};

#endif //_VIE_HANDFACTORY_H_