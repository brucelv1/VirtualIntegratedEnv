////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_2x3PlaneFingers.h
/// @brief   �ⲿ���ݲ���-2��ָ��3ָ���ֵĿ����㷨�������ͷ�ļ�   
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/12
//////////////////////////////////////////////////////////////////////////

#ifndef _EDS_2x3PLANEFINGERS_H_
#define _EDS_2x3PLANEFINGERS_H_

#include "iexterndatastrategy.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class DataCollector
{
public:
	DataCollector() 
	{
		Reset();
	}

	~DataCollector() {}

	void Reset()
	{
		Angle = 0;
		ContactPos = osg::Vec3(0,0,0);
		ContactNorm = osg::Vec3(0,0,0);
	}

	double Angle;
	osg::Vec3 ContactPos;
	osg::Vec3 ContactNorm;
};

class StateCollector
{
public:
	StateCollector()
	{
		Reset();
	}
	~StateCollector() {}

	void Reset()
	{
		IsCollided = false;
		IsLimited = false;
	}

	bool IsCollided; // ������ײ
	bool IsLimited;  // ���Ｋ��
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class EDS_2x3PlaneFingers :
	public IExternDataStrategy
{
public:
	IMPLEMENT_EDS_CLONE(EDS_2x3PlaneFingers)
	
	EDS_2x3PlaneFingers(void);
	
	EDS_2x3PlaneFingers(const EDS_2x3PlaneFingers& copy);		

	virtual ~EDS_2x3PlaneFingers(void);

	virtual bool initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual void UpdateHand();

	virtual void OnMessage(MessageData* data);

private:
	std::vector<unsigned int> mFingerConfigInfo;
	std::vector< std::vector<DataCollector*> > mDataTable;
	std::vector< std::vector<StateCollector*> > mStateTable;
	Part* mGraspingObj;
	double mObjPosX;
	double mObjPosY;
	
	std::ofstream mOutputFile;

	void _updateData();
	void _makeDataZero();

	// �ж�������ָֹͣ�˶�
	bool _isStopped();
};

#endif //_EDS_2x3PLANEFINGERS_H_

