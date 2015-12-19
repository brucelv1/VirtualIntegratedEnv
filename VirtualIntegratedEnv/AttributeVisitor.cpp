////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    AttributeVisitor.cpp    
/// @brief   节点属性访问器类的源文件  
///  
/// 本文件完成节点属性访问器类的实现 
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "AttributeVisitor.h"
#include <dtCore/refptr.h>

AttributeVisitor::AttributeVisitor(float r,float g,float b,float a)
: osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
, _indent(0)
{
	mRed = r;
	mGreen = g;
	mBlue = b;
	mAlpha = a;
}

void AttributeVisitor::apply(osg::Node& node)
{
	for(int i=0;i<_indent;++i)
	{
		std::cout<<"  ";
	}
	std::cout<<"["<<_indent+1<<"]"<<node.libraryName()<<"::"<<node.className()<<"  "<<node.getName()<<std::endl;

	_indent++;
	traverse(node);
	_indent--;
}

void AttributeVisitor::apply(osg::Geode& node)
{
	for(unsigned int n=0;n<node.getNumDrawables();++n)
	{
		osg::Drawable* drawable = node.getDrawable(n);
		osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
		if(geom)
		{
			dtCore::RefPtr<osg::Vec4Array> colors = new osg::Vec4Array(1);
			//(*colors)[0] = osg::Vec4(mRed,mGreen,mBlue,mAlpha); //银灰色:RGBA:0.4,0.4,0.4,0.1
			(*colors)[0] = osg::Vec4(mRed,mGreen,mBlue,mAlpha);
			geom->setColorArray(colors);
		}
	}

	traverse(node);
}