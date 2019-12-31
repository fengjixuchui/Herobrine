// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "include.h"



class Attribute
{
#ifdef OS_WIN
	friend class WinAttributeInit;
#endif

public:
	enum class fore
	{
		black  = 0x00,
		blue   = 0x01,
		green  = 0x02,
		cyan   = 0x03,
		red    = 0x04,
		purple = 0x05,
		yellow = 0x06,
		white  = 0x07,
		gray   = 0x08,
	};

	enum class back
	{
		black  = 0x00,
		blue   = 0x10,
		green  = 0x20,
		cyan   = 0x30,
		red    = 0x40,
		purple = 0x50,
		yellow = 0x60,
		white  = 0x70,
		gray   = 0x80,
	};

	enum class mode
	{
		underline = 0x8000,
		fore_bold = 0x0008,
		back_bold = 0x0080,
	};

	static void set(fore);
	static void set(back);
	static void set(mode);
	static void rest();
	
private:
#ifdef OS_WIN
	static HANDLE hStdOut;  // ��׼������
	static WORD   defAttr;  // Ĭ������
	static WORD   attr;     // ��ǰ����̨�ַ�����ֵ
#endif
};



#endif // ATTRIBUTE_H_
