// Copyright 2019 SMS
// License(Apache-2.0)

#include "../console/Command.h"
#include "../print.h"



class ListenCommand : public Command
{
public:
	ListenCommand()
			: Command("����", "Herobrine", Platform::Common, License::Apache_2_0)
	{
		addSyntax("ip", {Syntax::Type::STRING, "������IP��ַ", false});
		addSyntax("port", {Syntax::Type::INT, "�����Ķ˿ڵ�ַ", false});
	}

	void excute(Console& c) override
	{
		print::good("������ʼ: " + c.getStringArg("ip") + ":" + c.getStringArg("port"));
	};
};


