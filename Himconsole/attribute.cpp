// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������

#include "attribute.h"



#ifdef OS_WIN

HANDLE Attribute::hStdOut;
WORD   Attribute::defAttr;
WORD   Attribute::attr;

// ����ǰ������
void Attribute::set(Fore attr_)
{
	attr &= 0xf0;
	attr |= (WORD)attr_;
	SetConsoleTextAttribute(hStdOut, attr);
}


// ���ñ�������
void Attribute::set(Back attr_)
{
	attr &= 0x0f;
	attr |= (WORD)attr_;
	SetConsoleTextAttribute(hStdOut, attr);
}


// ���ù�ͬ����
void Attribute::set(Mode attr_)
{
	attr |= (WORD)attr_;
	SetConsoleTextAttribute(hStdOut, attr);
}


// ��ԭ��Ĭ������
void Attribute::rest()
{
	attr = defAttr;
	SetConsoleTextAttribute(hStdOut, attr);
}


// �Զ���ʼ��
class WinAttributeInit
{
public:
	WinAttributeInit()
	{
		Attribute::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// ��ȡ��ǰ�������ַ�����
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(Attribute::hStdOut, &bufInfo);
		Attribute::defAttr = bufInfo.wAttributes;
		Attribute::attr    = bufInfo.wAttributes;
	}

	~WinAttributeInit()
	{
	}
};

WinAttributeInit winAttributeInit;

#endif // OS_WIN



#ifdef OS_LINUX

// ����ǰ������
void Attribute::set(fore attr)
{
	switch(attr)
	{
	case fore::black:
		printf("\033[30m");
		break;

	case fore::blue:
		printf("\033[34m");
		break;

	case fore::cyan:
		printf("\033[36m");
		break;

	case fore::gray:
		printf("");
		break;

	case fore::green:
		printf("\033[32m");
		break;

	case fore::purple:
		printf("\033[35m");
		break;

	case fore::red:
		printf("\033[31m");
		break;

	case fore::white:
		printf("\033[37m");
		break;

	case fore::yellow:
		printf("\033[33m");
		break;
	}
}


// ���ñ�������
void Attribute::set(back attr)
{
	switch(attr)
	{
	case back::black:
		printf("\033[40;");
		break;

	case back::blue:
		printf("\033[34;");
		break;

	case back::cyan:
		printf("\033[36;");
		break;

	case back::gray:
		printf("");
		break;

	case back::green:
		printf("\033[32;");
		break;

	case back::purple:
		printf("\033[35;");
		break;

	case back::red:
		printf("\033[31;");
		break;

	case back::white:
		printf("\033[37;");
		break;

	case back::yellow:
		printf("\033[33;");
		break;
	}
}


// ���ù�ͬ����
void Attribute::set(mode attr)
{
	switch(attr)
	{
	case mode::back_bold:
		printf("");
		break;

	case mode::fore_bold:
		printf("");
		break;

	case mode::underline:
		printf("\33[4m");
		break;
	}
}


// ��ԭ��Ĭ������
void Attribute::rest()
{
	printf("\33[0m");
}

#endif // OS_LINUX


