////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    IExternDataStrategy.cpp
/// @brief   �ⲿ���ݲ��Գ�������Դ�ļ�    
/// 
/// ���ļ�ʵ�����ⲿ���ݳ�����Ĺ�������
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "IExternDataStrategy.h"
#include <iostream>

std::vector<std::string> IExternDataStrategy::EDSNameList;
std::vector<IExternDataStrategy*> IExternDataStrategy::EDSObjectList;

IExternDataStrategy* IExternDataStrategy::addEDSPrototype( std::string _name, IExternDataStrategy* ied )
{
	std::cout << "adding EDS prototype for " << _name << std::endl;
	EDSNameList.push_back(_name);
	EDSObjectList.push_back(ied);
	std::cout << "done\n";
	return ied;
}

IExternDataStrategy* IExternDataStrategy::makeEDSProduct( std::string _name )
{
	IExternDataStrategy* ie;
	unsigned int EDS_id=0;
	for (EDS_id; EDS_id<EDSNameList.size(); EDS_id++)
	{
		if (EDSNameList[EDS_id] == _name)
		{
			ie = EDSObjectList[EDS_id];
			return ie->clone();
		}
	}

	// if not found
	std::cout << "Cannot find the EDS prototype: " << _name.c_str() << std::endl;
	return NULL;
}
