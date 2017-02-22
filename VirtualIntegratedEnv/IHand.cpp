////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IHand.cpp
/// @brief   虚拟手抽象基类的源文件    
/// 
/// 本文件声明了虚拟手抽象基类的公共方法
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "IHand.h"

IHand::IHand(std::string name, float scale, const std::string& configFile, bool useCollision)
: mName(name)
, mScale(scale)
, mConfigFile(configFile)
, mUseCollision(useCollision)
, HasElbowAction(false)
{
	initPartPtr();
	mRoot = new Part("mRoot");
}

IHand::~IHand()
{
	delete mAsmInfo;
	mAsmInfo = NULL;
	std::cout << "IHand Class has been destroyed!" << std::endl;
}

int IHand::ConfigureHand()
{
	mAsmInfo = new ReadAsmTxt(mConfigFile);
	mAsmInfo->readWholeFileInfo();

	if(false == mAsmInfo->Is_OpenSuccessful())
		return -1; //文件未能打开

	if(false == LoadPartToVector())
		return -2; //解析文件错误

	return 1;
}

bool IHand::LoadPartToVector()
{
	// parse fingers and knuckles
	if(false == mAsmInfo->parseFingerConfigInfo(mFingerConfigInfo))
		return false;

	// parse part scale factor
	double _scale = mScale;
	if(false == mAsmInfo->parsePartScale(_scale))
		return false;
	mScale = _scale;

	// parse part info, and save them into the PartVector
	std::vector<AssemblyInfoStruct*> PartList;
	if(false == mAsmInfo->parsePartInfo(PartList))
		return false;
	for (unsigned int i=0; i<PartList.size(); i++)
	{
		Part* pt = new Part();
		configPart(pt,*(PartList[i]));
		PartVector.push_back(pt);
	}

	return true;
}

void IHand::configPart(Part* thisPart, AssemblyInfoStruct & ais, Part* parent/*=NULL*/)
{
	thisPart->setName(ais.name);
	thisPart->loadFile(ais.filename,false);
	if(parent != NULL)
		parent->addChild(thisPart);
	thisPart->getModelPtr()->SetScale(osg::Vec3(mScale, mScale, mScale));
	//thisPart->setPosition(ais.pos*mScale);
	//thisPart->setAttitude(ais.att);
	//thisPart->makeTransform();
	thisPart->setOriginPosition(ais.pos*mScale);
	thisPart->setOriginAttitude(ais.att);
	thisPart->makeAssembly();
	thisPart->setDeltaAttitudePerFrame(ais.delta_att_perFrame);
	std::cout << ais.name << " is @ " << ais.filename << std::endl;
}

Part* IHand::getHandRoot() const
{
	return mRoot;
}

Part* IHand::getPartFromVector(const std::string& partName)
{
	std::vector<Part*>::iterator iter = PartVector.begin();
	for(; iter!=PartVector.end(); iter++)
	{
		if( (*iter)->getModelPtr()->GetName() == partName )
			return (*iter);
	}
	return NULL;
}

void IHand::initPartPtr()
{
	mRoot = NULL;
	mArm = NULL;
	mForeArm = NULL;
	mPostWrist = NULL;
	mWrist = NULL;
	mPalm = NULL;
}

Finger* IHand::getFingerFromVector(unsigned int index)
{
	if (index < FingersVector.size())
	{
		return FingersVector[index];
	}

	else
	{
		std::cout << "Invalid Index, return a Null pointer!\n";
		return NULL;
	}
}

void IHand::getFingerConfigInfo(std::vector<int>& FCI)
{
	for(unsigned int i=0; i<mFingerConfigInfo.size(); i++)
		FCI.push_back(mFingerConfigInfo[i]);
}
