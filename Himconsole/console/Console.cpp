// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#include "console.h"
#include "../localization.h"
#include <ctype.h>

#ifdef OS_WIN
#include <conio.h>
#endif



Console::Console()
		: highlight(this), autoComplete(this), state(State::COMMAND)
{
}


Console::~Console()
{
}


size_t Console::getArgSize() const
{
	return args.size();
}


const string& Console::getStringArg(const string& key) const
{
	return args.at(key);
}

int Console::getIntArg(const string& key) const
{
	return stoi(args.at(key));
}

long Console::getLongArg(const string& key) const
{
	return stol(args.at(key));
}


void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}


void Console::setHistorySize(size_t size)
{
	historySize = size;
}


/*void Console::addHistory(const vector<string>& buffers) const
{
	while(historys.size() >= historySize)
		historys.pop_back();

	historys.push_front(buffers);
}*/

/*
const deque<vector<string>>& Console::getHistory() const
{
	return historys;
}
*/

void Console::addCommand(const string& name, Command* cmd)
{
	assert(getCommand(name) == nullptr);

	commands.insert({name, cmd});
}


void Console::delCommand(const string& name)
{
	commands.erase(name);
}


Command* Console::getCommand(const string& name) const
{
	auto res = commands.find(name);
	if(res == commands.end())
		return nullptr;
	return res->second;
}

const Syntax* Console::getKey(const string& name) const
{
	assert(pCommand != nullptr);

	auto res = pCommand->syntax.find(name);
	if(res == pCommand->syntax.end())
		return nullptr;
	return &(res->second);
}



const map<string, Command*>& Console::getCommand() const
{
	return commands;
}



// TODO(SMS):
//   �﷨����, ������ֱ����command->syntax���������е�����
//   ������ʷ


void Console::run()
{
	while(true)
	{
		vector<string> buffers;
		string*				 arg				 = nullptr;
		bool					 inputString = false;
		state											 = State::COMMAND;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();

			if(inputString && isprint(ch))
			{
				if(ch == '"')
					inputString = false;
				printf("%c", ch);
				buf += ch;
				continue;
			}

			if(ch == '\r' || ch == '\n')
			{
				switch(state)
				{
				case State::KEY:
					continue;

				case State::COMMAND:
					pCommand = getCommand(buf);
					if(pCommand == nullptr)
						continue;
					// TODO: ����Ƿ�����ȫ����ѡ����
					break;

				case State::VALUE:
					if(buf.size() == 0)
						continue;

					if(buf.front() == '"')
					{
						if(buf.back() != '"')
							continue;
						*arg = buf.substr(1, buf.size() - 2);
					}
					else
						*arg = buf;
					break;
				}
				printf("\n");
				break;
			}

			// ���������ַ�
			switch(ch)
			{
			case ' ':
				switch(state)
				{
				case State::COMMAND:
					if(pCommand == nullptr)
						continue;
					buffers.push_back(buf);
					state = State::KEY;
					buf.clear();
					break;

				case State::VALUE:
					buffers.push_back(buf);
					if(buf.size() >= 2)
						if(buf.front() == '"')
							*arg = buf.substr(1, buf.size() - 2);
						else
							*arg = buf;
					state = State::KEY;
					buf.clear();
					break;

				case State::KEY:
					continue;
				}
				printf(" ");
				continue;

			case ':':
				if(state != State::KEY || pKey == nullptr)
					continue;
				state = State::DELIM;
				highlight.run(state, buf, pCommand, pKey);
				arg = &args[buf];
				buffers.push_back(buf);
				buf.clear();
				state = State::VALUE;
				continue;

			case '\b':
				switch(state)
				{
				case State::COMMAND:
					if(buf.empty())
						continue;
					buf.pop_back();
					break;

				case State::KEY:
					if(buf.empty())
					{
						buf = buffers.back();
						buffers.pop_back();
						if(buffers.size() == 0)
							state = State::COMMAND;
						else
							state = State::VALUE;
					}
					else
						buf.pop_back();
					break;

				case State::VALUE:
					if(buf.empty())
					{
						buf = buffers.back();
						buffers.pop_back();
						state = State::KEY;
					}
					else
						buf.pop_back();
					break;
				}
				printf("\b \b");
				break;

			case '\t':
				autoComplete.complete(buf);
				if(state == State::KEY)
				{
					pKey = getKey(buf);
					highlight.run(state, buf, pCommand, pKey);
					if(pKey != nullptr && pKey->type != Syntax::Type::OPTION)
					{
						state = State::DELIM;
						highlight.run(state, buf, pCommand, pKey);
						arg = &args[buf];
						buffers.push_back(buf);
						buf.clear();
						state = State::VALUE;
					}
				}
				break;

			default:
				// ����Ϸ��Լ��
				if(ch < -1 || ch > 255)
					continue;
				switch(state)
				{
				case State::COMMAND:
				case State::KEY:
					if(!isalnum(ch))
						continue;
					break;

				case State::VALUE:
					switch(pKey->type)
					{
					case Syntax::Type::STRING:
						if(!isprint(ch))
							continue;
						if(ch == '"' && buf.size() == 0)
							inputString = true;
						break;

					case Syntax::Type::INT:
						if(!isdigit(ch))
							continue;
						break;

					case Syntax::Type::FLOAT:
					case Syntax::Type::DOUBLE:
						if(!isdigit(ch) && ch != '.')
							continue;
						break;
					}
					break;
				}
			}

			if(isprint(ch))
			{
				printf("%c", ch);
				buf += ch;
			}

			// ʶ��ؼ���
			if(state == State::COMMAND)
				pCommand = getCommand(buf);
			else if(state == State::KEY)
				pKey = getKey(buf);

			// �ؼ��ָ���
			highlight.run(state, buf, pCommand, pKey);

			// �Զ����
			autoComplete.run(state, buf, pCommand);
		}

		try
		{
			assert(pCommand != nullptr);
			pCommand->excute(*this);
		}
		catch(const char* error)
		{
			print::error(error);
		}
		catch(...)
		{
			auto& cmd = buffers.front();

			print::error("�����쳣");
			print::info("ж������: " + cmd);
			delCommand(cmd);
		}

		buf.clear();
		buffers.clear();
		args.clear();
	}
}


// �����������ʾ��
void Console::PrintPrompt()
{
	printf("\n");
	attribute::set(attribute::mode::underline);
	printf(prompt.c_str());
	attribute::rest();
	printf("> ");
}


// ����һ���ַ�, ������
inline int Console::GetChar()
{
#ifdef OS_WIN
	return _getch();
#endif

#ifdef OS_LINUX
	system("stty -echo");
	system("stty -icanon");
	char c = getchar();
	system("stty icanon");
	system("stty echo");
	return c;
#endif
}


bool Console::isFilled(const Syntax* pSyntax)
{
	return std::any_of(filled.begin(), filled.end(), [pSyntax](Syntax* i) { return i == pSyntax; });
}
