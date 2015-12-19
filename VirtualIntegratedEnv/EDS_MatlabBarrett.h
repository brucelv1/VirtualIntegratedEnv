////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_MatlabBarrett.h
/// @brief   �ⲿ���ݲ���-Barrett�ֵ�Matlab�����㷨�������ͷ�ļ�    
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _EDS_MATLABBARRETT_H_
#define _EDS_MATLABBARRETT_H_

#include "iexterndatastrategy.h"
#include "BarrettGrasp.h"

class EDS_MatlabBarrett :
	public IExternDataStrategy
{
public:
	IMPLEMENT_EDS_CLONE(EDS_MatlabBarrett)
	EDS_MatlabBarrett(void);
	EDS_MatlabBarrett(const EDS_MatlabBarrett& copy);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~EDS_MatlabBarrett(void);

	virtual void UpdateHand();

	virtual void OnMessage(MessageData* data);

protected:
	std::vector<bool> mFingerCollided;

	bool b_mLibLoaded;

	mwArray* mJointValues;
	mwArray* mEndMove;
	mwArray* mFingerMove;
	mwArray* mCalcuNum;
};

#endif //_EDS_MATLABBARRETT_H_

