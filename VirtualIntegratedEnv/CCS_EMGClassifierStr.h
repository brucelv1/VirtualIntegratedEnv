////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    CCS_EMGClassifierStr.h
/// @brief   �����ַ�����-�����źŷ������������ͷ�ļ�    
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
////////////////////////////////////////////////////////////////////////// 

#ifndef _CCS_EMGCLASSIFIERSTR_H_
#define _CCS_EMGCLASSIFIERSTR_H_

#include "IControlCharStrategy.h"
#include "SerialPort.h"

class CCS_EMGClassifierStr
	: public IControlCharStrategy
{
public:
	/// for prototype purpose
	IMPLEMENT_CCS_CLONE(CCS_EMGClassifierStr)
	CCS_EMGClassifierStr();
	CCS_EMGClassifierStr(const CCS_EMGClassifierStr& copy);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~CCS_EMGClassifierStr();

	//�򿪴��ڣ����շ����������Ŀ����ַ�
	void openPortForClassifier(unsigned int nCOM);

	//�򿪴��ڣ���Ӳ���豸���Ϳ����ַ�
	void openPortForHardware(unsigned int nCOM);

	//��ָ��������
	virtual void doGesture();
	void extendAllFingers();

	//����������
	virtual void doWristAction();
	void recoverWrist();

	virtual void setCommandBits(std::bitset<5> bits);
	virtual void setWristActionType(int _type);

	//��ײ��Ӧ
	virtual void OnMessage(MessageData* data);

private:
	void updateCommand();
	CSerialPort* mClassifierPort;
	CSerialPort* mHardwarePort;

	bool b_mAllFingersRecoverd;
	bool b_mFingerActionFinished;
	bool b_mWristRecovered;
	bool b_mWristActionFinished;
	bool b_mNeedRecoverToLastFrameToAvoidCollisionDetect[5];

};

#endif