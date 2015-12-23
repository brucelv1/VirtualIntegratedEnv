////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    InfoStruct.h
/// @brief   ���ݽṹ��ͷ�ļ�    
/// 
/// ���ļ����������ɳ����жദʹ�õģ����ڴ�����Ϣ�����ݽṹ
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////
#ifndef _Delta_AssemblyInfoStruct_H_
#define _Delta_AssemblyInfoStruct_H_

#include <osg/Vec3>

struct AssemblyInfoStruct
{
	std::string name;              //�Բ���������
	std::string filename;          //Ҫ���صĲ�����ַ
	osg::Vec3 pos;                 //����λ��
	osg::Vec3 att;                 //������̬
	osg::Vec3 delta_att_perFrame;  //ÿ֡��̬�仯�������ڶ�����ʾ
};

struct SettingsInfoStruct
{
	std::string strategy;          //������
	unsigned int inputCOM;         //�����豸���ں�
	unsigned int outputCOM;        //����豸���ں�
};

struct CollisionInfoStruct
{
	std::string name;                //������
	unsigned long CollisionCategory; //��ײ���
	unsigned long CollisionCollides; //��ײĿ��
};
#endif //_Delta_AssemblyInfoStruct_H_