// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#include "himconsole.h"

#include "command/ClearCommand.h"
#include "command/HelpCommand.h"
#include "command/HistoryCommand.h"
#include "command/ExecCommand.h"

#include "localization.h"



Himconsole::Himconsole()
{
}

Himconsole::~Himconsole()
{
}



///////////
/**/
int main()
{
	print::warn(local::WARN_DEBUG);
	printf(
			"  __      __    __\n"
			" |  |    |  |  |__|   __________\n"
			" |  |____|  |   __   |  __  __  |\n"
			" |   ____   |  |  |  |  ||  ||  |\n"
			" |  |    |  |  |  |  |  ||  ||  |\n"
			" |__|    |__|  |__|  |__||__||__|\n"
			"\n"
			" [Herobrine (Alpha)             ]\n"
			" [Update Date: %-17.17s]\n"
			" [Update Time: %-17.17s]\n",
			__DATE__, __TIME__);

	Console console;
	console.setPrompt("him");

	console.addCommand(dynamic_cast<Command*>(new ClearCommand()));
	console.addCommand(dynamic_cast<Command*>(new ExecCommand()));
	console.addCommand(dynamic_cast<Command*>(new HelpCommand()));
	console.addCommand(dynamic_cast<Command*>(new HistoryCommand()));

	console.console();

	return 0;
}
/**/
///////////







/*

inline vector<string> split(string, char);

// ������
void Himconsole::Console()
{
	string cmd;

	while (true)
	{
		// ���������ʾ��
		printf("\n");
		Attribute::set(mode::underline);
		printf(prompt.c_str());
		Attribute::setRest();
		printf("> ");

		cmd = ReadLine();

		if (cmd.size() == 0)
			continue;

		// �������
		arg = split(cmd, ' ');

		// ���������ʷ��¼
		while (history_.size() >= historySize)
			history_.pop_back();
		// TODO(SMS): ȥ�����������Ŀհ��ַ�
		history_.push_front(cmd);
		history_.begin()->shrink_to_fit();

		cmd.clear();

		// ִ���ڲ�����
		if (arg[0] == "clear" || arg[0] == "cls")
			clear();
		else if (arg[0] == "exit" || arg[0] == "quit")
			return;
		else if (arg[0] == "help")
			help();
		else if (arg[0] == "history")
			history();
		else
		{
			// ִ���ⲿ����
			ushort i;
			for (i = 0; i < cmd_.size(); i++)
				if (arg[0] == cmd_[i].name)
				{
					cmd_[i].func(*this);
					break;
				}
			if (i == cmd_.size())
				print::error("δ֪����: " + arg[0]);
		}
	}
}


// ��������
string Himconsole::ReadLine()
{
		char   buf;
		string cmd;
	
		size_t pPredict = -1;    // ����Ԥ��ָ��
		size_t pHistory = -1;    // ������ʷָ��

		while (true)
		{
			buf = _getch();

			// �߽���
			if (cmd.size() + 1 > cmd.max_size())
			{
				print::error("�������");
				cmd.clear();
				break;
			}

			// ���ܼ�
			if (buf == -32 || buf == 0)
			{
				buf = _getch();	   // ��ȡ���ܼ�ASCII����

				// ��/�¼� �л�������ʷ��¼
				if (buf == 72)  	 // �ϼ�
				{
					if (history_.empty())
						continue;

					if (pHistory == -1)
						pHistory = 0;
					else if (pHistory < history_.size() - 1)
						pHistory++;
					else
						continue;
				}

				if (buf == 80)	   // �¼�
				{
					if (history_.empty())
						continue;

					if (pHistory == -1)
						pHistory = 0;
					else if (pHistory > 0)
						pHistory--;
					else
						continue;
				}

				// �л���ָ����������ʷ��¼
				if (buf == 72 || buf == 80)
				{
					for (size_t i = 0; i < cmd.size(); i++)
						printf("\b \b");
					cmd = history_[pHistory];
					printf(cmd.c_str());
				}

				continue;
			}


			// Enter�� ��������
			if (buf == '\r')
			{
				printf("\n");
				break;
			}


			// Tab�� ��ȫ����
			if (buf == '\t')
			{
				if (pPredict == -1)	// û��ƥ����
					continue;
				Attribute::set(fore::white);
				Attribute::set(mode::fore_bold);
				printf("%s", &cmd_[pPredict].name[cmd.size()]);
				cmd += &cmd_[pPredict].name[cmd.size()];
				continue;
			}


			// ESC�� �������
			if (buf == 27)
			{
				for (size_t i = 0; i < cmd.size(); i++)
					printf("\b \b");
				pPredict = -1;
				pHistory = -1;
				cmd.clear();
				continue;
			}


			// ���˷Ƿ��ַ�
			if (false)
				; // TODO(SMS): �д�����, ע�����ɶ���


			// Backspace�� ɾ����һ���ַ�
			if (buf == '\b')
			{
				if (cmd.size() <= 0)
					continue;
				printf("\b \b");
				cmd.pop_back();
			}
			else
			{
				// ����������ַ�
				Attribute::set(fore::white);
				Attribute::set(mode::fore_bold);

				printf("%c", buf);

				cmd += buf;
			}

			// ���Ԥ����ʾ
			for (ushort i = 0; i < cmd_.size(); i++)
			{
				if (cmd_[i].name.compare(0, cmd.size(), cmd) == 0 && !cmd.empty()) // ƥ��ɹ�
				{
					// ����������ʾ
					if (pPredict != i && pPredict != -1)
					{
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf(" ");
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf("\b");
					}

					// �����ʾ
					Attribute::set(fore::gray);
					printf("%s", &cmd_[i].name[cmd.size()]);

					// ������
					for (size_t j = 0; j < cmd_[i].name.size() - cmd.size(); j++)
						printf("\b");

					pPredict = i;

					break;
				}

				if (i + 1 == cmd_.size()) // ��ƥ��
				{
					if (pPredict != -1 && cmd.size() < cmd_[pPredict].name.size())
					{
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf(" ");
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf("\b");
						pPredict = -1;
					}
				}
			}
		}

		Attribute::setRest();

		return cmd;
}


// �������
void Himconsole::AddCommand(func_t func, string name, string desc, string help)
{
	cmd_.push_back({ func, name, desc, help });
}


// ������������ʾ��
void Himconsole::SetPrompt(const string& prompt)
{
	this->prompt = prompt;
}


// ��������л�����
void Himconsole::clear()
{
#ifdef OS_WIN
	system("cls");
#elif OS_LINUX
	system("clear");
#endif
}


// ��ʾ������Ϣ
void Himconsole::help()
{
	if (arg.size() > 2)
	{
		print::error("��������");
		return;
	}

	if (arg.size() == 1)   // ö��ȫ�����������
	{
		Attribute::set(fore::black);
		Attribute::set(back::cyan);
		printf(" %-8s %-20s\n", "����", "����");
		Attribute::setRest();

		for (auto& cmd : cmd_)
			printf(" %-8s %-20s\n", cmd.name.c_str(), cmd.desc.c_str());
		return;
	}

	for (auto& cmd : cmd_)   // ���ָ��������﷨
	{
		if (cmd.name == arg[1])
		{
			printf("%s\n%s", cmd.desc.c_str(), cmd.help.c_str());
			return;
		}
	}

	print::error("δ֪����: " + arg[1]);
}


// ��ʾ������ʷ��¼
void Himconsole::history()
{
	Attribute::set(fore::black);
	Attribute::set(back::cyan);
	printf(" %-4s %-20s\n", "ID", "����");
	Attribute::setRest();

	for (size_t i = 0; i < history_.size(); i++)
		printf(" %-4zu %-20s\n", i, history_[i].c_str());
}



// �ָ��ַ���
inline vector<string> split(string str, const char pattern)
{
	vector<string>    ret;
	string::size_type pos;

	str += pattern;

	for (size_t i = 0; i < str.size(); i++)
	{
		pos = str.find(pattern, i);
		if (pos < str.size())
		{
			auto sub = str.substr(i, pos - i);
			ret.push_back(sub);
			i = pos;
		}
	}

	return ret;
}

*/
