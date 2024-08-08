/*
*  학습 목표 : C++ 언어 학습. C언어 에서 배운 내용을 복습해본다.
*  작성일    : 2024-08-08
*  작성자    : 황은중
*/

/*
*   Hello World 출력 해주는 함수 <- 입출력 함수 : <stdio.h>  printf, scanf
*   Hello World 출력 해주는 함수 <- 입출력 함수 : <iostream> cout , cin
*   cout : 출력 함수
*   사용법  std::cout << "Hello World!" << std::endl;
*   cin  : 입력 함수
*   int num;
*   사용법  std::cin >> num;
*/

/*
*  1. std::cout << " " 이 형태를 이해하기 위해서. 앞에서 부터 살펴봤을 때
*  'std::' 문법을 이해해보자.
*  namespace 이름 공간 -> 어떤 정의된 객체가 어디에 소속되어 있는지 알려주는 것입니다.
*  std는 c++ standard Library에 등록된 함수들입니다. C++ 표준 라이브러리의 모든 함수가 정의된 이름 공간
*/

/*
*  함수, 변수를 작성을 하는데, 다른 사람이 쓴 코드를 가져다 쓰면서 중복된 이름을 가진 함수를 사용할 확률이 높아집니다.
*  C++ 문법에서 이를 구분하기 위해서 namespace라는 문법을 제공합니다.
*  사용법 namespace (이름공간)이름 { } : 창원-황은중 김해-황은중
*/

/*
*  범위 지정 연산자 '::'
*  사용법 : 이름 공간:: 변수 또는 함수;
*  이름 공간안에 있는 변수 또는 함수를 사용할 수 있다.
*  만약에 이름 공간이 너무 길어서, 편리하게 쓰는 방법이 없을까?
*  using 키워드
*  using TODAYISTHRUSDAY::num;
*/


/*
*  1. 변수          : int, char, float, double
*  2. 반복문, 조건문 : for반복문, while반복문, if, switch 조건문
*  3. 포인터(변수)  : int*, char*,  &num ,  &a1, *num, *a1
*/

#include "lectures.h"
#include "cstring"

namespace TODAYISTHRUSDAY
{
	int num;
	int num2;
}

using TODAYISTHRUSDAY::num;	     // num 이름만 이름 공간에서 사용한다.
// using namespace TODAYISTHRUSDAY; // 모든 변수 또는 함수를 이름 공간에서 가져온다.
// 이 페이지 안에서 사용하는 모든 변수 또는 함수는 using namespace 이름을 사용해라.
// 장점 : 이름이 긴 namespace를 굳이 입력안해도 된다.
// 단점 : namespace 안에 변수와 함수가 많을 수록, 다른 함수 또는 변수와 이름이 겹치는 경우가 생깁니다.

// 사용 추천안
// using namespace를 이용해서 모든 변수를 참조하는 방식은 지양해라.
// 필요한 함수만 필요한 변수만 지정해서 사용해라

// namespace using 예제

// std::cout -> cout 사용할 수 있게끔 using문을 사용해서 만들어 보세요


namespace CPP
{
	void Sample()
	{
		std::cout << "Sample!" << std::endl;
	}
}

namespace CPP2
{
	void Sample()
	{
		std::cout << "Sample2!" << std::endl;
	}
}

using std::cout;
using std::endl;

namespace HEJ
{
	// 변수
	int age;
	char name[30];
	// 함수
	void PrintMyName()
	{
		cout << "제 이름은 " << name << "입니다.\n";
		cout << "나이는 " << age << "입니다.\n";
	}
}


// std::in 네임스페이스 사용해보기
// 숫자맞추기 간단히 구현해보기.


void lecture1()
{
	cout << "Hello World!\n";
	cout << "Hello World!" << endl;

	CPP::Sample();
	CPP2::Sample();

	// 이름이 나오면 :: namespace이구나
	// std 이름공간입니다. : c++ 표준 라이브러리의 이름 공간 
	strcpy_s(HEJ::name, 27, "황은중");
	HEJ::PrintMyName();

	int a1;
	//scanf_s("%d", &a1); :: C언어에서 입력 받는 방법
	std::cout << "입력 받을 수를 입력해 주세요 : ";
	std::cin >> a1;
	std::cout << "입력받은 수 " << a1;

	// int형 변수 LuckyNumber 선언해주세요 = 5.
	int LuckyNumber = 5;
	// c++ 출력 함수 "나의 숫자를 맞추어 보세요" << std::endl;
	std::cout << "나의 숫자를 맞추어 보세요" << std::endl;
	// int UserInput 선언을 해줍니다.
	int UserInput;



	// 132 ~ 135 while 반복문으로 맞출 때까지 진행하는 코드
	// if함수를 사용해서 LuckyNumber와 UserInput 같으면 
	// c++ 출력 함수 "정답을 맞추었습니다" 개행 기능도 추가해주세요
	// if함수를 사용해서 다르다면
	// c++ 출력 함수 "오답입니다. 다시 입력하세요"
	while (true)
	{
		// 입력을 계속 받아야 합니다.
		std::cin >> UserInput;
		if (LuckyNumber == UserInput)
		{
			std::cout << "정답을 맞추었습니다." << std::endl;
			break;
		}
		else if (LuckyNumber != UserInput)
		{
			std::cout << "오답입니다. 다시 입력하세요" << std::endl;
		}

	}

}