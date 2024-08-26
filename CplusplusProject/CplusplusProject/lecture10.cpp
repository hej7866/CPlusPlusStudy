#include "lectures.h"


using namespace std;

/*
*  학습 목표 : 객체프로그래밍의 다형성
*  작정일    : 2024-08-26
*  작성자    : 황은중
*/

// Pet 클래스
// Dog, HuntDog, Cat : Pet을 상속하는 클래스
// (down, child, derived) // (up, parent, base)

// PetController Handler 클래스
// Has-A관계 play(Pet& pet)
// 1. 확장성의 문제점
// Play (Dog, Cat, Bird...) 확장해야 하는 클래스 만큼 오버로딩을 해야하는 문제가 발생
// 1-2 해결방안
// Play(Pet* pet) -> Pet 클래스 안에있는 PlayWithMaster();
// virtual - override


// 클래스 포인터와 상속 관계
// First 클래스 타입
// second 클래스 타입 ( First 클래스 + second 고유 멤버)

// First* a = new First();
// First* b = new second();

// second* a = new Second();
// second* b = new First(); // 안될 가능성이 있기 때문에 문법적으로 막아놨다.

class Water
{
private:
	int mL;
public:
	Water(int mL) : mL(mL) {}
	virtual void Show()
	{
		cout << mL << "mL" << endl;
	}
};

class SparklingWater : public Water
{
private:
	int sparkle;
public:
	SparklingWater(int mL, int sparkle) : Water(mL), sparkle(sparkle) {}
	void Show() override
	{
		Water::Show();
		cout << sparkle << endl;
	}
};

class First
{
private:
	char* str1;
public:
	First(const char* _str1)
	{
		str1 = new char[strlen(_str1 + 1)];
		strcpy_s(str1, strlen(str1), _str1);
	}
	virtual void SimpleFunc()
	{
		cout << str1 << endl;
	}
};

class Second : public First
{
private:
	char* str2;
public:
	Second(const char* _str1, const char* _str2) : First(_str1)
	{
		str2 = new char[strlen(_str2 + 1)];
		strcpy_s(str2, strlen(str2), _str2);
	}
	void SimpleFunc() override
	{
		cout << str2 << endl;
	}
};



class Handler
{

};

// c언어 형변환 (타입)이름;
// c++언어는 형변환 조건을 추가해서 연산자로 만듦.
// static_cast, dynamic_cast, reinterpret_cast, const_cast

// 1. static_cast 연산자 (static : 정적인)
// 2. dynamic_cast 연산자 (dynamic : 동적인)

// 첫번째. 기본 데이터 타입(primitive Type) : int, double, char 등의 형변환은 무조건 static_cast를 사용하라.

// 포인터, 참조자 사이의 형변환 연산자
// reinterpret_cast

/*
*  <<c++ 형변환 연산자 정리>>
* - 기본 자료형의 형변환은 static_cast를 사용하라.
* - 상속관계에서 형변환은 dynamic_cast를 사용하라.
* - 상속관계에서 강제로 형변환을 해야하는 경우에는 static_cast를 사용하라.
* - 포인터/참조 타입에서 무조건 형변환을 강제 시키려면 reinterpret_cast를 사용하라
* - const 성향을 없애려면 const_cast를 사용하라
*/

void lecture10()
{
	cout << "10강, 객체 지향프로그래밍 다형성" << endl;
	First* fptr = new First("첫번째 클래스");
	(*fptr).SimpleFunc();

	First* sptr = new Second("첫번째 클래스", "두번째 클래스");
	(*sptr).SimpleFunc();

	// 1번 예시 static_cast
	int d = 4;
	char* iPtr1 = (char*)d; // c스타일 형변환

	// reinterpret_cast 예시
	// 용도 : 포인터, 참조자 사이의 형변환을 강제로 실행시킨다.
	// perent* child*
	char* iPtr2 = reinterpret_cast<char*>(&d); 
	First* sptr2 = reinterpret_cast<First*>(fptr);

	// const_cast 연산자
	// 상수 키워드로 선언한 변수를 비 상수로 변경하는 연산자
	const char* str = "Hello"; // ROM에 저장되어 있기 때문에
	char* str2 = const_cast<char*>(str); // const_cast로 형변환을 하여도
	// 주의 사항 str2[2] = 'a'; // str2직접 접근해서 변경하는것은 불가능하다.
	cout << "const_cast 예시 : " << str2 << endl;

	char newChar = static_cast<char>(d); // 사용 가능한 경우

	// static_cast를 사용하는 이유
	// 1. static_cast는 강제 형변환을 아래 조건으로 제한하고 있다.
	// 다른 타입 간의 형 변환을 제한한다. (int <-> double <-> char)

	// 2. 부모 <-> 자식 클래스 형변환
	// Parent* parent = new Child();
	// (Child)parent;

	// dynamic_cast 연산자
	// 상속관계에서의 형변환을 안전하게 처리할 수 있는 연산자
	// static_cast의 경우에는 형변환이 불가능한 경우에도 컴파일을 허용하기 때문에
	// 상속관계에서 불안전한 형변환 방식이다.
	// 따라서 부모 자식 형변환을 할땐 dynamic_cast사용
	
	cout << "부모 자식 형변환 예시" << endl;
	
	// 부모 클래스를 자식 클래스로 형변환하라.
	Water* water = new SparklingWater(100, 10);
	(*water).Show();

	SparklingWater* spWater = dynamic_cast<SparklingWater*>(water); // 부모포인터(탄산수가 들어있는) 객체
	(*spWater).Show();

	Water* water2 = new Water(150);
	SparklingWater* spWater2 = dynamic_cast<SparklingWater*>(water2); // 부모포인터(부모 객체)가 들어있다.
	if (spWater2 != nullptr) {
		(*spWater2).Show();
	}
	

	// spWater2를 static_cast로 형변환을하면 그대로 컴파일 에러가 발생한다.
	// spWater2를 dynamic_cast로 형변환을 해서 그 결과값이 형변환이 불가능하면 nullPtr를 반환한다.
}