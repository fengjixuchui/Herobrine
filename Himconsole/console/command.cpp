// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "command.h"
#include "console.h"
#include "../localization.h"



Command::Command(
		const string& desc,
		const string& author,
		Platform      platform,
		License       license)
	: desc(desc),
	  author(author),
	  platform(platform),
	  license(license)
{
}


const string& Command::getDescription() const
{
	return desc;
}

const string& Command::getAuthor() const
{
	return author;
}
Platform Command::getPlatform() const
{
	return platform;
}

License Command::getLicense() const
{
	return license;
}

const map<const string, const Syntax>& Command::getSyntax() const
{
	return syntax;
}


// ��Ӳ����﷨
void Command::addSyntax(const string& name, const Syntax syntax)
{
	this->syntax.insert({name, syntax});
}


