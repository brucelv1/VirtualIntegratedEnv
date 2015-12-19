////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    Finger.h
/// @brief   �����ֵ���ָ���ͷ�ļ�    
/// 
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _VIE2_FINGER_H_
#define _VIE2_FINGER_H_

#include "Part.h"
#include <vector>
#include <string>

class Finger
{
public:
	Finger(const std::string& name = "Finger") 
	{
		mName = name;
	}
	~Finger() {}

	void addKnuckle_back(Part* knuckle);
	Part* getKnuckleAt(unsigned int index);

	//�������е���ָ�������������˳����ɸ���ӳ�䣬0��1�ĸ�������1��2�ĸ��������Դ�����
	void makeFinger();

	//������ָ�����е�ָ������unsigned int
	unsigned int numOfKnuckles();

	//�����ָ�����в����Ƿ�ֹͣ�˶�
	bool isFingerStopped();

	//��ӱ��Լ��˶����ȼ����ߵ���ָ����
	void addHigherPriority(Finger* _finger);

	//���������ȼ���ָ�Ƿ�ֹͣ�˶������Ƕ�ֹͣ�ˣ��Լ������˶�
	bool readyToMove();

private:
	std::string mName;
	std::vector<Part*> KnuckleVector;
	std::vector<Finger*> HigherPriority;
	//��Ŵ���ָ����ָ����һ֡����̬�������ж��Ƿ�ֹͣ�˶�
	std::vector<osg::Vec3> LastAttitude;

};

#endif // _VIE2_FINGER_H_