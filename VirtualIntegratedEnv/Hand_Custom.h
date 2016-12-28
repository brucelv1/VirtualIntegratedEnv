////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_Custom.h
/// @brief   用户用于扩展的自定义手类的头文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef	VIE_HAND_CUSTOM_H_
#define VIE_HAND_CUSTOM_H_

#include "IHand.h"
#include "Finger.h"

class Hand_Custom : public IHand
{
public:
	Hand_Custom(std::string name, float scale, const std::string& configFile);
	virtual ~Hand_Custom();

	virtual int ConfigureHand();

protected:
	//需要在子类中实现的方法，并在子类的构造函数中依次调用
	//1、部件映射：将加载到部件容器PartVector中的手指相关部件，根据其名字映射到手指容器FingersVector中
	virtual void Part_Node_Mapping();
	//2、对需要进行碰撞检测的部件进行碰撞包围体映射，不是必须实现；若使用，必须在Parent_Child_Mapping()前调用
	virtual void Part_Collision_Mapping();
	//3、父子节点映射
	virtual void Parent_Child_Mapping();

	//确定手指的运动优先级，具有较低优先级的手指，等待其他手指运动完成之后才开始动作
	void setMotionPriority();
};

#endif // VIE_HAND_CUSTOM_H_