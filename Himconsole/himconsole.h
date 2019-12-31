// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#ifndef HIMCONSOLE_H_
#define HIMCONSOLE_H_

#include "console.h"
#include "slave.h"



class Himconsole : public Console
{
public:
	Himconsole();
	~Himconsole();

	const Slave& getSlave();

private:
	map<id_t, Slave*> slave;
};



#endif // HIMCONSOLE_H_
