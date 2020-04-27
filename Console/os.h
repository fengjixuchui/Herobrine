// Copyright 2019 SMS
// License(Apache-2.0)

#ifndef OS_H_
#define OS_H_


// �������ϵͳ��, �����жϲ���ϵͳ����
#ifdef _WIN32
	#define OS_WIN // Windows
	#ifdef _WIN64
		#define OS_WIN64
	#else
		#define OS_WIN32
	#endif
#else
	#define OS_LINUX // Linux
#endif


#endif // OS_H_
