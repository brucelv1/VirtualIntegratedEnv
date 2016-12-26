////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    ColorVisitor.h
/// @brief   �ڵ���ɫ���������ͷ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DELTA_NodeStructureTest_ColorVisitor
#define DELTA_NodeStructureTest_ColorVisitor 1

#include <osg/Node>
#include <osgDB/ReadFile>
#include <iostream>

class ColorVisitor :
	public osg::NodeVisitor
{
private:
	float _r;
	float _g;
	float _b;
	float _a;
public:
	ColorVisitor(void);

	virtual void apply(osg::Node& node);

	virtual void apply(osg::Geode& node);

	void setRGBA(float r, float g, float b, float a)
	{
		_r=r; _g=g; _b=b; _a=a;
	}
};
#endif // DELTA_NodeStructureTest_ColorVisitor