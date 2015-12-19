////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Finger.h
/// @brief   虚拟手的手指类的头文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _VIE2_FINGER_H_
#define _VIE2_FINGER_H_

#include "Part.h"
#include <vector>
#include <string>

class Finger
{
public:
	Finger(const std::string& name = "Finger") 
	{
		mName = name;
	}
	~Finger() {}

	void addKnuckle_back(Part* knuckle);
	Part* getKnuckleAt(unsigned int index);

	//将容器中的手指部件，按照序号顺序完成父子映射，0是1的父部件，1是2的父部件，以此类推
	void makeFinger();

	//返回手指容器中的指节数，unsigned int
	unsigned int numOfKnuckles();

	//检查手指的所有部件是否都停止运动
	bool isFingerStopped();

	//添加比自己运动优先级更高的手指部件
	void addHigherPriority(Finger* _finger);

	//检查更高优先级手指是否停止运动，它们都停止了，自己才能运动
	bool readyToMove();

private:
	std::string mName;
	std::vector<Part*> KnuckleVector;
	std::vector<Finger*> HigherPriority;
	//存放此手指各个指节上一帧的姿态，用于判断是否停止运动
	std::vector<osg::Vec3> LastAttitude;

};

#endif // _VIE2_FINGER_H_