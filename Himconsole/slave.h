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
	char* name; // �û�����
};


// ģ����Ϣ
struct module_info
{
	string path;     // ·��
	string auther;   // ����
	string license;  // ���֤
};


class Slave
{
public:
	Slave();

	bool Load(const string& mod);      // װ��ģ��
	bool Unload(const string& mod);    // ж��ģ��

private:
	os_info    osInfo;                 // ϵͳ��Ϣ
	user_info  userInfo;               // �û���Ϣ
	map<id_t, module_info*> module;    // ��װ�ص�ģ��

	vector<id_t> userId;

	void OnAccept();
};



#endif // SLAVE_H_
