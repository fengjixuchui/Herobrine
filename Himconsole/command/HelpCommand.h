// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("��ʾ���������Ϣ", "Herobrine")
	{
		syntax.insert({"command", Syntax(Syntax::Type::STRING, true, "Ҫ��ʾ������Ϣ������")});
	}

	void excute(Console& console) override
	{
		if(console.getArgSize() == 0)
		{
			/*auto size = console.getCommandSize();
			for(size_t i = 0; i < size; i++)
			{
				auto cmd = console.getCommand(i);
				printf("%-15s %s\n", cmd->getName().c_str(), cmd->getDescription().c_str());
			}*/
		} else {
			auto name = console.getStringArg("command");
			auto cmd	= console.getCommand(name);
			if(cmd == nullptr)
				throw "δ�ҵ�����";
			printf("%s\n%s\n", name.c_str(), cmd->getDescription().c_str());
		}
	}
};


