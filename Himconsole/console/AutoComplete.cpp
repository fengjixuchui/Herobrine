// Copyright 2019 SMS
// License(Apache-2.0)
// �Զ����

#include "AutoComplete.h"
#include "../attribute.h"
#include "Command.h"
#include "Console.h"

using std::string;



AutoComplete::AutoComplete(Console* console)
		: console(*console)
{
}


void AutoComplete::run(State state, const string& str, const Command* pCmd)
{
	switch(state)
	{
	case State::COMMAND:
		MatchCommand(str);
		break;

	case State::KEY:
		MatchArgument(pCmd, str);
		break;

	default:
		return;
	}

	if(matchs.size() == 0)
	{
		CleanPrompt();
		match = nullptr;
		return;
	}
	if(matchs.size() == 1)
	{
		auto newMatch = matchs.front();
		if(newMatch != match)
		{
			CleanPrompt();
			match = newMatch;
		}
		pos = match->size() - str.size();
	}
	if(matchs.size() > 1)
	{
		// ��ʾ����ƥ���������ͬ��λ��
		// TODO: �˴��������ȱ��

		CleanPrompt();
		pos		= 0;
		match = matchs.back();
		matchs.pop_back();
		int i = 0;
		bool flag = false;
		while(!flag)
		{
			for(auto m : matchs)
				if(m->size() <= i || (*match)[i] != (*m)[i])
				{
					pos = i - str.size();
					flag = true;
					break;
				}
			i++;
		}
	}

	PrintPrompt(str);

	matchs.clear();
}


// �����ȫ��ʾ
void AutoComplete::PrintPrompt(const string& str)
{
	attribute::set(attribute::fore::gray);
	printf("%s", match->substr(str.size(), pos).c_str());
	for(size_t i = 0; i < pos; i++)
		printf("\b");
	attribute::rest();
}


// �����ȫ��ʾ
void AutoComplete::CleanPrompt()
{
	for(size_t i = 0; i <= pos; i++)
		printf(" ");
	for(size_t i = 0; i <= pos; i++)
		printf("\b \b");
}


// ��������ƥ����
void AutoComplete::MatchCommand(const string& str)
{
	if(str.size() == 0)
		return;
	for(auto& i : console.getCommand())
		if(str == i.first.substr(0, str.size()))
			matchs.push_back(&i.first);
}

// ���Ҳ���ƥ����
void AutoComplete::MatchArgument(const Command* cmd, const string& str)
{
	for(auto& syntax : cmd->getSyntax())
		if(str == syntax.first.substr(0, str.size()))
			matchs.push_back(&syntax.first);
}


// ��ȫ
void AutoComplete::complete(string& str)
{
	if(match == nullptr)
		return;
	printf("%s", match->substr(str.size(), pos).c_str());
	str += match->substr(str.size(), pos);
	return;
}
