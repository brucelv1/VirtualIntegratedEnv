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

int ReadAsmTxt::checkValidity()
{
	std::vector<AssemblyInfoStruct*> PartInfolist;
	parsePartInfo(PartInfolist);

	std::vector<unsigned int> fingerInfoList;
	parseFingerConfigInfo(fingerInfoList);

	// check the number of knuckles
	unsigned int NumOfKnuckles = 0;
	for (unsigned int i=0; i<fingerInfoList.size(); i++)
		NumOfKnuckles += fingerInfoList[i];

	if ( NumOfKnuckles != PartInfolist.size())
	{
		QMessageBox::warning(NULL, "Warning", 
			"The number of knuckles does not match that of records in the configuration file. Please try again after fix the file.");
		for (unsigned int j=0; j<InfoListMarker.size(); j++)
			InfoListMarker[j] = 0;
		return -1;
	}
	
	for (unsigned int j=0; j<InfoListMarker.size(); j++)
		InfoListMarker[j] = 0;
	return 1;
}

bool ReadAsmTxt::parsePartInfo(std::vector<AssemblyInfoStruct*>& AssemblyInfoList)
{
	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,8) == "PartInfo")
		{
			// after being read, mark it as 1
			InfoListMarker[i] = 1;
			std::vector<char*> items;
			splitIntoItems(InfoList[i], ",", items);

			// for now, there are 11 items in each record.
			if (items.size() != 11)
			{
				QString mes = "The number of pieces of info in one single record does not match. Please try again after fixing the error.\n[In Position]: ";
				mes.append(items[0]);
				QMessageBox::warning(NULL, "Warning", mes);
				
				return false;
			}

			unsigned int index = 0;
			AssemblyInfoStruct* ais = new AssemblyInfoStruct();

			// parse name and filename
			ais->name = items[index];
			ais->filename = items[++index];

			// parse translation coordinates
			double x = atof(items[++index]);
			double y = atof(items[++index]);
			double z = atof(items[++index]);
			ais->pos = osg::Vec3(x,y,z);

			// parse rotation attitude
			x = atof(items[++index]);
			y = atof(items[++index]);
			z = atof(items[++index]);
			ais->att = osg::Vec3(x,y,z);

			// parse delta rotation per frame
			x = atof(items[++index]);
			y = atof(items[++index]);
			z = atof(items[++index]);
			ais->delta_att_perFrame = osg::Vec3(x,y,z);

			// push this single info into the list
			AssemblyInfoList.push_back(ais);
		}			
	}
	return true;
}

bool ReadAsmTxt::parseFingerConfigInfo(std::vector<unsigned int>& FingerConfigInfoList)
{
	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,16) == "FingerConfigInfo")
		{
			InfoListMarker[i] = 1;
			std::vector<char*> items;
			splitIntoItems(InfoList[i], ",", items);

			for (unsigned int j=0; j<items.size(); j++)
				FingerConfigInfoList.push_back((unsigned int)atoi(items[j]));
		}
	}
	return true;
}

bool ReadAsmTxt::parsePartScale(double& scale)
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
	if (scale <= 0)
		return false;

	return true;
}

bool ReadAsmTxt::parsePartCollision(std::vector<CollisionInfoStruct*>& CollisionInfoList)
{
	for (unsigned int i=0; i<InfoList.size(); i++)
	{
		if(InfoListMarker[i] ==0 && InfoList[i].substr(0,13) == "PartCollision")
		{
			InfoListMarker[i] = 1;
			std::vector<char*> items;
			splitIntoItems(InfoList[i], ",", items);

			unsigned int index=0;
			CollisionInfoStruct* cis = new CollisionInfoStruct();

			// parse the part name
			cis->name = items[index];

			// parse collision category
			cis->CollisionCategory = _transformToCategoryBits(items[++index]);

			// parse collision collides
			++index;
			unsigned long collidesBits = 0;
			for (; index<items.size(); index++)
			{
				collidesBits |= _transformToCategoryBits(items[index]);
			}
			cis->CollisionCollides = collidesBits;

			// push this single info into the list
			CollisionInfoList.push_back(cis);
		}
	}
	return true;
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

std::vector<std::string> ReadAsmTxt::getInfoList()
{
	return InfoList;
}

ReadAsmTxt::CategoryBits ReadAsmTxt::_transformToCategoryBits(char* src)
{
	if(strcmp(src,"A") == 0) return CAT_A;
	if(strcmp(src,"B") == 0) return CAT_B;
	if(strcmp(src,"C") == 0) return CAT_C;
	if(strcmp(src,"D") == 0) return CAT_D;
	else                     return CAT_DEFAULT;
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

	std::vector<char*> collides;
	rat->parsePartCollision(collides);
	for (unsigned int i=0; i<collides.size(); i++)
		printf_s("%s\n", collides[i]);

	int a = 1;
	delete rat;
	return 0;
}

#endif
