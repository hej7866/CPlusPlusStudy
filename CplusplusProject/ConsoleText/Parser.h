#pragma once
#include <string>

enum CommandType // 어떤 종류의 커맨드인지 구분하는 열거형(enum)
{
	CommandTypeNone,

	CommandTypeW,
	CommandTypeA,
	CommandTypeS,
	CommandTypeD,

	CommandTypeQuit,
	CommandTypeGet,
	CommandTypeInventory,
	CommandTypeHelp,
	CommandTypeInfo,
};
// char* char[]
// w,a,s,d
class ConsoleTextCommand
{

public:
 
	CommandType commandType;
	std::string Parameter;

};

ConsoleTextCommand ParseCommand();