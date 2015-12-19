////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    AttributeVisitor.h    
/// @brief   节点属性访问器类的头文件  
///  
/// 本文件完成节点属性访问器类的声明 
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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