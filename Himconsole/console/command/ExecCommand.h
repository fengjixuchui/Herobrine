// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"
#include "../../print.h"



#ifdef OS_WIN
#define popen  _popen
#define pclose _pclose
#elif OS_LINUX
#define popen  popen
#define pclose pclose
#endif


class ExecCommand : public Command
{
public:
	ExecCommand()
			: Command("ִ���ⲿϵͳ����", "Herobrine", Platform::Common, License::Apache_2_0)
	{
		addSyntax("command", {Syntax::Type::STRING, "Ҫִ�е�����", false});
	}

	void excute(Console& c) override
	{
		char	buf[1024];
		FILE* pipe;
			
		pipe = popen(c.getStringArg("command").c_str(), "r");

		if(pipe == NULL)
			throw "�޷��򿪹ܵ�";

		while(!feof(pipe))
			if(fgets(buf, 1024, pipe))
				printf("%s", buf);

		if(pclose(pipe) == -1)
			throw "�޷��رչܵ�";
	}
};


