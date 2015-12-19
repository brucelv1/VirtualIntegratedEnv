////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    ReadAsmTxt.cpp
/// @brief   读取TXT文件类的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "ReadAsmTxt.h"
#include <iostream>
#include <osg/Vec3>
#include <QtGui/QMessageBox>

ReadAsmTxt::ReadAsmTxt(std::string filename)
: b_mFileOpenSuccessful(false)
{
	m_file.open(filename.c_str());
	if(!m_file.is_open())
	{
		QMessageBox::warning(NULL, "Warning", "Fail to open assembly info file, this may crash the application!"); 
		b_mFileOpenSuccessful = false;
	}
	else
		b_mFileOpenSuccessful = true;
}

ReadAsmTxt::~ReadAsmTxt()
{
	m_file.close();
}

bool ReadAsmTxt::Is_OpenSuccessful()
{
	return b_mFileOpenSuccessful;
}

// isspace()是一个宏函数，用于检查是否空格、\t、\r、\n、\v、\f
char* ReadAsmTxt::removeSpaceOnSides(char* s)
{
	int head = 0;
	int tail = strlen(s)-1;
	int newIndex = 0;

	while(isspace(s[head]) && s[head]!='\0')
		head++;

	while(isspace(s[tail]) && tail >= 0 )
		tail--;

	while ( head <= tail )
		s[newIndex++] = s[head++];

	s[newIndex] = '\0';

	return s;
}

void ReadAsmTxt::readWholeFileInfo()
{
	std::string str;

	while (getline(m_file,str))
	{
		InfoList.push_back(str);
		InfoListMarker.push_back(0);
	}
}

void ReadAsmTxt::parsePartInfo(std::vector<AssemblyInfoStruct*>& AssemblyInfoList)
{
	std::string str;
	char* str_token;
	char* pNext = NULL;

	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,8) == "PartInfo")
		{
			// 读过，打标签
			InfoListMarker[i] = 1;

			str = InfoList[i];
			unsigned int pos = str.find('=')+1;
			unsigned int newpos = 0;
			char tempChar[300]={'\0'};
			strcpy_s(tempChar,str.c_str());

			while(pos < str.length())
				tempChar[newpos++] = str[pos++];
			tempChar[newpos] = '\0';

			AssemblyInfoStruct* ais = new AssemblyInfoStruct();

			str_token = strtok_s(tempChar,",",&pNext);
			ais->name = removeSpaceOnSides(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			ais->filename = removeSpaceOnSides(str_token);

			//以下三组，读出位置坐标
			str_token = strtok_s(NULL,",",&pNext);
			float x = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float y = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float z = atof(str_token);
			ais->pos = osg::Vec3(x,y,z);

			//以下三组，读出姿态坐标
			str_token = strtok_s(NULL,",",&pNext);
			float h = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float p = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float r = atof(str_token);
			ais->att = osg::Vec3(h,p,r);

			//以下三组，读出每帧姿态变化量
			str_token = strtok_s(NULL,",",&pNext);
			float dh = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float dp = atof(str_token);

			str_token = strtok_s(NULL,",",&pNext);
			float dr = atof(str_token);
			ais->delta_att_perFrame = osg::Vec3(dh,dp,dr);

			AssemblyInfoList.push_back(ais);
		}			
	}
}

void ReadAsmTxt::parseFingerConfigInfo(std::vector<int>& FingerConfigInfoList)
{
	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,16) == "FingerConfigInfo")
		{
			InfoListMarker[i] = 1;
			std::vector<char*> items;
			splitIntoItems(InfoList[i], ",", items);

			for (unsigned int j=0; j<items.size(); j++)
				FingerConfigInfoList.push_back(atoi(items[j]));
		}
	}
}

void ReadAsmTxt::splitIntoItems(std::string& info, char* delimiter, std::vector<char*>& items)
{
	unsigned int head = info.find('=')+1;
	unsigned int tail = info.length();

	// to transform a const char* into a non-const char*
	std::string tmp = info.substr(head, tail);
	unsigned int len = tmp.length()+1;
	char* c_info = new char[len];
	strcpy_s(c_info, len, tmp.c_str());

	char* str_token;
	char* pNext = NULL;
	str_token = strtok_s(c_info, delimiter, &pNext);
	items.push_back(removeSpaceOnSides(str_token));
	while(strlen(pNext) != 0)
	{
		str_token = strtok_s(NULL, delimiter, &pNext);
		items.push_back(removeSpaceOnSides(str_token));
	}
}

void ReadAsmTxt::parsePartScale(double& scale)
{
	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,9) == "PartScale")
		{
			InfoListMarker[i] = 1;
			std::vector<char*> items;
			splitIntoItems(InfoList[i], ",", items);

			if (!items.empty())
				scale = atof(items[0]);
		}
	}
}

std::vector<std::string> ReadAsmTxt::getInfoList()
{
	return InfoList;
}

//////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_MAIN

int main()
{
	ReadAsmTxt* rat = new ReadAsmTxt("NewParserTest.txt");
	rat->readWholeFileInfo();
	std::vector<std::string> infoList = rat->getInfoList();
	for(unsigned int i=0; i<infoList.size(); i++)
		printf_s("%s\n", infoList[i].c_str());


	std::vector<AssemblyInfoStruct*> list;
	rat->parsePartInfo(list);
	for (unsigned int i=0; i<list.size(); i++)
		printf_s("%s\n", list[i]->name.c_str());

	std::vector<int> fingerInfoList;
	rat->parseFingerConfigInfo(fingerInfoList);
	for (unsigned int i=0; i<fingerInfoList.size(); i++)
		printf_s("%i\n", fingerInfoList[i]);

	double partScale;
	rat->parsePartScale(partScale);
	printf_s("%f\n", partScale);

	int a = 1;
	delete rat;
	return 0;
}

#endif
