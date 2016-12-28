////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_Human.cpp
/// @brief   仿人手类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Hand_Human.h"

Hand_Human::Hand_Human(std::string name, float scale, const std::string& configFile)
	: IHand(name, scale, configFile)
{
}

Hand_Human::~Hand_Human()
{
	std::cout << "Hand_Human Class has been destroyed!" << std::endl;
}

int Hand_Human::ConfigureHand()
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

void Hand_Human::Part_Node_Mapping()
{
	mPalm = getPartFromVector("Palm");

	Finger* Finger0 = new Finger("Thumb");
	Finger0->addKnuckle_back(getPartFromVector("Base0"));
	Finger0->addKnuckle_back(getPartFromVector("Mid0"));
	Finger0->addKnuckle_back(getPartFromVector("Tip0"));
	FingersVector.push_back(Finger0);

	Finger* Finger1 = new Finger("Index");
	Finger1->addKnuckle_back(getPartFromVector("Base1"));
	Finger1->addKnuckle_back(getPartFromVector("Mid1"));
	Finger1->addKnuckle_back(getPartFromVector("Tip1"));
	FingersVector.push_back(Finger1);

	Finger* Finger2 = new Finger("Middle");
	Finger2->addKnuckle_back(getPartFromVector("Base2"));
	Finger2->addKnuckle_back(getPartFromVector("Mid2"));
	Finger2->addKnuckle_back(getPartFromVector("Tip2"));
	FingersVector.push_back(Finger2);

	Finger* Finger3 = new Finger("Ring");
	Finger3->addKnuckle_back(getPartFromVector("Base3"));
	Finger3->addKnuckle_back(getPartFromVector("Mid3"));
	Finger3->addKnuckle_back(getPartFromVector("Tip3"));
	FingersVector.push_back(Finger3);

	Finger* Finger4 = new Finger("Little");
	Finger4->addKnuckle_back(getPartFromVector("Base4"));
	Finger4->addKnuckle_back(getPartFromVector("Mid4"));
	Finger4->addKnuckle_back(getPartFromVector("Tip4"));
	FingersVector.push_back(Finger4);

}

void Hand_Human::Part_Collision_Mapping()
{
	mPalm->getModelPtr()->SetCollisionMesh();

	for (unsigned int i=0; i<FingersVector.size(); i++)
	{
		unsigned int endKnuckleID = getFingerFromVector(i)->numOfKnuckles()-1;
		getFingerFromVector(i)->getKnuckleAt(endKnuckleID)->getModelPtr()->SetCollisionMesh();
		getFingerFromVector(i)->getKnuckleAt(endKnuckleID-1)->getModelPtr()->SetCollisionMesh();
	}
}

void Hand_Human::Parent_Child_Mapping()
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

void Hand_Human::setMotionPriority()
{
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(1));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(2));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(3));
	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(4));
}