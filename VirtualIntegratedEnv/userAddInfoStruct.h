////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    userAddInfoStruct.h
/// @brief   用户添加部件数据结构的头文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _Delta_userAddInfoStruct_H_
#define _Delta_userAddInfoStruct_H_

/// @brief 存储“添加”对话框中的各种信息的结构体
/// @deprecated 版本升级，请不要使用这个结构体，替代为AssemblyInfoStruct
/// @see InfoStruct.h
struct userAddInfo
{
	std::string part;        ///< 部件成员选项
	std::string name;        ///< 用户对部件的命名，英文
	std::string filename;    ///< 要加载的部件地址
	float x,y,z;             ///< 放置位置
	float h,p,r;             ///< 放置姿态
};
#endif //_Delta_userAddInfoStruct_H_