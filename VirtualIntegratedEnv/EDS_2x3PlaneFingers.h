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
	void _updateData();
	void _makeDataZero();
};

#endif //_EDS_2x3PLANEFINGERS_H_

