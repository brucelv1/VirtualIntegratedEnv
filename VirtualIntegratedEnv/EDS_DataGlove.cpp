////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_DataGlove.cpp
/// @brief   �ⲿ���ݲ���-���������������Դ�ļ�    
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "EDS_DataGlove.h"

//MAKE_EDS_PROTOTYPE(EDS_DataGlove)

EDS_DataGlove::EDS_DataGlove()
: IExternDataStrategy()
, pGlove(NULL)
{

}

EDS_DataGlove::EDS_DataGlove(const EDS_DataGlove& _DG)
{
	pGlove = _DG.pGlove;
}

void EDS_DataGlove::initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene)
{
	IExternDataStrategy::initStrategyConfig(si,_hand,_scene);
	pGlove = getDataGlovePtr();
	if (pGlove == NULL)
	{
		printf("No available data glove has been opened!\n");
		printf("You have to check USB or RS232 port, and re-start!\n");
	}
}


EDS_DataGlove::~EDS_DataGlove(void)
{
	if (pGlove != NULL)
	{
		fdClose(pGlove);
	}
}

//���ⲿ���õĽӿڣ�����������λ����̬����
void EDS_DataGlove::UpdateHand()
{
	if (pGlove == NULL)
		return;

	//���������ײɼ����Ĺ�һ���ĽǶȣ�0~1��ӳ�䵽���ʵĴ�С 
	//��λ��degrees


	//Ĵָ
	//�������ײ��ܷ���Ĵָ��������̬������ֱ�Ӹ�ֵ��ʹĴָ��ֱ�����Ƽ��ɣ��������Խ���ץȡ
	//osg::Vec3 thumbOri = mHand->getFingerFromVector(0)->getKnuckleAt(0)->getOriginAttitude();
	//thumbOri.y() = -90;
	//mHand->getFingerFromVector(0)->getKnuckleAt(0)->setAttitude(thumbOri);
	float thumbNear = -90.0*fdGetSensorScaled(pGlove,FD_THUMBNEAR);
	mHand->getFingerFromVector(0)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,thumbNear,0));	
	float thumbFar = -90.0*fdGetSensorScaled(pGlove,FD_THUMBFAR);
	mHand->getFingerFromVector(0)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,thumbFar,0));
	mHand->getFingerFromVector(0)->getKnuckleAt(0)->makeTransform();
	mHand->getFingerFromVector(0)->getKnuckleAt(1)->makeTransform();
	mHand->getFingerFromVector(0)->getKnuckleAt(2)->makeTransform();

	//ʳָ
	float indexBase = 0*fdGetSensorScaled(pGlove,FD_INDEXMIDDLE);
	mHand->getFingerFromVector(1)->getKnuckleAt(0)->setAttitude(osg::Vec3(indexBase,0,0));
	float indexNear = -90.0*fdGetSensorScaled(pGlove,FD_INDEXNEAR);
	mHand->getFingerFromVector(1)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,indexNear,0));
	float indexFar = -90.0*fdGetSensorScaled(pGlove,FD_INDEXFAR);
	mHand->getFingerFromVector(1)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,indexFar,0));
	//ĩ��ָ�ڹ���
	//mHand->getFingerFromVector(1)->getKnuckleAt(3)->setAttitude(mHand->getFingerFromVector(1)->getKnuckleAt(3)->getOriginAttitude() + osg::Vec3(0,0.7*indexNear,0));
	mHand->getFingerFromVector(1)->getKnuckleAt(0)->makeTransform();
	mHand->getFingerFromVector(1)->getKnuckleAt(1)->makeTransform();
	mHand->getFingerFromVector(1)->getKnuckleAt(2)->makeTransform();
	//mHand->getFingerFromVector(1)->getKnuckleAt(3)->makeTransform();

	//��ָ
	float middleRing = 0*fdGetSensorScaled(pGlove,FD_MIDDLERING);
	mHand->getFingerFromVector(2)->getKnuckleAt(0)->setAttitude(osg::Vec3(middleRing,0,0));	
	float middleNear = -90.0*fdGetSensorScaled(pGlove,FD_MIDDLENEAR);
	mHand->getFingerFromVector(2)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,middleNear,0));	
	float middleFar = -90.0*fdGetSensorScaled(pGlove,FD_MIDDLEFAR);
	mHand->getFingerFromVector(2)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,middleFar,0));
	//mHand->getFingerFromVector(2)->getKnuckleAt(3)->setAttitude(mHand->getFingerFromVector(2)->getKnuckleAt(3)->getOriginAttitude() + osg::Vec3(0,0.7*middleFar,0));
	mHand->getFingerFromVector(2)->getKnuckleAt(0)->makeTransform();
	mHand->getFingerFromVector(2)->getKnuckleAt(1)->makeTransform();
	mHand->getFingerFromVector(2)->getKnuckleAt(2)->makeTransform();
	//mHand->getFingerFromVector(2)->getKnuckleAt(3)->makeTransform();

	//����ָ
	float ringBase = 0*fdGetSensorScaled(pGlove,FD_MIDDLERING);
	mHand->getFingerFromVector(3)->getKnuckleAt(0)->setAttitude(osg::Vec3(ringBase,0,0));	
	float ringNear = -90.0*fdGetSensorScaled(pGlove,FD_RINGNEAR);
	mHand->getFingerFromVector(3)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,ringNear,0));	
	float ringFar = -90.0*fdGetSensorScaled(pGlove,FD_RINGFAR);
	mHand->getFingerFromVector(3)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,ringFar,0));
	//mHand->getFingerFromVector(3)->getKnuckleAt(3)->setAttitude(mHand->getFingerFromVector(3)->getKnuckleAt(3)->getOriginAttitude() + osg::Vec3(0,0.7*ringBase,0));
	mHand->getFingerFromVector(3)->getKnuckleAt(0)->makeTransform();
	mHand->getFingerFromVector(3)->getKnuckleAt(1)->makeTransform();
	mHand->getFingerFromVector(3)->getKnuckleAt(2)->makeTransform();
	//mHand->getFingerFromVector(3)->getKnuckleAt(3)->makeTransform();

	//Сָ
	float littleBase = 0.0*fdGetSensorScaled(pGlove,FD_RINGLITTLE);
	mHand->getFingerFromVector(4)->getKnuckleAt(0)->setAttitude(osg::Vec3(littleBase,0,0));
	float littleNear = -90.0*fdGetSensorScaled(pGlove,FD_LITTLENEAR);
	mHand->getFingerFromVector(4)->getKnuckleAt(1)->setAttitude(osg::Vec3(0,littleNear,0));	
	float littleFar = -90.0*fdGetSensorScaled(pGlove,FD_LITTLEFAR);
	mHand->getFingerFromVector(4)->getKnuckleAt(2)->setAttitude(osg::Vec3(0,littleFar,0));
	//mHand->getFingerFromVector(4)->getKnuckleAt(3)->setAttitude(mHand->getFingerFromVector(4)->getKnuckleAt(3)->getOriginAttitude() + osg::Vec3(0,0.7*littleFar,0));
	mHand->getFingerFromVector(4)->getKnuckleAt(0)->makeTransform();
	mHand->getFingerFromVector(4)->getKnuckleAt(1)->makeTransform();
	mHand->getFingerFromVector(4)->getKnuckleAt(2)->makeTransform();
	//mHand->getFingerFromVector(4)->getKnuckleAt(3)->makeTransform();
}

fdGlove* EDS_DataGlove::getDataGlovePtr()
{
	char    *szPort    = NULL;
	const int PortToOpenSize = 6;
	char	szPortToOpen[PortToOpenSize];
	fdGlove *pGlove    = NULL;
	bool     showraw   = false;
	int      glovetype = FD_GLOVENONE;

	if (!szPort)
	{
#ifdef WIN32
		szPort = "USB";
#else
		szPort = "/dev/fglove";
#endif
	}
	strcpy_s(szPortToOpen, PortToOpenSize, szPort);
	if (strcmp(szPort,"USB") == 0)
	{
		unsigned short aPID[5];
		int nNumFound = 5;
		int nChosen = 0;
		fdScanUSB(aPID,nNumFound);
		for (int c = 0; c < nNumFound; c++)
		{
			printf("Available USB Gloves:\n");
			printf("%i - ",c);
			switch (aPID[c])
			{
			case DG14U_R:
				printf("Data Glove 14 Ultra Right\n");
				break;
			case DG14U_L:
				printf("Data Glove 14 Ultra Left\n");
				break;
			case DG5U_R:
				printf("Data Glove 5 Ultra Right\n");
				break;
			case DG5U_L:
				printf("Data Glove 5 Ultra Left\n");
				break;
			default:
				printf("Unknown\n");
			}
		}
		printf("Please enter the number to select Data Glove:");
		scanf_s("%i",&nChosen,2); // ���뻺������СΪ2�ֽڣ��ڶ����ֽ����ڴ��'\0'
		sprintf_s(szPortToOpen, PortToOpenSize,"USB%i",nChosen);
		fdOpen(szPortToOpen);
	}

	// Initialize glove
	printf( "Attempting to open glove on %s .. \n", szPortToOpen );
	if (NULL == (pGlove = fdOpen( szPortToOpen )))
	{
		printf( "failed.\n" );
		//return -1;
		return NULL;  //ԭ���ĺ����������ͣ����ڷ���ָ�룬��������޸�
	}

	printf( "+-------------------------------+\n" );
	printf( "+ Data glove linking succeeded. +\n" );
	printf( "+-------------------------------+\n" );

	char *szType = "?";
	glovetype = fdGetGloveType(pGlove);
	switch (glovetype)
	{
	case FD_GLOVENONE: szType = "None"; break;
	case FD_GLOVE7:    szType = "Glove7"; break;
	case FD_GLOVE7W:   szType = "Glove7W"; break;
	case FD_GLOVE16:   szType = "Glove16"; break;
	case FD_GLOVE16W:  szType = "Glove16W"; break;
	case FD_GLOVE5U: szType = "DG5 Ultra serial"; break;
	case FD_GLOVE5UW: szType = "DG5 Ultra serial, wireless"; break;
	case FD_GLOVE5U_USB: szType = "DG5 Ultra USB"; break;
	case FD_GLOVE14U: szType = "DG14 Ultra serial"; break;
	case FD_GLOVE14UW: szType = "DG14 Ultra serial, wireless"; break;
	case FD_GLOVE14U_USB: szType = "DG14 Ultra USB"; break;
	}
	printf( "glove type: %s\n", szType );
	printf( "glove handedness: %s\n", fdGetGloveHand(pGlove)==FD_HAND_RIGHT?"Right":"Left" );
	int iNumSensors = fdGetNumSensors(pGlove);
	printf( "glove num sensors: %d\n", iNumSensors );

	return pGlove;
}