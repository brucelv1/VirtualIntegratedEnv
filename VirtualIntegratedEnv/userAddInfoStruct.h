////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    userAddInfoStruct.h
/// @brief   �û���Ӳ������ݽṹ��ͷ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _Delta_userAddInfoStruct_H_
#define _Delta_userAddInfoStruct_H_

/// @brief �洢����ӡ��Ի����еĸ�����Ϣ�Ľṹ��
/// @deprecated �汾�������벻Ҫʹ������ṹ�壬���ΪAssemblyInfoStruct
/// @see InfoStruct.h
struct userAddInfo
{
	std::string part;        ///< ������Աѡ��
	std::string name;        ///< �û��Բ�����������Ӣ��
	std::string filename;    ///< Ҫ���صĲ�����ַ
	float x,y,z;             ///< ����λ��
	float h,p,r;             ///< ������̬
};
#endif //_Delta_userAddInfoStruct_H_