#include <iostream>
#include "StdExample.cpp"
#include "TikTaeToe.h"

using namespace std;


// 클래스 키워드, 이름, 상속을 해야하면 상속을 선언
// 기능과 멤버 변수 선언 private, public, protected
// 생성자, 소멸자 선언 - 복사생성자, 얕은 복사 - 깊은 복사
// 상속 : virtual 키워드를 사용할지 말지.
// 다형성 표현  - 클래스의 확장성을 제공해준다.
// virtual 함수 (); 자식 함수(이름이 같은 함수) override;
// c++ 형변환. dynamic_cast (부모 -> 자식 형변환) if문과 함께 사용해서 안전한 형변환이 가능했다.
// template키워드를 사용하여 일반화 코드 작성하는법

template<typename T>
class SingleTon // 싱글톤패턴의 기본 틀이라 생각하자
{
private:
	static T* singleton;
public:
	SingleTon() {}
	virtual ~SingleTon() {}
	static T* GetSingleTon()
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
// Sington 클래스는 GameManager를 내부적으로 사용하고있다
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
		cout << "메인 메뉴 시작" << endl;
		
		while (true)
		{
			//system("cls");
			
			int userInput = 0;
			cout << "1. 게임 시작" << endl;
			cout << "2. 게임 종료" << endl;
			cin >> userInput;
			if(userInput == 1)
			{
				GameStart();

				Board b(3);
				b.GamePlay();
				b.PrintBoard();
			}
			else if(userInput == 2)

			{
				GameEnd();
			}
			else
			{
				cout << "잘못 입력하였습니다. 다시 입력해주십시오." << endl;
			}
		}
	}
	void GameStart()
	{
		cout << "게임 시작!" << endl;
	}
	void GameEnd()
	{
		exit(0);
	}
};

int main(void)
{
	/*cout << "Std 함수 예제" << endl;
	SampleSTD* sample = new SampleSTD;
	sample->SetWidthExample();
	sample->IsDigitExample();
	delete sample;*/

	cout << "메인 화면" << endl;
	GameManager* gm = GameManager::GetSingleTon();
	gm->MainMenu();
}