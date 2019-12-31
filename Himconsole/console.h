// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "include.h"
#include "command.h"
#include "print.h"



class Console
{
public:
	Console();
	virtual ~Console();

	const string& getStringArg(const string& key);
	int           getIntArg(const string& key);
	long          getLongArg(const string& key);
	size_t        getArgSize();

	void          setHistorySize(size_t);
	const string& getHistory(size_t);
	size_t        getHistorySize();

	void          addCommand(const string& name, Command*);
	Command*      getCommand(const string& name);
	size_t        getCommandSize();
	Command*      getCommandFirst();
	Command*      getCommandNext();

	void          setPrompt(const string&);

	void console();

private:
	map<string, string>   args;             // ����
	map<string, Command*> commands;
	deque<string>				  history;					// ������ʷ��¼
	size_t							  historySize = 30; // ���������ʷ��¼����
	string							  prompt;						// ��������ʾ��

	virtual void PrintPrompt();
	inline  int  GetChar();                   // ����һ���ַ�, ������
};



#endif // CONSOLE_H_
