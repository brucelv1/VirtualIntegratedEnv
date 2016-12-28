////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_SJT3.cpp
/// @brief   SJT3手类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Hand_SJT_3.h"

Hand_SJT_3::Hand_SJT_3(std::string name, float scale, const std::string& configFile)
	: IHand(name, scale, configFile)
{
}

Hand_SJT_3::~Hand_SJT_3()
{
	std::cout << "Hand_SJT_3 Class has been destroyed!" << std::endl;
}

int Hand_SJT_3::ConfigureHand()
{
	int ErrorCode = IHand::ConfigureHand();
	if(ErrorCode != 1)
		return ErrorCode;

	if(mAsmInfo->Is_OpenSuccessful())
	{
		Part_Node_Mapping();
		Part_Collision_Mapping();
		Parent_Child_Mapping();
		setMotionPriority();
	}

	return 1;
}

void Hand_SJT_3::Part_Node_Mapping()
{
	mArm = getPartFromVector("Arm");
	mPostWrist = getPartFromVector("PostWrist");
	mWrist = getPartFromVector("Wrist");
	mPalm = getPartFromVector("Palm");

	Finger* Finger0 = new Finger("Thumb");
	Finger0->addKnuckle_back(getPartFromVector("Thumb0"));
	Finger0->addKnuckle_back(getPartFromVector("Thumb1"));
	Finger0->addKnuckle_back(getPartFromVector("Thumb2"));
	FingersVector.push_back(Finger0);

	Finger* Finger1 = new Finger("Index");
	Finger1->addKnuckle_back(getPartFromVector("Index0"));
	Finger1->addKnuckle_back(getPartFromVector("Index1"));
	Finger1->addKnuckle_back(getPartFromVector("Index2"));
	Finger1->addKnuckle_back(getPartFromVector("Index3"));
	FingersVector.push_back(Finger1);

	Finger* Finger2 = new Finger("Middle");
	Finger2->addKnuckle_back(getPartFromVector("Middle0"));
	Finger2->addKnuckle_back(getPartFromVector("Middle1"));
	Finger2->addKnuckle_back(getPartFromVector("Middle2"));
	Finger2->addKnuckle_back(getPartFromVector("Middle3"));
	FingersVector.push_back(Finger2);

	Finger* Finger3 = new Finger("Ring");
	Finger3->addKnuckle_back(getPartFromVector("Ring0"));
	Finger3->addKnuckle_back(getPartFromVector("Ring1"));
	Finger3->addKnuckle_back(getPartFromVector("Ring2"));
	Finger3->addKnuckle_back(getPartFromVector("Ring3"));
	FingersVector.push_back(Finger3);

	Finger* Finger4 = new Finger("Little");
	Finger4->addKnuckle_back(getPartFromVector("Little0"));
	Finger4->addKnuckle_back(getPartFromVector("Little1"));
	Finger4->addKnuckle_back(getPartFromVector("Little2"));
	Finger4->addKnuckle_back(getPartFromVector("Little3"));
	FingersVector.push_back(Finger4);

}

void Hand_SJT_3::Part_Collision_Mapping()
{
	mPalm->getModelPtr()->SetCollisionMesh();

	getFingerFromVector(0)->getKnuckleAt(2)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(1)->getKnuckleAt(3)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(2)->getKnuckleAt(3)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(3)->getKnuckleAt(3)->getModelPtr()->SetCollisionMesh();
	getFingerFromVector(4)->getKnuckleAt(3)->getModelPtr()->SetCollisionMesh();
}

void Hand_SJT_3::Parent_Child_Mapping()
{
	mRoot->addChild(mArm);
	mArm->addChild(mPostWrist);
	mPostWrist->addChild(mWrist);
	mWrist->addChild(mPalm);

	for (int i=0; i<5; i++)
	{
		if(getFingerFromVector(i) != NULL)
		{
			getFingerFromVector(i)->makeFinger();
			mPalm->addChild(getFingerFromVector(i)->getKnuckleAt(0));
		}
	}
}

void Hand_SJT_3::setMotionPriority()
{
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(1));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(2));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(3));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(4));
}