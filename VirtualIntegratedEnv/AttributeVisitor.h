////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    AttributeVisitor.h    
/// @brief   �ڵ����Է��������ͷ�ļ�  
///  
/// ���ļ���ɽڵ����Է������������ 
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DELTA_NodeStructureTest_AttributeVisitor
#define DELTA_NodeStructureTest_AttributeVisitor

#include <osg/Node>
#include <osgDB/ReadFile>
#include <iostream>

class AttributeVisitor :
	public osg::NodeVisitor
{
public:
	AttributeVisitor(float red,float green,float blue,float alpha);

	virtual void apply(osg::Node& node);

	virtual void apply(osg::Geode& node);

protected:
	int _indent;

private:
	float mRed,mGreen,mBlue,mAlpha;
};
#endif // DELTA_NodeStructureTest_AttributeVisitor