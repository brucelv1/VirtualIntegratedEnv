////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    IHand.h
/// @brief   �����ֳ�������ͷ�ļ�    
/// 
/// ���ļ������������ֳ�����࣬��������ӿں���������̳еĽӿ�
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _IHAND_H_
#define _IHAND_H_

//odeҪ��ָ��dSINGLE��dDOUBLE
#ifndef dSINGLE
#define dSINGLE
#endif

#include <iostream>
#include <vector>
#include "Part.h"
#include "ReadAsmTxt.h"
#include "Finger.h"

class IHand
{
public:
	IHand(float scale, const std::string& configFile);
	virtual ~IHand();

	// ����ֵ����ù������������������д�ú���������Ҫ���ʼ�������������
	virtual int ConfigureHand();

	Part* getHandRoot() const;

	std::vector<Finger*> FingersVector;
	Finger* getFingerFromVector(unsigned int index);

	float getHandScale() {return mScale;}

	void getFingerConfigInfo(std::vector<int>& FCI);

	void initPartPtr();
	Part* mRoot; //ֻ��ʼ����λ�ˣ�������ģ�ͣ�ר��������������֪��������ɫ�Ȼ᲻�����
	Part* mArm;
	Part* mPostWrist;
	Part* mWrist;
	Part* mPalm;

protected:
	//��Ҫ��������ʵ�ֵķ�������������Ĺ��캯�������ε���
	//1������ӳ�䣺�����ص���������PartVector�е���ָ��ز���������������ӳ�䵽��ָ����FingersVector��
	virtual void Part_Node_Mapping()=0;
	//2������Ҫ������ײ���Ĳ���������ײ��Χ��ӳ�䣬���Ǳ���ʵ��
	virtual void Part_Collision_Mapping() {}
	//3�����ӽڵ�ӳ��
	virtual void Parent_Child_Mapping()=0;

	Part* getPartFromVector(const std::string& partName);

	ReadAsmTxt* mAsmInfo;
	std::vector<int> mFingerConfigInfo;

private:
	std::vector<Part*> PartVector;
	float mScale;
	std::string mConfigFile;

	void configPart(Part* thisPart, AssemblyInfoStruct & ais, Part* parent = NULL);

	bool LoadPartToVector();
};

#endif // _IHAND_H_