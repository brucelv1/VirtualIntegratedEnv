////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    InfoStruct.h
/// @brief   数据结构的头文件    
/// 
/// 本文件声明了若干程序中多处使用的，用于传递信息的数据结构
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////
#ifndef _Delta_AssemblyInfoStruct_H_
#define _Delta_AssemblyInfoStruct_H_

#include <osg/Vec3>

struct AssemblyInfoStruct
{
	std::string name;              //对部件的命名
	std::string filename;          //要加载的部件地址
	osg::Vec3 pos;                 //放置位置
	osg::Vec3 att;                 //放置姿态
	osg::Vec3 delta_att_perFrame;  //每帧姿态变化量，用于动画演示
};

struct SettingsInfoStruct
{
	std::string strategy;          //策略名
	unsigned int inputCOM;         //输入设备串口号
	unsigned int outputCOM;        //输出设备串口号
};

struct CollisionInfoStruct
{
	std::string name;                //部件名
	unsigned long CollisionCategory; //碰撞类别
	unsigned long CollisionCollides; //碰撞目标
};
#endif //_Delta_AssemblyInfoStruct_H_