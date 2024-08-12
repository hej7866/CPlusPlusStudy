/*
* 학습 목표 : c++로 구조체 및 구조체 포인터 복습하기
* Pet Management Game
* 작성일 : 2024-08-12
* 작성자 : 황은중
*/

// typedef 키워드 : 다음에 작성되는 데이터 타입을 뒤에 이름으로 별명으로 지어주는 것

// 구조체 변수를 사용해서 cin 함수를 통해 개의 이름을 받아와서 만들어진 구조체에 복사하는 방법 (Easy)

// 1. 펫생성하기
// userInput 1이라는 데이터를 받으면 -> 동적 할당으로 새로운 개를 생성합니다 (normal)

// 개는 이름과, Happy(int), Hungry(int) 수치들은 각각 100이 최대
// Dog 구조체를 사용하는 함수를 만들어 보세요.

// Play(Dog& dog);
// Happy + 10; Hungry - 5;
// Feed(Dog& dog);
// Happy + 5; Hungry + 10;

// DayEnd(Dog& dog);
// Happy - 10; Hungry - 10;

// ShowStatus(Dog& dog);

// 게임 시작 화면 -> 개를 생성해주세요 -> 이름을 입력해주세요
// 메인플레이 화면 -> 1일차 -> 현재 개의 상태를 보여주고 -> 플레이어의 입력
// 1. 놀아주기 2. 먹이주기 등등..

// 새와 고양이 구조체 추가
// 새는 비행과 관련된 함수
// 고양이는 놀아주는데 실패할 확률이있다.
#include "lectures.h"
#include <cstdio>


typedef struct Dog
{
	char name[30];
	int happy;
	int hungry;
}Dog;

typedef struct Cat
{
	char name[30];
	int happy;
	int hungry;
	int curious;
}Cat;

void Play(Dog& dog)
{
	dog.happy += 10;
	dog.hungry -= 5;
}

void Play(Cat& cat)
{
	srand(time(NULL)); // 시드를 만들어주는 함수
	int randomNumber = rand() % 101;
	

	if (cat.curious < randomNumber) {
		std::cout << "고양이가 놀기를 거부했습니다." << std::endl;
		cat.hungry -= 5;
	}
	else {
		cat.happy += 10;
		cat.hungry -= 5;
	}
}

void Feed(Dog& dog)
{
	dog.happy += 5;
	dog.hungry += 10;
}

void Feed(Cat& cat)
{
	cat.happy += 5;
	cat.hungry += 10;
}

void DayEnd(Dog& dog, int& currentDay)
{
	dog.happy -= 10;
	dog.hungry -= 10;
	currentDay += 1;
}

void DayEnd(Cat& cat, int& currentDay)
{
	cat.happy -= 5;
	cat.hungry -= 5;
	currentDay += 1;
}

void ShowStatus(Dog& dog, int& currentDay)
{
	std::cout << "진행 날짜 :" << currentDay << std::endl;
	std::cout << "펫의 이름 :" << dog.name << std::endl;
	std::cout << "행복도    :" << dog.happy << std::endl;
	std::cout << "허기      :" << dog.hungry << std::endl;
}

void ShowStatus(Cat& cat, int& currentDay)
{
	std::cout << "진행 날짜 :" << currentDay << std::endl;
	std::cout << "펫의 이름 :" << cat.name << std::endl;
	std::cout << "행복도    :" << cat.happy << std::endl;
	std::cout << "허기      :" << cat.hungry << std::endl;
}

void MakePet(Dog& dog)
{
	std::cout << "펫의 이름을 입력해주세요" << std::endl;
	std::cin >> dog.name;
	dog.happy = 100;
	dog.hungry = 100;
}

void MakePet(Cat& cat)
{
	std::cout << "펫의 이름을 입력해주세요" << std::endl;
	std::cin >> cat.name;
	cat.happy = 100;
	cat.hungry = 100;
	cat.curious = 75;
}

void MainPlay(Dog& dog,int& currentDay)
{
	while (true) {
		system("cls"); // 콘솔클리어
		ShowStatus(dog, currentDay);
		int userInput;
		std::cout << "행동을 선택해주세요" << std::endl;
		std::cout << "1. 놀아주기" << std::endl;
		std::cout << "2. 먹이주기" << std::endl;
		std::cin >> userInput;
		if (userInput == 1) {
			Play(dog);
		}
		else if (userInput == 2) {
			Feed(dog);
		}

		DayEnd(dog, currentDay);

		if (currentDay >= 10) {
			break;
		}
	}
	ShowStatus(dog, currentDay);
}

void MainPlay(Cat& cat, int& currentDay)
{
	while (true) {
		system("cls"); // 콘솔클리어
		ShowStatus(cat, currentDay);
		int userInput;
		std::cout << "행동을 선택해주세요" << std::endl;
		std::cout << "1. 놀아주기" << std::endl;
		std::cout << "2. 먹이주기" << std::endl;
		std::cin >> userInput;
		if (userInput == 1) {
			Play(cat);
		}
		else if (userInput == 2) {
			Feed(cat);
		}

		DayEnd(cat, currentDay);

		if (currentDay >= 10) {
			break;
		}
	}
	ShowStatus(cat, currentDay);
}

void lecture3()
{
	// 구조체 선언하는 방법
	Dog dog;
	Cat cat;

	int selectPet; // 1.dog 2.cat
	std::cout << "펫을 선택해주세요 1번은 개, 2번은 고양이입니다." << std::endl;
	std::cin >> selectPet;
	switch (selectPet) {
		case 1:
			MakePet(dog);
			break;
		case 2:
			MakePet(cat);
			break;
		default:
			std::cout << "잘못된 숫자를 입력하였습니다." << std::endl;
	}
	int currentDay = 1;
	if (selectPet == 1) {
		MainPlay(dog, currentDay);
	}
	else if (selectPet == 2) {
		MainPlay(cat, currentDay);
	}
	std::cout << "게임 종료!" << std::endl;

	// 구조체 포인터
	Dog* dogPtr = &dog; // 첫번쨰 방법, 구조체 포인터를 선언한 후에 변수의 주소연산자로 할당하기.
	
	// 동적 할당 (memory allocation : 메모리 할당)
	// c++의 동적할당 : new 데이터타입();
	// 동적할당 해제 : delete변수 
	Dog* dogPtr2 = new Dog();
	// (*dogPtr2).name; 이 코드를 화살표연산자로 표현이 가능했다.
	strcpy_s(dogPtr2->name, 30, "삐끼"); 


	std::cout << "구조체 포인터가 가리키는 이름 : " << dogPtr2->name;
	delete dogPtr2;

}

// Play, Feed, ShowStatus 함수 인자 Dog, Cat
// Dog hungry, happy 변경해주는 함수 , dog 객체가 함수를 실행시킨다.
// dog.Play(); dog.Feed();

// 정리
// 1. Dog 구조체로 모든 함수를 표현할 수 없었다. => Dog, Cat, Bird 공통된 구조체 하나로 표현하는 방법이 없을까?
// 2. 새로운 기능을 추가하기 위해서는 Dog, Cat, Bird 함수를 오버로딩 => Play(Pet% pet);
// 3. pet.Play(); 표현을 하는 방식이 더 자연스럽다.
// 4. struct 변수드릉ㄴ 따로 초기화 함수가 필요하다. 초기화 함수를 따로 만들지 않고 문법적으로 지원해주지 않을까?
// 클래스 문법을통해 해결