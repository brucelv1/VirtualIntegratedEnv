////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    ReadAsmTxt.h
/// @brief   读取TXT文件类的头文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _READASMTXT_H_
#define _READASMTXT_H_

#include <fstream>
#include <string>
#include "InfoStruct.h"
#include <vector>

class ReadAsmTxt
{
public:
	ReadAsmTxt(std::string filename);
	~ReadAsmTxt();

	bool Is_OpenSuccessful();

    // 一次性把配置文件全部读入内存，存储在InfoList中
	void readWholeFileInfo();

	// 检查配置文件内容的有效性，并返回相应的错误代码
	int checkValidity();

	// 解析“PartInfo”属性，该属性不可缺省
	bool parsePartInfo(std::vector<AssemblyInfoStruct*>& AssemblyInfoList);

	// 解析“FingerConfigInfo”属性，该属性不可缺省
	bool parseFingerConfigInfo(std::vector<int>& FingerConfigInfoList);

	// 解析“PartScale”属性,若无该属性，则不对scale引用做任何修改
	bool parsePartScale(double& scale);

	// 解析“PartCollision”属性，若无该属性，则不对CollidesList引用作任何修改
	bool parsePartCollision(std::vector<char*>& CollidesList);

	// 返回InfoList
	std::vector<std::string> getInfoList();

private:
	// 切分一行配置信息，将切分得到的每个item存入容器items
	void splitIntoItems(std::string& info, char* delimiter, std::vector<char*>& items);

	// remove white spaces at the head and end
	char* removeSpaceOnSides(char* s);

private:
	std::ifstream m_file;
	bool b_mFileOpenSuccessful;
	std::vector<std::string> InfoList;
	std::vector<char> InfoListMarker;
};

#endif  //_READASMTXT_H_