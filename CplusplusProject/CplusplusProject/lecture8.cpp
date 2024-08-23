#include "lectures.h"
#include <string>
/*
*  학습 목표 : c++ 상속 기본 문법에 대한 이해
*  작성일    : 2024-08-22
*  작성자    : 황은중
*/

/*
*  상속(inheritance) : 부모로 부터 유산을 이어받는 것
*  부모(클래스) <-> 자식(클래스) 상속한다 : private 멤버 변수 선언. public 함수를 선언해서 멤버 변수를 사용하였다.
*  부모가 가지고 있는 변수, 함수를 자식이 사용한다. 부모가 소유하고 있는 모든 것을 사용할 수 있었을까?
*/

/*
*  상속에서 자주 사용되는 용어 정리
*  상속을 해주는 클래스   vs    상속은 받는 클래스
*  부모(parent)          vs     자식(child)
*  기반(base)            vs     유도,파생(derived)
*  슈퍼(super)           vs     서브(sub)
*  상위                  vs     하위
*/

/*
*  상속의 기본 기능 : 부모 클래스(상속 하는 클래스)를 중복하지 않고 사용할 수 있는 문법이다.
*  클래스의 생성자 소멸자
*/

/*
*  접근 지정자
*  public    : public 범위 보다 큰 모든 멤버의 접근을 허용한다. private 이외의 모든 접근을 허용한다.
*  private   : 자신 클래스 이외의 모든 클래스의 접근을 막는다. 자식 클래스의 접근도 제한한다.
*  protected : 기본적으로 private과 용도가 같은데, 클래스가 상속되었을 때 자식 클래스의 접근을 허용하는 범위
*  c++ 특별한 상속 문법 : 다중 상속, 이중 상속	문제를 접근 지정자로 해결하기 위해서 private, protected 상속이 존재한다.
*/

/*
*  상속의 세가지 방법 : public 상속, private 상속, protected 상속
*  public 상속 : (부모 클래스)private 이외의 모든 접근을 허용한다. 부모가 갖고 있는 접근지정자와 동일하게 가져온다.
*  protected 상속 : (부모 클래스)private 이외의 모든 접근을 protected 접근으로 변경한다.
*  private 상속 : 모든 접근 지정자를 private로 변경한다. 재상속하는 이유가 없어지는 상속 방법.
*/

/*
*  ★★★★★ IS-A에 해당하는 경우에만 상속을 하세요.
*  상속을 언제 해야하는가?
*  IS-A	:   A is B 인가? A가 B인가요? Child(Parent + 추가적으로 Child 구현된 기능)가 Parent 인가요?
*  EBook은 책입니다. 책을 클래스 정의. EBook 책의 내용을 상속받을 수 있다.
*  정사각형은 사각형인가요?
*  HAS-A : A가 B를 소유하고 있다.  Police(자식)가 Gun(부모)을 소유하고 있다.
*  Police (경찰)
*  Gun(총)
*/

class Book
{
private:
	char* title;
	int price;
public:
	Book(const char* title, int price)
	{
		this->price = price;   //: price(price) 처리가 같다.
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
	~Book()
	{
		delete[] title;
	}

	void ShowBookInfo()	
	{
		std::cout << "제목 : " << title << std::endl;
		std::cout << "가격 : " << price << std::endl;
	}
};

class EBook : public Book
{
private:
	char* DRMkey;
public:
	EBook(const char* title, int price, const char* key) : Book(title, price)
	{
		DRMkey = new char[strlen(key) + 1];
		strcpy_s(DRMkey, strlen(key) + 1, key);
	}

	void ShowEBookInfo() 
	{
		ShowBookInfo();
		std::cout << "DRMKey의 값" << "wasdfwefiajed" << std::endl;
	}

	~EBook()
	{
		delete[] DRMkey;
	}
};

class Gun
{
protected:
	int bulletCount;
public:
	Gun(int bullet)
	{
		bulletCount = bullet;
	}
	void UseGun()
	{
		bulletCount--;
	}
	int ShowRemainBullet()
	{
		return bulletCount;
	}
};

class Police// IS - A,  Has - A  경찰이 총(소유(Has-A)는 하고 있습니다)입니까?
{
private:
	Gun* gun;
public:
	Police()
	{
		gun = new Gun(10);
	}
	void Shot()
	{
		gun->UseGun();
		std::cout << "발사!" << std::endl;
		std::cout << "남은 잔탄 수 : " << gun->ShowRemainBullet() << std::endl;
	}
};

class Police2 : public Gun
{
	// 경찰 중에 총을 소유안한 경찰이 있을 수 있나요? -> 소유할 수 도있고 안할 수 도 있다.
	// Has-A  Police 객체가 Gun을 상속해야할지 말아야할지 판단할 때 Gun클래스 소유안해도 되는 경우도 만들어야하는 case

	// bat*
};

class base
{
private:
	int num1;
protected:
	int num3;
public:
	base(int value, int value3) : num1(value), num3(value3) {}     // 멤버 이니셜라이저
	base()
	{
		std::cout << "base() 생성자 호출!" << std::endl;
	}
	void Print()
	{
		num1 = 1;
		std::cout << "base()" << num1 << std::endl;
	}
	~base()
	{
		std::cout << "base() 소멸자 호출!" << std::endl;
	}
};

class derived : public base
{
private:
	int num2;
public:
	derived(int value) : num2(value) {}
	derived()
	{
		std::cout << "derived() 생성자 호출!" << std::endl;
	}
	void dPrint()
	{
		num3 = 3;
		num2 = 2;
		std::cout << "drived()" << num2 << " " << num3 << std::endl;
	}
	~derived()
	{
		std::cout << "dervied() 소멸자 호출!" << std::endl;
	}
};

class parent
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;
};

class child : protected parent
{
	// num3의 접근 지정자가 protected 
};


// 예제 문제
// 정사각형(Square) 사각형(Rectangle)

class Rectangle
{
private:
	int width, height;
public:
	Rectangle(int width, int height) : width(width), height(height) {}
	void ShowAreaInfo()
	{
		std::cout << "넓이 : " << width * height << std::endl;
	}
};

class square : public Rectangle
{
public:
	square(int size) : Rectangle(size, size) {}
};
// 생성자 초기화
// Rectangle(int width, int height) : width(width), height(height)
// public : ShowAreaInfo ( width * height)
// 
// class Square : public Rectangle{} // 정사각형 가로의 세로의 길이가 같은 사각형 



void lecture8()
{
	std::cout << "8강 !" << std::endl;
	base b1(1, 3);
	b1.Print();
	derived d1;	  // 자식 클래스는 생성될 때 부모 클래스도 같이 생성해야 한다.
	d1.Print();
	d1.dPrint();

	// 예제 풀이

	Rectangle re(2, 4);
	re.ShowAreaInfo();
	square sq(5);
	sq.ShowAreaInfo();

	// protected 상속
	// 객체 지향의 정보 은닉 원칙을 지키려는 문법적 지원이다.
	parent p1;
	p1.num3 = 10;
	child c1;
	//c1.num3 = 100;

	// 전자책
	// EBook ebook("C++ 예제 문제", 10000,  "wwwssssddd");

	// 경찰
	Police police;
	police.Shot();

	// Pet 관리 프로그램.   상속으로 표현      Dog, Cat, Bird -> Pet 공통된 요소
	// Dog,Cat,Bird 돌봐주는 사람 player Pet이랑 상호작용을 한다.	playerController

}