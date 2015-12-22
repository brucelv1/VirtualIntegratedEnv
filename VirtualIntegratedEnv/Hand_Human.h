////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    Hand_Human.h
/// @brief   ���������ͷ�ļ�    
/// 
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef	VIE_HAND_HUMAN_H_
#define VIE_HAND_HUMAN_H_

#include "IHand.h"
#include "Finger.h"

class Hand_Human : public IHand
{
public:
	Hand_Human(float scale, const std::string& configFile);
	virtual ~Hand_Human();

	virtual int ConfigureHand();

protected:
	//��Ҫ��������ʵ�ֵķ�������������Ĺ��캯�������ε���
	//1������ӳ�䣺�����ص���������PartVector�е���ָ��ز���������������ӳ�䵽��ָ����FingersVector��
	virtual void Part_Node_Mapping();
	//2������Ҫ������ײ���Ĳ���������ײ��Χ��ӳ�䣬���Ǳ���ʵ��
	virtual void Part_Collision_Mapping();
	//3�����ӽڵ�ӳ��
	virtual void Parent_Child_Mapping();

	//ȷ����ָ���˶����ȼ������нϵ����ȼ�����ָ���ȴ�������ָ�˶����֮��ſ�ʼ����
	void setMotionPriority();
};

#endif // VIE_HAND_HUMAN_H_