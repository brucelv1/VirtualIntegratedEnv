////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    ColorVisitor.cpp
/// @brief   节点信息访问器类的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "ColorVisitor.h"

ColorVisitor::ColorVisitor(void):osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
{
	_r=1.0;
	_g=1.0;
	_b=1.0;
	_a=1.0;
}

void ColorVisitor::apply(osg::Node& node)
{
	// do nothing, just go deeper
	traverse(node);
}

void ColorVisitor::apply(osg::Geode& node)
{
	for(unsigned int n=0;n<node.getNumDrawables();++n)
	{
		osg::Drawable* drawable = node.getDrawable(n);
		if(!drawable) continue;

		osg::Geometry* geom = drawable->asGeometry();
		if (geom)
		{
			osg::ref_ptr< osg::Vec4Array > colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(_r,_g,_b,_a));
			geom->setColorArray(colors);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);

			// transparency
			if (_a<1)
			{
				// the canonical way of enabling transparency after setting the alpha
				// in a metarial or a texture or a geometry color (with GL_COLOR_MATERIAL) is:			
				osg::StateSet* state = geom->getOrCreateStateSet();
				state->setMode( GL_BLEND, osg::StateAttribute::ON);
				state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
			}
		}
	}

	traverse(node);
}
