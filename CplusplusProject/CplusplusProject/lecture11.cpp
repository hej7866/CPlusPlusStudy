#include "lectures.h"

using namespace std;

/*
*  학습 목표 : 객체프로그래밍의 다형성2
*  작정일    : 2024-08-27
*  작성자    : 황은중
*/

/*
* 1. c++ 캐스팅 연산자
* 
* 2. virtual 가상 함수에 대한 이해[객체지향프로그래밍의 다형성]
* pure virtual
* abstract 클래스
* vtable
* 
* 3. monster class - Player와 전투
* 4. 전투 결과로 Reward - monster죽었을 때 보상하는 아이템
*/

class AA
{
private:
	int Aint;
public:
	virtual void Show()
	{
		cout << "AA" << endl;
	}
};

class BB : public AA
{
public:
	void Show()
	{
		cout << "BB" << endl;
	}
	void MyBB()
	{
		cout << "MyBB" << endl;
	}
};

class CC : public AA
{
public:
	void Show()
	{
		cout << "CC" << endl;
	}
	void MyCC()
	{
		cout << "MyCC" << endl;
	}
};


// 2. virtual 가상 함수에 대한 이해[객체지향프로그래밍의 다형성]
// pure virtual
// abstract 클래스
// vtable

class NewPet
{
public:
	virtual void Sound() = 0; // 순수 가상 함수 기능(pure virtual function) -> NewPet을 상속받는 Dog, Cat Sound를 실행시켜라
};

// pure virtual function
// 기능 : 반드시 오버라이딩 되어야 하는 함수
// 순수 가상 함수를 포함하고 있는 클래스 추상 클래스라고 정의합니다.
// 추상 클래스는 반드시 하나 이상의 상속이 필요하다.

// virtual 키워드를 포함하고 있는 가상함수는 상속하는 클래스를 모두 참조해서 사용할 수 있다.
// 그러면 모든 함수를 virtual 키워드로 선언해도 문제가 없지 않나요?? 에러가 발생하는것은 아니다 그러나

// virtual 키워드를 사용하면 내부적으로 vtable 공간을 생성한다.
// virtual 선언하지 않았을 때 바로 해당함수를 실행하기 때문에 속도가 빨리 처리가 된다.

// 따라서 다형성이 필요할 때만 가상함수를 사용하는 것이 최적화 된 코드를 짜는 방법이다.

class NewDog : public NewPet
{
public:
	virtual void Sound()
	{
		cout << "멍멍!" << endl;
	}

	virtual void Play() // 이게 좋은 방법일까?
	{
		cout << "개랑 놀기" << endl;
	}

	void DDD()
	{
		cout << "DDD" << endl;
	}
};

// Monster class - 추상 클래스로 표현
// reward class - 경험치, 재화, 아이템(아이템 번호, item, quest item)

// player <-> monster 배틀시스템
// battle class. public : bool End() : 플레이어가 죽었을 때, 몬스터가 죽었을 때, 도주를 성공하였을 때
// 무한 반복(전투의 끝을 의미하는 bool)
// 1. player turn (1) 공격 (2) 방어 (3) 도주
// NextTurn
// 2. monster turn (1) 공격

// 몬스터가 죽으며 monster class Has, Is -> Reward Drop Item()
// Player.GetItem(monster* m1);


void lecture11()
{
	cout << "c++ casting 연산자" << endl;
	cout << "1. static_cast<type>" << endl;
	// 기본 자료형의 변환, 포인터 및 참조 변환, 상속 관계의 클래스 변환에 사용될 수 있다.

	double pi = 3.14; // 3
	int pi_int = 3.14 - 0.14; // 3의 근사치 값이 반환된다.
	int pi_int2 = (int)(3.14 - 0.14); // 3이 반환된다.
	int pi_int3 = static_cast<int>(pi);

	cout << "pi_int의 값 : " << pi_int << endl;
	cout << "pi_int2의 값 : " << pi_int2 << endl;
	cout << "pi_int3의 값 : " << pi_int3 << endl;

	// 첫번째, 가상 함수를 이용하여 객체의 다형성 표현
	AA* aptr1 = new AA();
	(*aptr1).Show();
	AA* aptr2 = new BB();
	(*aptr2).Show();
	AA* aptr3 = new CC();
	(*aptr3).Show();
	// static_cast 상속관계의 클래스 표현

	BB* bptr1 = static_cast<BB*>(aptr2);
	(*bptr1).Show();
	(*bptr1).MyBB();

	BB* bptr2 = static_cast<BB*>(aptr3); // 강제로 형변환
	(*bptr2).Show();
	(*bptr2).MyBB();

	// 상속 사이의 클래스의 형변환 dynamic_cast

	CC* cptr1 = dynamic_cast<CC*>(aptr3);
	if (cptr1 != nullptr) {
		(*cptr1).MyCC();
	}

	// const_cast : const 키워드를 수식받는 변수의 상수성을 제거하는 변환.

	const int num = 10;
	int* noneConstNum = const_cast<int*>(&num);
	*noneConstNum = 12;
	cout << "num의 값 : " << num << endl;
	cout << "noneConstNum의 값 : " << *noneConstNum << endl;

	// reinterpret_cast

	// int 16 = 00000000 00000000 00000000 00001000(2)

	int num2 = 65; // int형 주소값을 char 주소로 강제 형변환을 해보고싶다.
	char* charPtr = reinterpret_cast<char*>(&num2);
	cout << "char 형태로 강제 형변환 : " << *charPtr << endl;

	// 데이터가 담겨있는 유실을 신경쓰지 않고 강제로 형변환.
	double* intPtrValue = reinterpret_cast<double*>(&num2);
	cout << "정수를 강제로 실수로 형변환 : " << *intPtrValue << endl;

	NewPet* np1 = new NewDog();
	(*np1).Sound();

	NewDog* nd1 = dynamic_cast<NewDog*>(np1);
	(*nd1).Play();
}