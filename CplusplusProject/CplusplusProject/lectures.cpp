#include "lectures.h"

namespace CPP
{
	void Sample()
	{
		std::cout << "Sample!";
	}
}

namespace CPP2
{
	void Sample()
	{
		std::cout << "Sample2!";
	}
}

using std::cout;
using std::endl;

void lecture1()
{

}

// int형 변수 선언
int LuckyNumber = 5;

std::cout << "나의 숫자를 맞추어 보세요" << std::endl;

int UserInput;

while (true)
{
	std::cin >> UserInput;

	if (LuckyNumber == UserInput) {
		std::cout << "정답을 맞추었습니다" << std::endl;
	}
	else if (LuckyNumber !- UserInput)
	{
		std::cout << "오답입니다. 다시 입력하세요" << std::endl;
	}
}
