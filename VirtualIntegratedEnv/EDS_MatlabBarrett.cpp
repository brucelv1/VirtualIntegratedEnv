////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_MatlabBarrett.cpp
/// @brief   外部数据策略-Barrett手的Matlab控制算法数据类的源文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "EDS_MatlabBarrett.h"
//MAKE_EDS_PROTOTYPE(EDS_MatlabBarrett)

EDS_MatlabBarrett::EDS_MatlabBarrett(void)
: IExternDataStrategy()
, b_mLibLoaded(false)
, mJointValues(NULL)
, mEndMove(NULL)
, mFingerMove(NULL)
, mCalcuNum(NULL)
{
	
}

EDS_MatlabBarrett::EDS_MatlabBarrett(const EDS_MatlabBarrett& copy)
{
	b_mLibLoaded = copy.b_mLibLoaded;

	mJointValues = copy.mJointValues;
	mEndMove = copy.mEndMove;
	mFingerMove = copy.mFingerMove;
	mCalcuNum = copy.mCalcuNum;
}

EDS_MatlabBarrett::~EDS_MatlabBarrett(void)
{
	if(b_mLibLoaded)
	{
		BarrettGraspTerminate();
	}
}

bool EDS_MatlabBarrett::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IExternDataStrategy::initStrategyConfig(si,_hand,_scene);

	mFingerCollided = std::vector<bool>(mHand->FingersVector.size(),false);

	b_mLibLoaded = BarrettGraspInitialize();
	if(b_mLibLoaded)
		std::cout << "Matlab lib loaded!\n";

	mJointValues = new mwArray(8,1,mxDOUBLE_CLASS);
	double jointVal[] = {0,0,0,0,0,0,0,0};
	mJointValues->SetData(jointVal,8);

	mEndMove = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mEndMove)(1,1) = 0;

	mFingerMove = new mwArray(3,1,mxDOUBLE_CLASS);
	double fingerMove[] = {0,0,0};
	mFingerMove->SetData(fingerMove,3);

	mCalcuNum = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mCalcuNum)(1,1) = 0;

	return true;
}

void EDS_MatlabBarrett::UpdateHand()
{
	mwArray tmpJointValues(8,1,mxDOUBLE_CLASS);
	double tmp[] = {0,0,0,0,0,0,0,0};
	tmpJointValues.SetData(tmp,8);

	mwArray tmpNum(1,1,mxDOUBLE_CLASS);
	tmpNum(1,1) = 0;

	barrett_angle_generation(3,tmpJointValues,*mEndMove,tmpNum,*mFingerMove,*mJointValues,*mCalcuNum);
	double dEndMove = (*mEndMove)(1,1);
	if(dEndMove == 0)
	{
		(*mJointValues) = tmpJointValues;
		(*mCalcuNum) = tmpNum;

		double dJV[8] = {0};
		mJointValues->GetData(dJV,8);

		mHand->getFingerFromVector(1)->getKnuckleAt(0)->setAttitude(osg::Vec3(dJV[0],0,0));
		mHand->getFingerFromVector(1)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,0,dJV[1]));
		mHand->getFingerFromVector(1)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,0,dJV[2]));
		mHand->getFingerFromVector(2)->getKnuckleAt(0)->setAttitude(osg::Vec3(dJV[3],0,0));
		mHand->getFingerFromVector(2)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,0,dJV[4]));
		mHand->getFingerFromVector(2)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,0,dJV[5]));
		mHand->getFingerFromVector(0)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,0,dJV[6]));
		mHand->getFingerFromVector(0)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,0,dJV[7]));

		for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
		{
			Finger* fg = mHand->FingersVector[i];
			for (unsigned int j=0; j<fg->numOfKnuckles(); j++)
			{
				fg->getKnuckleAt(j)->makeTransform();
			}
		}
	}
	if (dEndMove == 1)
	{
		mwArray energy(1,1,mxDOUBLE_CLASS);
		barrett_cal_energy(1,energy,*mJointValues,*mCalcuNum);
		double egy = energy(1,1);
		std::cout << egy << std::endl;
	}
}

void EDS_MatlabBarrett::OnMessage( MessageData* data )
{
	if (data->message == "collision")
	{
		dtCore::Scene::CollisionData* cd = static_cast< dtCore::Scene::CollisionData* >( data->userData );

		//模型建模编号与matlab程序编号有些不同，在这里完成映射
		Part* tip1 = mHand->getFingerFromVector(1)->getKnuckleAt(2);
		Part* tip2 = mHand->getFingerFromVector(2)->getKnuckleAt(2);
		Part* tip3 = mHand->getFingerFromVector(0)->getKnuckleAt(1);

		if (cd->mBodies[0] == tip1->getModelPtr() || cd->mBodies[1] == tip1->getModelPtr())
			(*mFingerMove)(1,1) = 1;
		if (cd->mBodies[0] == tip2->getModelPtr() || cd->mBodies[1] == tip2->getModelPtr())
			(*mFingerMove)(2,1) = 1;
		if (cd->mBodies[0] == tip3->getModelPtr() || cd->mBodies[1] == tip3->getModelPtr())
			(*mFingerMove)(3,1) = 1;
	}
}


