// Copyright 2019 SMS
// License(Apache-2.0)
// ���ض�

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "print.h"



enum class os_type
{
	windows_xp,
	windows_10,
	kali,
};
	

// Ŀ�����ϵͳ������Ϣ
struct os_info
{
	os_type type;
};


// Ŀ���û�������Ϣ
struct user_info
{
	string name; // �û�����
};


// ģ����Ϣ
struct module_info
{
	string path;     // ·��
	string auther;   // ����
	string license;  // ���֤
};

typedef uint module_id_t;


class Slave
{
public:
	Slave();

	bool load(const string& mod);      // װ��ģ��
	bool unload(const string& mod);    // ж��ģ��

private:
	os_info    osInfo;                 // ϵͳ��Ϣ
	user_info  userInfo;               // �û���Ϣ
	map<module_id_t, module_info*> module;    // ��װ�ص�ģ��
};



#endif // SLAVE_H_
