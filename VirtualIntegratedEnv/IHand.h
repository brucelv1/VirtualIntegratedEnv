////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IHand.h
/// @brief   虚拟手抽象基类的头文件    
/// 
/// 本文件声明了虚拟手抽象基类，包括对外接口和用于子类继承的接口
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _IHAND_H_
#define _IHAND_H_

////ode要求指定dSINGLE或dDOUBLE
//#ifndef dSINGLE
//#define dSINGLE
//#endif

#include <iostream>
#include <vector>
#include "Part.h"
#include "ReadAsmTxt.h"
#include "Finger.h"

class IHand
{
public:
	bool HasElbowAction;
public:
	std::vector<Finger*> FingersVector;

	IHand(std::string name, float scale, const std::string& configFile);
	virtual ~IHand();

	// 完成手的配置工作，子类根据需求重写该函数，但是要在最开始处调用这个函数
	virtual int ConfigureHand();

	Part* getHandRoot() const;

	Part* getPartFromVector(const std::string& partName);

	Finger* getFingerFromVector(unsigned int index);

	void getFingerConfigInfo(std::vector<int>& FCI);

	std::string getName() {return mName;}
	float getHandScale() {return mScale;}
	std::string getConfigFilePath() {return mConfigFile;}

	// 公共动作：完全张开手掌
	virtual void OpenHand(bool open) {}

	void initPartPtr();
	Part* mRoot; //只初始化其位姿，不加载模型，专门用作管理。（不知道对于颜色等会不会出错）
	Part* mArm;
	Part* mForeArm; //并不是每只手都区分上臂和下臂，现在只有SJT-6区分
	Part* mPostWrist;
	Part* mWrist;
	Part* mPalm;

protected:
	//需要在子类中实现的方法，并在子类的构造函数中依次调用
	//1、部件映射：将加载到部件容器PartVector中的手指相关部件，根据其名字映射到手指容器FingersVector中
	virtual void Part_Node_Mapping()=0;
	//2、对需要进行碰撞检测的部件进行碰撞包围体映射，不是必须实现
	virtual void Part_Collision_Mapping() {}
	//3、父子节点映射
	virtual void Parent_Child_Mapping()=0;

	ReadAsmTxt* mAsmInfo;
	std::vector<int> mFingerConfigInfo;

private:
	std::vector<Part*> PartVector;
	std::string mName;
	float mScale;
	std::string mConfigFile;

	void configPart(Part* thisPart, AssemblyInfoStruct & ais, Part* parent = NULL);

	bool LoadPartToVector();
};

#endif // _IHAND_H_