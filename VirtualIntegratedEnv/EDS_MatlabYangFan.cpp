////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_MatlabYangFan.cpp
/// @brief   外部数据策略-Barrett手的Matlab控制算法数据类的源文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "EDS_MatlabYangFan.h"

EDS_MatlabYangFan::EDS_MatlabYangFan(void)
	: IExternDataStrategy()
	, b_mLibLoaded(false)
	, mLAngle(NULL)
	, mRAngle(NULL)
	, mMAngle(NULL)
	, mIAngle(NULL)
	, mTAngle(NULL)
	, mSteps(NULL)
{

}

EDS_MatlabYangFan::EDS_MatlabYangFan(const EDS_MatlabYangFan& copy)
{
	b_mLibLoaded = copy.b_mLibLoaded;

	mLAngle = copy.mLAngle;
	mRAngle = copy.mRAngle;
	mMAngle = copy.mMAngle;
	mIAngle = copy.mIAngle;
	mTAngle = copy.mTAngle;
	mSteps = copy.mSteps;
}

EDS_MatlabYangFan::~EDS_MatlabYangFan(void)
{
	if(b_mLibLoaded)
	{
		JAGeneraterTerminate();
	}
	if(mOutputFile.is_open())
		mOutputFile.close();
}

bool EDS_MatlabYangFan::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IExternDataStrategy::initStrategyConfig(si,_hand,_scene);

	mFingerCollided = std::vector<int>(mHand->FingersVector.size(),0);

	b_mLibLoaded = JAGeneraterInitialize();
	if(b_mLibLoaded)
		std::cout << "YF lib loaded!\n";

	mLAngle = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mLAngle)(1,1) = 0;
	mRAngle = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mRAngle)(1,1) = 0;
	mMAngle = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mMAngle)(1,1) = 0;
	mIAngle = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mIAngle)(1,1) = 0;
	mTAngle = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mTAngle)(1,1) = 0;
	mSteps = new mwArray(1,1,mxDOUBLE_CLASS);
	(*mSteps)(1,1) = 0;

	mOutputFile.open("./Data/YangFan/data.txt",std::ios::out);

	return true;
}

void EDS_MatlabYangFan::UpdateHand()
{
	double _steps;
	mSteps->GetData(&_steps,1);
	if(_steps > 11)
		return;

	joint_angle_generater(6,*mLAngle,*mRAngle,*mMAngle,*mIAngle,*mTAngle,*mSteps,*mSteps);
	double LAngle = 0;
	double RAngle = 0;
	double MAngle = 0;
	double IAngle = 0;
	double TAngle = 0;
	mLAngle->GetData(&LAngle,1);
	mRAngle->GetData(&RAngle,1);
	mMAngle->GetData(&MAngle,1);
	mIAngle->GetData(&IAngle,1);
	mTAngle->GetData(&TAngle,1);

	mHand->getFingerFromVector(4)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,LAngle,0));
	mHand->getFingerFromVector(3)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,RAngle,0));
	mHand->getFingerFromVector(2)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,MAngle,0));
	mHand->getFingerFromVector(1)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,IAngle,0));
	mHand->getFingerFromVector(0)->getKnuckleAt(0)->setAttitude(osg::Vec3(0,-TAngle,0));
	//mHand->getFingerFromVector(0)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,0,0));

	for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
	{
		Finger* fg = mHand->FingersVector[i];
		for (unsigned int j=0; j<fg->numOfKnuckles(); j++)
		{
			fg->getKnuckleAt(j)->makeTransform();
		}
	}
}

void EDS_MatlabYangFan::OnMessage( MessageData* data )
{
	if (data->message == "collision")
	{
		dtCore::Scene::CollisionData* cd = static_cast< dtCore::Scene::CollisionData* >( data->userData );

		Part* tip1 = mHand->getFingerFromVector(0)->getKnuckleAt(1);
		Part* tip2 = mHand->getFingerFromVector(1)->getKnuckleAt(0);
		Part* tip3 = mHand->getFingerFromVector(2)->getKnuckleAt(0);
		Part* tip4 = mHand->getFingerFromVector(3)->getKnuckleAt(0);
		Part* tip5 = mHand->getFingerFromVector(4)->getKnuckleAt(0);

		double _steps = (*mSteps)(1,1);
		if( _steps < 11)
		{
			_outputInfoOnce(0,tip1,cd,_steps);
			_outputInfoOnce(1,tip2,cd,_steps);
			_outputInfoOnce(2,tip3,cd,_steps);
			_outputInfoOnce(3,tip4,cd,_steps);
			_outputInfoOnce(4,tip5,cd,_steps);
		}
	}
}

void EDS_MatlabYangFan::_outputInfoOnce(unsigned int fingerIndex, Part* knuckle, dtCore::Scene::CollisionData* cd, double steps)
{
	if (mFingerCollided[fingerIndex] == 0 && (cd->mBodies[0] == knuckle->getModelPtr() || cd->mBodies[1] == knuckle->getModelPtr()) )
	{
		mFingerCollided[fingerIndex] = 1;
		mOutputFile << knuckle->getModelPtr()->GetName() << ": d=" << steps << "\n";
	}
}


