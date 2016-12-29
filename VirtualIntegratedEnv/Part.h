////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Part.h
/// @brief   部件类的头文件    
///
/// 本文件所声明的部件类，是对Delta3d::Object类的封装
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _PART_H_
#define _PART_H_

////ode要求指定dSINGLE或dDOUBLE
//#ifndef dSINGLE
//#define dSINGLE
//#endif

#include <dtCore/object.h>
class dtCore::Scene;

class Part
{
public:
	Part(const std::string& name = "Part");

	~Part();

	void setPosition(float x,float y,float z);
	void setPosition(osg::Vec3 pos);

	osg::Vec3 getPosition();

	void setAttitude(float h,float p,float r);
	void setAttitude(osg::Vec3 att);

	osg::Vec3 getAttitude();

	//按照给定的初始位置和姿态装配坐标系对象
	void makeAssembly();
	//把位置和姿态合为一个变换矩阵（transform），然后赋给mModel，实现其运动
	void makeTransform();

	void loadFile(const std::string& filename, bool useCache = true);

	std::string getName();
	void setName(const std::string& name);

	void addToScene(dtCore::Scene* scene);

	dtCore::Object* getModelPtr();
	dtCore::Object* getCoordinatePtr();

public:
	void addChild(Part* pt);

	void setCollisionCategoryBits(unsigned long bits);
	unsigned long getCollisionCategoryBits();

	void setCollisionCollideBits(unsigned long bits);

	bool isLoaded();

	void setOriginAttitude(osg::Vec3 origin);
	osg::Vec3 getOriginAttitude();

	void setOriginPosition(osg::Vec3 origin);
	osg::Vec3 getOriginPosition();

	void setDeltaAttitudePerFrame(osg::Vec3 dAttPerFrame);
	osg::Vec3 getDeltaAttitudePerFrame();

	// 用于手指的函数，也许可以放到Part类的子类去实现，暂时先放在这里
	Part* getNextKnuckle();
private:
	// mCoordinateFrame负责记录模型的初始位置和姿态，是mModel的父部件，这样可以保证
	// mModel在不规则初始姿态下的转动的正确性
	osg::ref_ptr<dtCore::Object> mCoordinateFrame;
	osg::ref_ptr<dtCore::Object> mModel;
	// mPos,mAtt分别记录位置和姿态,并且可以更新
	osg::Vec3 mPos;
	osg::Vec3 mAtt;
	// 记录初始装配位置和姿态
	osg::Vec3 mOriginPos;
	osg::Vec3 mOriginAtt;
	// 记录该部件在控制字符策略下，每一帧的姿态变化量
	osg::Vec3 mDeltaAttPerFrame;
	bool b_DrawableHasBeenLoaded;
	Part* mNextKnuckle;
};

#endif // _PART_H_