// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef INCLUDE_H_
#define INCLUDE_H_



typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;



// C ��׼��
#include <assert.h>


// C++ ��׼��
#include <thread>
using std::thread;


// C++ STL
#include <string>
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <forward_list>
using std::forward_list;

#include <list>
using std::list;

#include <map>
using std::map;

#include <algorithm>
using std::any_of;
using std::none_of;

#include <thread>
using std::thread;

#include <mutex>
using std::mutex;



// �������ϵͳ��, �����жϲ���ϵͳ����
#ifdef _WIN32
	#define OS_WIN      // Windows
	#ifdef _WIN64
		#define OS_WIN64
	#else
		#define OS_WIN32
	#endif
#else
	#define   OS_LINUX  // Linux
#endif



#endif // INCLUDE_H_
