////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    Finger.cpp
/// @brief   �����ֵ���ָ���Դ�ļ�    
/// 
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Finger.h"

void Finger::addKnuckle_back(Part* knuckle)
{
	KnuckleVector.push_back(knuckle);
	//ÿ����һ��ָ�ڣ���Ӧ������һ������̬����
	LastAttitude.push_back(osg::Vec3(1000,1000,1000));
}

Part* Finger::getKnuckleAt(unsigned int index)
{
	if(index < KnuckleVector.size())
		return KnuckleVector[index];
	else
		return NULL;
}

void Finger::makeFinger()
{
	if(KnuckleVector.size() == 1)
		return;

	for (unsigned int i=0; i <= KnuckleVector.size()-2; i++)
	{
		KnuckleVector[i]->addChild(KnuckleVector[i+1]);
	}
}

unsigned int Finger::numOfKnuckles()
{
	return KnuckleVector.size();
}

bool Finger::isFingerStopped()
{
	//���ܣ����μ����ָ�и���ָ���Ƿ��Ѿ�ֹͣ�˶�

	std::vector<bool> bStopped(numOfKnuckles(),true);

	//���±�־��ǰһ����̬
	for (unsigned int i=0; i<numOfKnuckles(); i++)
	{
		bStopped[i] = (getKnuckleAt(i)->getAttitude() == LastAttitude[i]);
		LastAttitude[i] = getKnuckleAt(i)->getAttitude();
	}

	//�������־
	for (unsigned int j=0; j<bStopped.size(); j++)
	{
		//ֻҪ��һ��false���ͷ���false
		if(bStopped[j] == false)
			return false;
	}

	return true;
}

void Finger::addHigherPriority(Finger* _finger)
{
	HigherPriority.push_back(_finger);
}

bool Finger::readyToMove()
{
	for (unsigned int i=0; i<HigherPriority.size(); i++)
	{
		if(HigherPriority[i]->isFingerStopped() == false)
			return false;
	}
	return true;
}