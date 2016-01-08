////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_2x3PlaneFingers.h
/// @brief   外部数据策略-2手指、3指节手的控制算法数据类的头文件   
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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
	double mTheta[2][3];
	int    mCollided[2][3];
	int    mReachLimit[2][3];
	osg::Vec3 mContactPos[2][3];
	osg::Vec3 mContactNormal[2][3];
	
	Part* mGraspingObj;
	double mObjPosX;
	double mObjPosY;
	
	std::ofstream mOutputFile;

	void _updateData();
	void _makeDataZero();
	// 第一期：先用mCollided和mReachLimit来判断这一轮试验是否结束
	bool _isStopped();


	std::vector< std::vector<DataCollector*> > DataTable;
};

#endif //_EDS_2x3PLANEFINGERS_H_

