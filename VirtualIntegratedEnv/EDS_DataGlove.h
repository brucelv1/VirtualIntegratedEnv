////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_DataGlove.h
/// @brief   �ⲿ���ݲ���-���������������ͷ�ļ�    
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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

	//���ⲿ���õĽӿڣ�����������λ����̬����
	virtual void UpdateHand();

private:
	//dataGlove
	fdGlove *pGlove;

	//�ڹ��캯���д��������ף�������ָ���pGlove
	fdGlove* getDataGlovePtr();
};

#endif // _EDS_DATAGLOVE_H_

