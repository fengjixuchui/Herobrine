// Copyright 2019 SMS
// License(Apache-2.0)

#include "Console.h"
#include "Command.h"
#include <assert.h>

#include <conio.h>

using std::string;



// ����״̬
// ��ǰ�������������
enum class InputState
{
	Command,
	Key,
	Value
};

// ����ʹ�����
enum class QuotationMark
{
	None,
	Single,
	Double
};



// ����������
void Console::run()
{
	while(true)
	{
		string					 buf;
		Command*				 pCommand			 = nullptr;
		Command::Syntax* pSyntax			 = nullptr;
		InputState			 state				 = InputState::Command;
		QuotationMark		 quotationMark = QuotationMark::None;

		printf(prompt.c_str());

		while(true)
		{
			char c = _getch();

			// �������
			if(c == '\r' || c == '\n')
				if(state == InputState::Command ||
					 state == InputState::Key && buf.size() == 0)
				{
					// �������Ƿ���д����
				}
				else
					continue;

			// ���˷Ƿ��ַ�
			if(!isprint(c))
				continue;

			switch(state)
			{
			case InputState::Command:
				break;

			case InputState::Key:
				break;

			case InputState::Value:
				switch(pSyntax->type)
				{
				case Command::Syntax::Type::String:
					switch(quotationMark)
					{
					case QuotationMark::None:
						if(c == '\'')
							quotationMark = QuotationMark::Single;
						else if(c == '\"')
							quotationMark = QuotationMark::Double;
						buf += c;
						break;

					case QuotationMark::Single:
						if(c != '\'')
							continue;
						quotationMark = QuotationMark::None;
						state					= InputState::Key;
						break;

					case QuotationMark::Double:
						if(c != '\"')
							continue;
						quotationMark = QuotationMark::None;
						state					= InputState::Key;
						break;
					}
					break;

				case Command::Syntax::Type::Int:
					break;

				case Command::Syntax::Type::Float:
					break;
				}
			}

			printf("%c", c);
		}

		// ִ������
		assert(pCommand != nullptr);
		try
		{
		}
		catch(...)
		{
		}
	}
}


// �������
//   name : Ҫ��ӵ���������
//   cmd  : Ҫ��ӵ������ָ��
void Console::addCommand(const std::string& name, Command* cmd)
{
	// ����������
	assert(cmd != nullptr);

	commands.insert({name, cmd});
}


// ����������ʾ��
//   prompt : Ҫ���õ�������ʾ��
void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}
