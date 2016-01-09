////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_GraspRegionAnalysis.h
/// @brief   �ⲿ���ݲ���-2��ָ��3ָ���ֵĿ����㷨�������ͷ�ļ�   
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/12
//////////////////////////////////////////////////////////////////////////

#ifndef _EDS_GRASP_REGION_H_
#define _EDS_GRASP_REGION_H_

#include "iexterndatastrategy.h"
#include <fstream>
#include <queue>

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
		Angle = osg::Vec3(0,0,0);
		ContactPos = osg::Vec3(0,0,0);
		ContactNorm = osg::Vec3(0,0,0);
	}

	osg::Vec3 Angle;
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
class EDS_GraspRegionAnalysis :
	public IExternDataStrategy
{
public:
	IMPLEMENT_EDS_CLONE(EDS_GraspRegionAnalysis)
	
	EDS_GraspRegionAnalysis(void);
	
	EDS_GraspRegionAnalysis(const EDS_GraspRegionAnalysis& copy);		

	virtual ~EDS_GraspRegionAnalysis(void);

	virtual bool initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual void UpdateHand();

	virtual void OnMessage(MessageData* data);

private:
	std::vector<unsigned int> mFingerConfigInfo;
	std::vector< std::vector<DataCollector*> > mDataTable;
	std::vector< std::vector<StateCollector*> > mStateTable;
	std::queue< osg::Vec3 > mTestPointList;

	Part* mGraspingObj;
    osg::Vec3 mObjPos;
	
	std::ofstream mOutputFile;

	void _updateData();
	void _makeDataZero();

	// �ж�������ָֹͣ�˶�
	bool _isStopped();

	void _fillTestPointList(double xLow, double xDomain, double xInc, 
							double yLow, double yDomain, double yInc, 
							double zLow, double zDomain, double zInc);
};

#endif //_EDS_GRASP_REGION_H_

