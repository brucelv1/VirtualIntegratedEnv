////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    Part.h
/// @brief   �������ͷ�ļ�    
///
/// ���ļ��������Ĳ����࣬�Ƕ�Delta3d::Object��ķ�װ
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _PART_H_
#define _PART_H_

////odeҪ��ָ��dSINGLE��dDOUBLE
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

	//���ո����ĳ�ʼλ�ú���̬װ������ϵ����
	void makeAssembly();
	//��λ�ú���̬��Ϊһ���任����transform����Ȼ�󸳸�mModel��ʵ�����˶�
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

	// ������ָ�ĺ�����Ҳ����Էŵ�Part�������ȥʵ�֣���ʱ�ȷ�������
	Part* getNextKnuckle();
private:
	// mCoordinateFrame�����¼ģ�͵ĳ�ʼλ�ú���̬����mModel�ĸ��������������Ա�֤
	// mModel�ڲ������ʼ��̬�µ�ת������ȷ��
	osg::ref_ptr<dtCore::Object> mCoordinateFrame;
	osg::ref_ptr<dtCore::Object> mModel;
	// mPos,mAtt�ֱ��¼λ�ú���̬,���ҿ��Ը���
	osg::Vec3 mPos;
	osg::Vec3 mAtt;
	// ��¼��ʼװ��λ�ú���̬
	osg::Vec3 mOriginPos;
	osg::Vec3 mOriginAtt;
	// ��¼�ò����ڿ����ַ������£�ÿһ֡����̬�仯��
	osg::Vec3 mDeltaAttPerFrame;
	bool b_DrawableHasBeenLoaded;
	Part* mNextKnuckle;
};

#endif // _PART_H_