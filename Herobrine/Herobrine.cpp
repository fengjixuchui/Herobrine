// Copyright 2019 SMS
// License(Apache-2.0)

#include "Herobrine.h"

int main()
{
	Herobrine him("127.0.0.1", 25565);
	him.run();

	getchar();
	getchar();

	return 0;
}



Herobrine::Herobrine(const std::string& ip, unsigned short port)
		: Session(ip, port)
{
}


void Herobrine::OnConnect(const boost::system::error_code& error)
{
	if(error)
	{
		// �޷����ӵ�������
		Connect();
		return;
	}

	main();

	Connect();
}


// ���ӵ�������
void Herobrine::main()
{

}

