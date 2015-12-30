////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Finger.cpp
/// @brief   虚拟手的手指类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Finger.h"

void Finger::addKnuckle_back(Part* knuckle)
{
	KnuckleVector.push_back(knuckle);
	//每增加一个指节，对应地增加一个旧姿态向量
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
	//功能：依次检查手指中各个指节是否都已经停止运动

	std::vector<bool> bStopped(numOfKnuckles(),true);

	//更新标志和前一个姿态
	for (unsigned int i=0; i<numOfKnuckles(); i++)
	{
		bStopped[i] = (getKnuckleAt(i)->getAttitude() == LastAttitude[i]);
		LastAttitude[i] = getKnuckleAt(i)->getAttitude();
	}

	//逐个检查标志
	for (unsigned int j=0; j<bStopped.size(); j++)
	{
		//只要有一个false，就返回false
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