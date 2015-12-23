////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    ReadAsmTxt.h
/// @brief   ��ȡTXT�ļ����ͷ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _READASMTXT_H_
#define _READASMTXT_H_

#include <fstream>
#include <string>
#include "InfoStruct.h"
#include <vector>
#include <dtUtil/macros.h>


class ReadAsmTxt
{
public:
	enum CategoryBits{CAT_A = UNSIGNED_BIT(31),
		              CAT_B = UNSIGNED_BIT(30),
		              CAT_C = UNSIGNED_BIT(29),
		              CAT_D = UNSIGNED_BIT(28),
	                  CAT_DEFAULT = UNSIGNED_BIT(5),}; //5->dtCore::Object 

	ReadAsmTxt(std::string filename);
	~ReadAsmTxt();

	bool Is_OpenSuccessful();

    // һ���԰������ļ�ȫ�������ڴ棬�洢��InfoList��
	void readWholeFileInfo();

	// ��������ļ����ݵ���Ч�ԣ���������Ӧ�Ĵ������
	int checkValidity();

	// ������PartInfo�����ԣ������Բ���ȱʡ
	bool parsePartInfo(std::vector<AssemblyInfoStruct*>& AssemblyInfoList);

	// ������FingerConfigInfo�����ԣ������Բ���ȱʡ
	bool parseFingerConfigInfo(std::vector<int>& FingerConfigInfoList);

	// ������PartScale������,���޸����ԣ��򲻶�scale�������κ��޸�
	bool parsePartScale(double& scale);

	// ������PartCollision�����ԣ����޸����ԣ��򲻶�CollidesList�������κ��޸�
	bool parsePartCollision(std::vector<CollisionInfoStruct*>& CollisionInfoList);

	// ����InfoList
	std::vector<std::string> getInfoList();

private:
	// �з�һ��������Ϣ�����зֵõ���ÿ��item��������items
	void splitIntoItems(std::string& info, char* delimiter, std::vector<char*>& items);

	// remove white spaces at the head and end
	char* removeSpaceOnSides(char* s);

	// ���ַ�A, B, C, Dӳ��Ϊö����CAT_A, CAT_B, CAT_C, CAT_D
	CategoryBits _transformToCategoryBits(char* src);

private:
	std::ifstream m_file;
	bool b_mFileOpenSuccessful;
	std::vector<std::string> InfoList;
	std::vector<char> InfoListMarker;
};

#endif  //_READASMTXT_H_