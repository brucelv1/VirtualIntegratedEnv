////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    findNodeVisitor.cpp
/// @brief   查找节点访问器类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "findNodeVisitor.h"   
   
// Default constructor - initialize searchForName to "" and    
// set the traversal mode to TRAVERSE_ALL_CHILDREN   
findNodeVisitor::findNodeVisitor() 
: osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
, searchForName()    
{    
}    
   
// Constructor that accepts string argument   
// Initializes searchForName to user string   
// set the traversal mode to TRAVERSE_ALL_CHILDREN   
findNodeVisitor::findNodeVisitor(const std::string &searchName)
: osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)    
, searchForName(searchName)    
{    
}    
   
 //The 'apply' method for 'node' type instances.   
 //Compare the 'searchForName' data member against the node's name.   
 //If the strings match, add this node to our list   
void findNodeVisitor::apply(osg::Node &searchNode)    
{    
   if (searchNode.getName() == searchForName)   
   {   
      foundNodeList.push_back(&searchNode);   
   }   
   traverse(searchNode);
}    
   
// Set the searchForName to user-defined string   
void findNodeVisitor::setNameToFind(const std::string &searchName)    
{    
   searchForName = searchName;    
   foundNodeList.clear();    
}    
   
//void findNodeVisitor::apply(osg::Transform &searchNode)   
//{   
//   osgSim::DOFTransform* dofNode =    
//      dynamic_cast<osgSim::DOFTransform*> (&searchNode);   
//   if (dofNode)   
//   {   
//      dofNode->setAnimationOn(false);   
//   }   
//   apply ( (osg::Node&) searchNode);   
//   traverse(searchNode);   
//}

osg::Node* findNodeVisitor::getFirst()
{
	if(foundNodeList.size() == 0) //如果某个名字的节点不存在，直接返回“空”；这个判断用于防止“越界错误”
		return NULL;
	return *(foundNodeList.begin());
} 
