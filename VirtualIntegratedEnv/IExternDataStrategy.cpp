////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IExternDataStrategy.cpp
/// @brief   外部数据策略抽象基类的源文件    
/// 
/// 本文件实现了外部数据抽象类的公共方法
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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
