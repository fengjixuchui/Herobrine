// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class ClearCommand : public Command
{
public:
	ClearCommand()
			: Command("��������л�����", "Herobrine", Platform::Common, License::Apache_2_0)
	{
	}

	void excute(Console& console) override
	{
#ifdef OS_WIN
			system("cls");
#endif

#ifdef OS_LINUX
			printf("\33[2J");
#endif
	}
};


