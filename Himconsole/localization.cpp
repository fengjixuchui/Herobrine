// Copyright 2019 SMS
// License(Apache-2.0)
// ���ػ�

#include "localization.h"



namespace local
{

#ifdef LANG_EN
const char* WARN_DEBUG             = "This version is built in development for debugging only";
const char* ERROR_UNKNOWN_COMMAND  = "Unknown command";
const char* ERROR_COMMAND_TOO_LONG = "Command too long";
const char* ERROR_INVALID_ARGUMENT = "Invalid arguments";
#endif

#ifdef LANG_ZH_CN
const char* WARN_DEBUG             = "�ð汾�ڿ����й���, ����������";
const char* ERROR_UNKNOWN_COMMAND  = "δ֪����";
const char* ERROR_COMMAND_TOO_LONG = "�������";
const char* ERROR_INVALID_ARGUMENT = "��Ч����";
#endif

#ifdef LANG_ZH_TW
const char* WARN_DEBUG             = "ԓ�汾��_�l�И���, �H���{ԇ��";
const char* ERROR_UNKNOWN_COMMAND  = "δ֪����";
const char* ERROR_COMMAND_TOO_LONG = "�����^�L";
const char* ERROR_INVALID_ARGUMENT = "�oЧ����";
#endif

}


