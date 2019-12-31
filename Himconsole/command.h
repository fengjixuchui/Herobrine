// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "include.h"



class  Console;

// ����ƽ̨
enum class Platform
{
	Common,
	Windows_XP,
	Windows_10,
};

// ��ԴЭ������
enum class License
{
	Apache_2_0,
	BSD,
	GPL_3_0,
	MPL_2_0,
	LGPL_3_0,
	TIM,
};

// �﷨
struct Syntax
{
	enum class Type
	{
		INT,	 // ����   long
		STRING // �ַ��� std::string
	};
	
	Syntax(Type type, bool required, const string& desc, Syntax* compliance = nullptr)
			: type(type), required(required), desc(desc), compliance(compliance)
	{
	}

	Type		type;
	bool		required;
	string  desc;
	Syntax* compliance;
};


class Command
{
	friend class Console;

public:
	Command(
		const string& desc,
		const string& author,
		Platform      platform = Platform::Common,
		License       license  = License::Apache_2_0);
	virtual ~Command();

	virtual void excute(Console&) = 0;

	const string& getDescription();
	const string& getAuthor();

protected:
	map<string, Syntax> syntax;

private:
	string	 desc;
	string	 author;
	Platform platform;
	License	 license;
};



#endif // COMMAND_H_
