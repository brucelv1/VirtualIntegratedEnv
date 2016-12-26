////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    InfoVisitor.cpp
/// @brief   �ڵ���Ϣ���������Դ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "InfoVisitor.h"

InfoVisitor::InfoVisitor(void):osg::NodeVisitor(TRAVERSE_ALL_CHILDREN),	_indent(0){}

void InfoVisitor::apply(osg::Node& node)
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

void InfoVisitor::apply(osg::Geode& node)
{
	for(int i=0;i<_indent;++i)
	{
		std::cout<<"  ";
	}
	std::cout<<"["<<_indent+1<<"]"<<node.libraryName()<<"::"<<node.className()<<std::endl;

	for(unsigned int n=0;n<node.getNumDrawables();++n)
	{
		osg::Drawable* drawable = node.getDrawable(n);
		if(!drawable) continue;

		for(int i=0;i<_indent;++i)
		{
			std::cout<<"  ";
		}
		std::cout<<"["<<_indent+1<<"]"<<drawable->libraryName()<<"::"<<drawable->className()<<"  "<<drawable->getName()<<std::endl;
	}

	_indent++;
	traverse(node);
	_indent--;

}

