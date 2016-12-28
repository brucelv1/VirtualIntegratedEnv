////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_Barrett.cpp
/// @brief   Barrett手类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Hand_Barrett.h"

Hand_Barrett::Hand_Barrett(std::string name, float scale, const std::string& configFile, bool useCollision)
: IHand(name, scale, configFile, useCollision)
{
}

Hand_Barrett::~Hand_Barrett()
{
	std::cout << "Hand_Barrett Class has been destroyed!" << std::endl;
}

int Hand_Barrett::ConfigureHand()
{
	int ErrorCode = IHand::ConfigureHand();
	if(ErrorCode != 1)
		return ErrorCode;

	if(mAsmInfo->Is_OpenSuccessful())
	{
		Part_Node_Mapping();
		Part_Collision_Mapping();
		Parent_Child_Mapping();
	}

	return 1;
}

void Hand_Barrett::Part_Node_Mapping()
{
	mPalm = getPartFromVector("Palm");

	Finger* Finger0 = new Finger("Finger0");
	Finger0->addKnuckle_back(getPartFromVector("Mid0"));
	Finger0->addKnuckle_back(getPartFromVector("Tip0"));
	FingersVector.push_back(Finger0);

	Finger* Finger1 = new Finger("Finger1");
	Finger1->addKnuckle_back(getPartFromVector("Base1"));
	Finger1->addKnuckle_back(getPartFromVector("Mid1"));
	Finger1->addKnuckle_back(getPartFromVector("Tip1"));
	FingersVector.push_back(Finger1);

	Finger* Finger2 = new Finger("Finger2");
	Finger2->addKnuckle_back(getPartFromVector("Base2"));
	Finger2->addKnuckle_back(getPartFromVector("Mid2"));
	Finger2->addKnuckle_back(getPartFromVector("Tip2"));
	FingersVector.push_back(Finger2);
}

void Hand_Barrett::Part_Collision_Mapping()
{
	if(mUseCollision == false)
		return;

	mPalm->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(0)->getKnuckleAt(1)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(1)->getKnuckleAt(2)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(2)->getKnuckleAt(2)->getModelPtr()->SetCollisionMesh();
}

void Hand_Barrett::Parent_Child_Mapping()
{
	mRoot->addChild(mPalm);

	for (unsigned int i=0; i<FingersVector.size(); i++)
	{
		if(getFingerFromVector(i) != NULL)
		{
			getFingerFromVector(i)->makeFinger();
			mPalm->addChild(getFingerFromVector(i)->getKnuckleAt(0));
		}
	}
}