////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    Hand_Custom.cpp
/// @brief   用户用于扩展的自定义手类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "Hand_Custom.h"
#include <QtGui/QMessageBox>

Hand_Custom::Hand_Custom(std::string name, float scale, const std::string& configFile)
	: IHand(name, scale, configFile)
{
}

Hand_Custom::~Hand_Custom()
{
	std::cout << "Hand_Custom Class has been destroyed!" << std::endl;
}

int Hand_Custom::ConfigureHand()
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

void Hand_Custom::Part_Node_Mapping()
{
	mPalm = getPartFromVector("Palm");

	for(unsigned int i=0; i<mFingerConfigInfo.size(); i++)
	{
		char* _name = new char[10];
		sprintf_s(_name,10,"Finger%i",i);
		std::string sName = _name;
		Finger* _Finger = new Finger(sName);
		for (int j=0; j<mFingerConfigInfo[i]; j++)
		{
			char* knuckleName = new char[10];
			sprintf_s(knuckleName,10,"Finger%i%i",i,j);
			std::string sKnuckleName = knuckleName;
			_Finger->addKnuckle_back(getPartFromVector(sKnuckleName));
			delete [] knuckleName;
		}
		FingersVector.push_back(_Finger);
		delete [] _name;
	}
}

void Hand_Custom::Part_Collision_Mapping()
{
	std::vector<CollisionInfoStruct*> CollidesList;
	IHand::mAsmInfo->parsePartCollision(CollidesList);
	for (unsigned int i=0; i<CollidesList.size(); i++)
	{
		Part* pt = NULL;
		pt = IHand::getPartFromVector(CollidesList[i]->name);
		if(pt == NULL)
		{
			QString mes = QString("No part named [%1] has been found during Collision Mapping!\n").arg(CollidesList[i]->name.c_str());
			mes.append("This might cause crash. Please fix this error and then try again.");
			QMessageBox::warning(NULL, "Warning", mes);
			break;
		}
		pt->getModelPtr()->SetCollisionMesh();
		pt->setCollisionCategoryBits(CollidesList[i]->CollisionCategory);
		pt->setCollisionCollideBits(CollidesList[i]->CollisionCollides);
	}
}

void Hand_Custom::Parent_Child_Mapping()
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

void Hand_Custom::setMotionPriority()
{
// 	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(1));
// 	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(2));
// 	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(3));
// 	getFingerFromVector(0)->addHigherPriority(getFingerFromVector(4));
}