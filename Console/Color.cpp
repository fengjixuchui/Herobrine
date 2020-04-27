// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������

#include "Color.h"

typedef unsigned int uint;

//std::map<unsigned int, Color::pair> Color::pairs;




// �����ɫ����
/*void Color::add(uint id, Fore fore, Back back, Mode mode)
{
	pairs.insert(std::pair<uint, pair>(id, {fore, back, mode}));
}

// ʹ����ɫ����
void Color::set(uint id)
{
	set(pairs[id].fore);
	set(pairs[id].back);
	set(pairs[id].mode);
}*/


#ifdef OS_WIN

HANDLE Color::hStdOut;
WORD	 Color::attr;
WORD	 Color::defAttr;


// ����ǰ��ɫ
void Color::set(Fore attr)
{
	Color::attr &= 0xf0;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// ���ñ���ɫ
void Color::set(Back attr)
{
	Color::attr &= 0x0f;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// ������������
void Color::set(Mode attr)
{
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}


// ��ԭĬ������
void Color::reset()
{
	attr = defAttr;
	SetConsoleTextAttribute(hStdOut, attr);
}


class WinColorInit
{
public:
	WinColorInit()
	{
		Color::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// ��ȡ��ǰ�������ַ�����
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(Color::hStdOut, &bufInfo);
		Color::defAttr = bufInfo.wAttributes;
		Color::attr		 = bufInfo.wAttributes;
	}
};

WinColorInit winColorInit;

#endif // OS_WIN


#ifdef OS_LINUX

// ����ǰ��ɫ
void Color::set(Fore attr)
{
	switch(attr)
	{
	case Fore::black:
		printf("\033[30m");
		break;

	case Fore::blue:
		printf("\033[34m");
		break;

	case Fore::cyan:
		printf("\033[36m");
		break;

	case Fore::gray:
		printf("");
		break;

	case Fore::green:
		printf("\033[32m");
		break;

	case Fore::purple:
		printf("\033[35m");
		break;

	case Fore::red:
		printf("\033[31m");
		break;

	case Fore::white:
		printf("\033[37m");
		break;

	case Fore::yellow:
		printf("\033[33m");
		break;
	}
}

// ���ñ���ɫ
void Color::set(Back attr)
{
	switch(attr)
	{
	case Back::black:
		printf("\033[40;");
		break;

	case Back::blue:
		printf("\033[34;");
		break;

	case Back::cyan:
		printf("\033[36;");
		break;

	case Back::gray:
		printf("");
		break;

	case Back::green:
		printf("\033[32;");
		break;

	case Back::purple:
		printf("\033[35;");
		break;

	case Back::red:
		printf("\033[31;");
		break;

	case Back::white:
		printf("\033[37;");
		break;

	case Back::yellow:
		printf("\033[33;");
		break;
	}
}

// ������������
void Color::set(Mode attr)
{
	switch(attr)
	{
	case Mode::back_bold:
		printf("");
		break;

	case Mode::fore_bold:
		printf("");
		break;

	case Mode::underline:
		printf("\33[4m");
		break;
	}
}

// ��ԭĬ������
void Color::reset()
{
	printf("\33[0m");
}

#endif // OS_LINUX
