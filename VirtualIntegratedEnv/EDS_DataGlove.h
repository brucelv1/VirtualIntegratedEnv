////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_DataGlove.h
/// @brief   外部数据策略-数据手套数据类的头文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef	_EDS_DATAGLOVE_H_
#define _EDS_DATAGLOVE_H_

#include "IExternDataStrategy.h"
#include "fglove.h"


class EDS_DataGlove :
	public IExternDataStrategy
{
public:
	IMPLEMENT_EDS_CLONE(EDS_DataGlove)
	EDS_DataGlove();
	EDS_DataGlove(const EDS_DataGlove& _DG);
	virtual bool initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~EDS_DataGlove(void);

	//供外部调用的接口，更新虚拟手位置姿态数据
	virtual void UpdateHand();

private:
	//dataGlove
	fdGlove *pGlove;

	//在构造函数中打开数据手套，并返回指针给pGlove
	fdGlove* getDataGlovePtr();
};

#endif // _EDS_DATAGLOVE_H_

