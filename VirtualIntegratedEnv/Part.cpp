////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Part.cpp
/// @brief   部件类的源文件    
///
/// 本文件所实现的部件类，是对Delta3d::Object类的封装
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Part.h"
#include <dtCore/transform.h>
#include <dtCore/scene.h>


Part::Part(const std::string& name /*= "Part"*/)
: b_DrawableHasBeenLoaded(false)
{
	mCoordinateFrame = new dtCore::Object(name+"Coordinate");
	mOriginPos = osg::Vec3(0,0,0);
	mOriginAtt = osg::Vec3(0,0,0);
	dtCore::Transform tf;
	tf.Set(mOriginPos,mOriginAtt);
	mCoordinateFrame->SetTransform(tf,dtCore::Transformable::REL_CS);

	mModel = new dtCore::Object(name);
	setPosition(0,0,0);
	setAttitude(0,0,0);
	makeTransform();
	mCoordinateFrame->AddChild(mModel);

	mNextKnuckle = NULL;
	mDeltaAttPerFrame.set(0,0,0);
}

Part::~Part()
{}

void Part::setPosition(float x,float y,float z)
{
	mPos.set(x,y,z);
}

void Part::setPosition(osg::Vec3 pos)
{
	mPos.set(pos);
}

osg::Vec3 Part::getPosition()
{
	return mPos;
}
void Part::setAttitude(float h,float p,float r)
{
	mAtt.set(h,p,r);
}
void Part::setAttitude(osg::Vec3 att)
{
	mAtt.set(att);
}
osg::Vec3 Part::getAttitude()
{
	return mAtt;
}

void Part::makeAssembly()
{
	dtCore::Transform tf;
	tf.Set(mOriginPos,mOriginAtt);
	mCoordinateFrame->SetTransform(tf,dtCore::Transformable::REL_CS);
}
void Part::makeTransform()
{
	dtCore::Transform tf;
	tf.Set(mPos,mAtt);
	mModel->SetTransform(tf,dtCore::Transformable::REL_CS);
}

void Part::loadFile(const std::string& filename, bool useCache /*= true*/)
{
	mModel->LoadFile(filename,useCache);
	b_DrawableHasBeenLoaded = true;
}

std::string Part::getName()
{
	return mModel->GetName();
}
void Part::setName(const std::string& name)
{
	mModel->SetName(name);
}

void Part::addToScene(dtCore::Scene* scene)
{
	/*if(scene != NULL)
		scene->AddChild(mModel);*/
	if(scene != NULL)
		scene->AddChild(mCoordinateFrame);
}

dtCore::Object* Part::getModelPtr()
{
	return mModel.get();
}

dtCore::Object* Part::getCoordinatePtr()
{
	return mCoordinateFrame.get();
}

void Part::addChild(Part* pt)
{
	//mModel->AddChild(pt->getModelPtr());
	mModel->AddChild(pt->getCoordinatePtr());
	mNextKnuckle = pt;
}

void Part::setCollisionCategoryBits(unsigned long bits)
{
	mModel->SetCollisionCategoryBits(bits);
}

unsigned long Part::getCollisionCategoryBits()
{
	return mModel->GetCollisionCategoryBits();
}

void Part::setCollisionCollideBits(unsigned long bits)
{
	mModel->SetCollisionCollideBits(bits);
}

bool Part::isLoaded()
{
	return b_DrawableHasBeenLoaded;
}

Part* Part::getNextKnuckle()
{
	return mNextKnuckle; 
}

void Part::setOriginAttitude(osg::Vec3 origin)
{
	mOriginAtt.set(origin);
}
osg::Vec3 Part::getOriginAttitude()
{
	return mOriginAtt;
}
void Part::setOriginPosition(osg::Vec3 origin)
{
	mOriginPos.set(origin);
}
osg::Vec3 Part::getOriginPosition()
{
	return mOriginPos;
}

void Part::setDeltaAttitudePerFrame(osg::Vec3 dAttPerFrame)
{
	mDeltaAttPerFrame.set(dAttPerFrame);
}
osg::Vec3 Part::getDeltaAttitudePerFrame()
{
	return mDeltaAttPerFrame;
}