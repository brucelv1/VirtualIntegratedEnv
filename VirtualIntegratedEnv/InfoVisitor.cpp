////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    InfoVisitor.cpp
/// @brief   节点信息访问器类的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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

