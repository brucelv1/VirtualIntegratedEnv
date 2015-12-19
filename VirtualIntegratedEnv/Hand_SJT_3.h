////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_SJT3.h
/// @brief   SJT3手类的头文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef	VIE_HAND_SJT_3_H_
#define VIE_HAND_SJT_3_H_

#include "IHand.h"
#include "Finger.h"

class Hand_SJT_3 : public IHand
{
public:
	Hand_SJT_3(float scale, const std::string& configFile);
	virtual ~Hand_SJT_3();

protected:
	//需要在子类中实现的方法，并在子类的构造函数中依次调用
	//1、部件映射：将加载到部件容器PartVector中的手指相关部件，根据其名字映射到手指容器FingersVector中
	virtual void Part_Node_Mapping();
	//2、对需要进行碰撞检测的部件进行碰撞包围体映射，不是必须实现
	virtual void Part_Collision_Mapping();
	//3、父子节点映射
	virtual void Parent_Child_Mapping();

	//确定手指的运动优先级，具有较低优先级的手指，等待其他手指运动完成之后才开始动作
	void setMotionPriority();
};

#endif // VIE_HAND_SJT_3_H_