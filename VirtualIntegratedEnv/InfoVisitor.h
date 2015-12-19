////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    InfoVisitor.h
/// @brief   节点信息访问器类的头文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DELTA_NodeStructureTest_InfoVisitor
#define DELTA_NodeStructureTest_InfoVisitor 1

#include <osg/Node>
#include <osgDB/ReadFile>
#include <iostream>

class InfoVisitor :
	public osg::NodeVisitor
{
public:
	InfoVisitor(void);

	virtual void apply(osg::Node& node);

	virtual void apply(osg::Geode& node);

protected:
	int _indent;
};
#endif // DELTA_NodeStructureTest_InfoVisitor