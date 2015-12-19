////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    InfoVisitor.h
/// @brief   �ڵ���Ϣ���������ͷ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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