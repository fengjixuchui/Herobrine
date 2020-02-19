// Copyright 2019 SMS
// License(Apache-2.0)
// ���ػ�

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include "include.h"



/*
 ����(Language)
 LANG_ZH_CN ���ļ���
 LANG_ZH_TW ���ķ��w
 LANG_EN    English
 */
#define LANG_ZH_CN

class Localization
{
public:
  const std::string& operator[](const std::string&);

private:
	map<std::string, std::string> dir;
};

extern Localization local;



#endif // LOCALIZATION_H_
