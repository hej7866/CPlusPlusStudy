#include <iostream>
#include "TickTaeToe.h"

// 클래스 키워드. 이름. 상속을 해야하면 상속을 선언.
// 기능과 멤버 변수 선언 private, public, protected
// 생성자, 소멸자	 - 복사생성자, 얕은 복사 - 깊은 복사
// 상속 : virtual <-> 일반 함수
// 다형성 표현 - 클래스의 확장성을 제공해준다.  
// virtual 함수(); 자식 함수(이름이 같은 함수) override;
// c++ 형변환. 부모->자식 형변환 : dynamic_cast. if문과 함께 사용해서 안전한 형변환 가능
// template 일반화 코드 작성하는 법

template <typename T>
class SingleTon
{
private:
	static T* singleton;
public:
	SingleTon() {}
	virtual ~SingleTon() {}
	static T* GetSingleton()
	{
		if (nullptr == singleton)
		{
			singleton = new T;
		}
		return singleton;
	}

	static void Release()
	{
		delete singleton;
		singleton = nullptr;
	}
};

template<typename T>
T* SingleTon<T>::singleton = nullptr;

// GameManager 클래스가 SingleTon 상속받는다. 
// SingleTon 클래스는 Gamemanager클래스를 내부적으로 사용하고 있다.
class GameManager : public SingleTon<GameManager>
{
private:
	// 멤버
public:
	GameManager() {}
	~GameManager() {}
	// 기능 : 게임 화면 출력, 게임 시작, 게임 종료
	void MainMenu()
	{
		std::cout << "메인 메뉴 시작" << std::endl;

		// while 반복문. inputnum .. 1 게임 시작. 2. 게임 종료 3. 게임 저장..

		while (true)
		{
			//system("cls");

			int userInput = 0;
			std::cout << "1. 게임 시작" << std::endl;
			std::cout << "2. 게임 종료" << std::endl;
			std::cin >> userInput;

			if (userInput == 1)
			{
				GameStart();
			}
			else if (userInput == 2)
			{
				GameEnd();
			}
			else
			{
				std::cout << "잘못된 입력, 다시 입력해주세요." << std::endl;
			}
		}
	}

	void GameStart()
	{
		std::cout << "게임 시작!" << std::endl;

		// 클래스 게임 이름.h 게임 이름.cpp 
		// Board board;   board.GamePlay();

		board b;
		b.GamePlay();
	}
	void GameEnd()
	{
		exit(0);
	}
};

int main(void)
{
	//std::cout << "Std 함수 예제" << std::endl;
	//SampleSTD* sample = new SampleSTD;
	//sample->SetWidthExample();
	//sample->IsDigitExampe();
	//delete sample;

	std::cout << "메인 화면" << std::endl;

	GameManager* gm = GameManager::GetSingleton();
	gm->MainMenu();

}