////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    findNodeVisitor.h
/// @brief   查找节点访问器类的头文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _Delta_FindNodeVisitor_H_
#define _Delta_FindNodeVisitor_H_

#include <osg/NodeVisitor>
#include <osg/Node>

class findNodeVisitor : public osg::NodeVisitor 
{
public: 

	// Default constructor - initialize searchForName to "" and 
	// set the traversal mode to TRAVERSE_ALL_CHILDREN
	findNodeVisitor(); 

	// Constructor that accepts string argument
	// Initializes searchForName to user string
	// set the traversal mode to TRAVERSE_ALL_CHILDREN
	findNodeVisitor(const std::string &searchName);

	// The 'apply' method for 'node' type instances.
	// Compare the 'searchForName' data member against the node's name.
	// If the strings match, add this node to our list
	virtual void apply(osg::Node &searchNode);

	// Set the searchForName to user-defined string
	void setNameToFind(const std::string &searchName);

	// Return a pointer to the first node in the list
	// with a matching name
	osg::Node* getFirst();

	// typedef a vector of node pointers for convenience
	typedef std::vector<osg::Node*> nodeListType; 

	// return a reference to the list of nodes we found
	nodeListType& getNodeList() { return foundNodeList; }

private:

	// the name we are looking for
	std::string searchForName; 

	// List of nodes with names that match the searchForName string
	nodeListType foundNodeList;

};

#endif //_Delta_FindNodeVisitor_H_
