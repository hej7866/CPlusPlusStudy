#include "Parser.h"
#include <vector> // 가변배열 (크기 변경이 가능한 배열)
#include <iostream>

ConsoleTextCommand ParseCommand()
{
    ConsoleTextCommand command = {};
    command.commandType = CommandTypeNone;

    const unsigned int INPUTCHARLIMIT = 256; // 상수로 최대 크기를 제한
    char inputstr[INPUTCHARLIMIT];

    char* inputValue = fgets(inputstr, INPUTCHARLIMIT, stdin); // W, North, Up

    std::vector<std::string> tokens;
    char* nextToken = nullptr;
    char* token = strtok_s(inputstr, "\t\n", &nextToken);

    while (token)
    {
        tokens.push_back(token);
        token = strtok_s(nullptr, " \t\n", &nextToken);
    }

    if (tokens.size() >= 1) // 입력을 받은 경우
    {
        std::string parseData = tokens[0];

        // 영어 -> 대소문자. UP up Up uP => 전부다 u으로 변환되는 기능
        for (unsigned int i = 0; i < parseData.size(); i++) {
            parseData[i] = tolower(parseData[i]);
        }

        if (parseData == "w" || parseData == "north" || parseData == "up") {
            command.commandType = CommandTypeW;
        }
        else if (parseData == "a" || parseData == "west" || parseData == "left") {
            command.commandType = CommandTypeA;
        }
        else if (parseData == "s" || parseData == "south" || parseData == "down") {
            command.commandType = CommandTypeS;
        }
        else if (parseData == "d" || parseData == "east" || parseData == "right") {
            command.commandType = CommandTypeD;
        }
    }
    return command;
}
