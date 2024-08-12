/*
* 학습 목표 : c언어 포인터 c++에서 활용법, 참조자(레퍼런스)에 대한 이해
* 작성일 : 2024-08-09
* 작성자 : 황은중
*/


#include "lectures.h"
#include <cstdio> // iostring
#include <cstring> // string

/*
* C언어에서 포인터를 사용하는 이유?
* 함수를 사용하면서 함수 안에서 데이터를 변경하려면 포인터를 인자로 넘겨줘야 한다.
*/

/*
* 함수를 사용할 때 포인터가 아닌 참조자를 사용하면 인자로 &(주소연산자)룰 사용하지 않을 수 있다.
* 주소 선언 : int*
* 참조자 선언 : int& 참조자 이름 = 참조하고자 하는 변수;
* int a;
* int& AnotherA = a;
*/

void SwapInt(int a, int b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// 함수 오버로딩 : C언어는 함수의 이름으로 함수를 구별한다 그러나 c++ 함수이름 + (매개변수, 인자)로 구분
void SwapInt2(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void SwapInt2(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void ChangeValue(int& p)
{
	const int& p1 = 10;// p의 값을 10으로 바꾸는 함수를 만들어보아라.
	p = p1;
}

int Function1() // int를 반환하는 함수
{
	int a = 2;
	return a;
}

// 참조자를 리턴하는 함수
int& Function2()
{
	int a = 2;
	return a;
}

int& Function3(int& a)
{
	a = 2;
	return a;
}

typedef struct Human
{
	char name[30]; // 홍길동
	int age; // 50
}Human;

// 정수형 레퍼런스를 반환하는 함수를 만들어 주세요.
// Human 구조체를 레퍼런스로 반환하는 함수를 하나 만들어 주세요.
// 
// Human 데이터를 넣는 함수
Human& AddHumanInfo(Human& human)
{
	// cin 함수를 이용해서 동적으로 데이터 입력하게 변경
	// strcpy_s(human.name, 30, "홍길동");
	char name2[30];
	std::cin >> name2;
	strcpy_s(human.name, 30, name2); // 왜 빈값이 나올까..?

	// cin 함수를 이용해서 동적으로 데이터 입력하게 변경
	// human.age = 50;
	std::cin >> human.age;
	return human;
}

void PrintHumanInfo(Human& human)
{
	std::cout << "이름 : " << human.name << std::endl;
	std::cout << "나이 : " << human.age << std::endl;
}



void lecture2()
{
	std::cout << "2강 " << std::endl;

	int num = 10; //num에는 10이라는 정수, 주소가 들어간다.
	int* numPtr = &num; // 포인터(변수) NULL을 해주지않으면 쓰레기 값이 들어간다.

	// c언어와 비교했을떄 c++는 데이터의 형태를 명시하지 않아도 작동한다 즉, 편리함이 있다.
	printf("포인터의 주소 %p\n", numPtr);

	std::cout << "포인터의 주소 : " << numPtr << std::endl;
	std::cout << "포인터가 가리키는 값 : " << *numPtr << std::endl; // *numPtr은 역참조를 뜻함

	// 변수의 이름 규칙
	int a; // 안좋은 예

	// 변수의 이름을 귀찮더라도 명확한 의미를 부여하는게 좋다.
	int number_of_people; // 단어와 단어사이를 '_' 로 구분하고있다. 
	int NumberOfPeople; // 띄어쓰기 할 때 대문자로 표현하고있다. 카멜방식

	// 주의사항 : 두가지 방식을 혼동 또는 혼용해서 사용하지 말 것

	int num1 = 1, num2 = 2;

	SwapInt(num1, num2); // 포인터를 안쓰는경우 값이 안바뀐다
	std::cout << "num1의 값 : " << num1 << std::endl << "num2의 값 : " << num2 << std::endl;

	SwapInt2(&num1, &num2); // 포인터를 쓰는경우 값이 정상적으로 바뀐다.
	std::cout << "num1의 값 : " << num1 << std::endl << "num2의 값 : " << num2 << std::endl;

	// 참조자 만드는 법
	// 참조자를 변수의 별명이라고 생각하면 편함
	int a1 = 10;
	int* a1Ptr = &a1;
	int& AnotherA1 = a1; // AnotherA1은 a1의 별명이다. 참조자는 기본적으로 메모리공간을 확보하지 않는다 

	std::cout << "AnotherA1의 값 : " << AnotherA1 << std::endl;

	// 그럼 그냥 a1쓰면 되는거아님?
	// -> Primitive type 은 그냥 써도 상관 없다.
	// 구조체의 크기는 사용자 정의형이기 때문에 작성자에 따라서 크기가 달라진다.
	// 참조자도 마찬가지로, 참조자가 가리키는 주소를 한번 복사하면 8바이트(64비트 시스템)만으로 구조체를 복사해서 쓸 수 있다.

	// 참조자와 포인터의 차이점?
	// 포인터는 주소연산자를 인자로 받게 해야한다. 사용자가 함수와 포인터에 대한 이해도가 높아야한다.
	// 그러나 참조자는 주소연산자를 인자로 받지않기때문에 사용자가 더 편리한 문법이다. (c++언어)


	int c_num2;
	std::cin >> c_num2; // C++
	std::cout << "c_num2의 값 : " << c_num2 << std::endl;

	// 참조자(Reference) 함수에서 사용하는 방법

	int d_num1 = 1, d_num2 = 2;
	SwapInt2(d_num1, d_num2);
	std::cout << "d_num1의 값 : " << d_num1 << std::endl << "d_num2의 값 : " << d_num2 << std::endl;

	// 참조자는 반드시 선언과 동시에 초기화를 해야한다.
	// 참조자는 선언할 때 상대의 주소를 가져와서 복사를 한다.
	// int& AnotherDNum1;는 에러가 난다.

	int& AnotherDNum1 = d_num1;

	// int& Literal = 100;도 에러가 난다. 즉 참조자는 리터럴 상수를 가리키지 못한다.

	const int& Literal = 100; // 참조자는 const키워드를 통해서 상수를 가리킬수 있다.
	 
	// ChangerValue;
	int p = 5;
	ChangeValue(p);
	std::cout << "p의 값 : " << p << std::endl;


	int p1 = 5;
	// 참조자(레퍼런스)를 리턴하는 함수
	int tempA = Function1(); // temA 는 Function1의 리턴값인 a의 값을 복사해서 대입한다.
	int tempB = Function2(); // temB = a;랑 같은 의미인데 지역변수 a는 함수가 끝나면 사라지므로 임시주소에 보관하게된다. 따라서 좋지않을 코드이다.
	int tempC = Function3(p1);
	// 레퍼런스 타입을 리턴할때는 반드시 지역변수를 반환하지 않도록 조심해야한다 ★★


	std::cout << tempA << std::endl;
	std::cout << tempB << std::endl;
	std::cout << tempC << std::endl;

	// int& anotherTemp = Function1();는 에러가난다.
	const int& anotherTemp = Function1();
	
	// int& anotherTemp2 = Function2();는 일부 컴파일러에서 에러가 발생한다.

	// (1) 함수에서 값을 리턴할 떄
	// int a = Function1(); a = 2; 2라는 값을 a에 대입한다. 값의 복사가 이루어졌다 즉, 사용가능
	// int& a = Function1(); 참조자 타입으로 리터럴 상수를 가르킬 수 없다. 컴파일 에러가 발생한다.
	// const int& a = Function1(); 참조자가 리터러를 가르치게 하고 싶으면 const 키워드를 사용한다
	// 단, const 수식 받는 a 참조자는 값의 변경이 불가능하다.

	// (2) 함수가 참조자를 리턴할 떄 int& Function1();
	// 레퍼런스 타입을 리턴할 때는 반드시 지역변수를 반환하지 않도록 조심해야 한다 ★★

	Human human;
	
	AddHumanInfo(human);
	PrintHumanInfo(human);
}
