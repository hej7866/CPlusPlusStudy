# include "lectures.h"

/*
* 학습 목표 : 복사생성자에 대한 이해 및 소멸자
* 작성일 : 2024-08-16
* 작성자 : 황은중
*/

// 몬스터 클래스를 만들어보기
// 스타크래프트에 등장하는 마린을 객체로표현

// 클래스의 소멸자에 대한 학습
// new 키워드가 포함된 생성자를 구현했을 때, new 키워드로 생성한 변수의 메모리를 해제를 못하는 문제점
// 클래스가 소멸하는 시점에 호출되는 소멸자를 구현해서 delete 키워드로 메모리를 해제해주었다.

// 복사생성자를 이용해서 클래스를 복사한다.
// 자기자신 클래스를 복사해서 다른 클래스에 복사하는 생성자입니다.

// 얕은복사 vs 깊은 복사
// 얕은 복사 : 복사를 할 떄 주소를 그대로 가져와서 같은 주소를 가르키는 복사 방식
// -> 주소를 복사할 떄 다른 주소가 먼저 메모리 해제가 되면 없는 주소를 가리키는 에러 발생.
// 깊은 복사 : 복사할 때 주소인 경우에 해당 공간을 동적할당으로 복사해서 새로운 공사를 복사하는 방식
//
// 얕은 복사를 쓰는 이유? 하나의 메모리로 둘 이상을 표현할 수 있다. but 메모리 해제 시 문제가 발생할 수 있다.



class Marine
{
private:
	int hp;
	int atk;
	int posX;
	int posY;
	bool isDead;
	char* name;
public:
	Marine(int x, int y); // 배럭의 위치에서 마린이 생선된다.
	Marine(int x, int y, const char* marineName); // 클래스 멤버인 name을 marineName로 복사하는 것 const한정해서, marineName이 변하지 않는다는 것을 명시
	Marine(const Marine& m1); // 복사생성자 호출 방식
	~Marine(); // 소멸자 : 소멸할 때 호출된다.
	void Move(int x, int y);
	int Attack();
	void Damaged(int Damage);
	void ShowStatus();
};

Marine::Marine(int x, int y)
{
	hp = 50;
	atk = 5;
	posX = x;
	posY = y;
	isDead = false;
}

Marine::Marine(int x, int y, const char* marineName)
{
	// 동적인 복사 방식 : 복사하고자 하는 문자열의 길이 만큼 메모리 공간을 할당해서 생성한다.
	name = new char[strlen(marineName) + 1]; // strlen은 문자열의 길이를 반환해주는 함수 (null을 포함하지 않기 떄문에 +1 해주어야함)
	strcpy_s(name, strlen(marineName) + 1, marineName);
	hp = 50;
	atk = 5;
	posX = x;
	posY = y;
	isDead = false;
}

Marine::Marine(const Marine& m1)
{
	name = new char[strlen(m1.name) + 1]; // strlen은 문자열의 길이를 반환해주는 함수 (null을 포함하지 않기 떄문에 +1 해주어야함)
	strcpy_s(name, strlen(m1.name) + 1, m1.name);
	hp = m1.hp;
	atk = m1.atk;
	posX = m1.posX;
	posY = m1.posY;
	isDead = m1.isDead;
}

Marine::~Marine()
{
	std::cout << name << "의 소멸자 호출!" << std::endl;
	delete[] name; // delete[] : 배열을 전체 메모리 해제하라.
}

void Marine::Move(int x, int y)
{
	posX = x;
	posY = y;
}

int Marine::Attack()
{
	return atk;
}

void Marine::Damaged(int Damage)
{
	hp -= Damage;

	if (hp <= 0) {
		isDead = true;
	}
}

void Marine::ShowStatus()
{
	std::cout << "** 마린 생성 **" << std::endl;
	std::cout << "이름 : " << name << std::endl;
	std::cout << "위치 : " << posX << "," << posY << std::endl;
	std::cout << "공격력 : " << atk << std::endl;
	std::cout << "현재 체력 : " << hp << std::endl;
}

void lecture6()
{
	// 마린1을 생성해보기.
	Marine marine1(1, 2, "marine1");
	marine1.ShowStatus();

	// 마린2를 생성해보기
	Marine marine2(5, 10, "marine2");
	marine2.ShowStatus();

	std::cout << "마린1이 마린2를 공격" << std::endl;
	marine2.Damaged(marine1.Attack());
	marine2.ShowStatus();

	// 여러마리의 마린을 한번에 생성해본다. -> 배열을 사용
	Marine* marines[100];

	marines[0] = new Marine(2, 3, "marine3");
	marines[1] = new Marine(3, 5, "marine4");
	marines[0]->ShowStatus();
	marines[1]->ShowStatus();

	delete marines[0];
	delete marines[1];

	// int형 값 복사
	int num = 10;
	int num2 = num;
	int num3(num); // num3(num) num 데이터 복사 num3에 대입

	std::cout << num3 << std::endl;

	// Marine형 복사생성자 호출 (디폴트 복사생성자)
	// 디폴트 복사생성자의 한계 : 클래스의 멤버 변수로 포인터의 변수가 주소를 가리키는 경우에 얕은 복사로 복제한다.
	// 기존 메모리 소멸 시 주소를 찾을 수 없는 문제가 발생한다.
	Marine marine3(0, 0, "마린1");
	Marine marine4 = marine3;
	Marine marine5(marine3);


	marine5.ShowStatus();

	// marine3 소멸자호출 -> marine4 소멸자호출 -> marine5 소멸자호출
}


// 1. 질럿 클래스 생성
// 2. 생성자와 소멸자 (체력과 이름을 초기화하고, 소멸할 때 동적할당 한 주소를 세세하게 만들 것
// 3. 복사생성자를 명시적으로 작성해서 , 얕은 복사가 아닌 깊은 복사 방식으로 복사할 수 있게 코드를 구성할 것

class Zealot
{
private:
	int hp;
	int sd;
	int atk;
	int posX;
	int posY;
	bool isDead;
	char* name;
public:
	Zealot(int x, int y, const char* name);
	Zealot(const Zealot& z1);
	~Zealot();
	void Move(int x, int y);
	int Attack();
	void Damaged(int Damage);
	void ShowStatus();
};



Zealot::Zealot(int x, int y, const char* zealotName)
{
	name = new char[strlen(zealotName) + 1]; // strlen은 문자열의 길이를 반환해주는 함수 (null을 포함하지 않기 떄문에 +1 해주어야함)
	strcpy_s(name, strlen(zealotName) + 1, zealotName);
	hp = 100;
	sd = 100;
	atk = 15;
	posX = x;
	posY = y;
	isDead = false;
}

Zealot::Zealot(const Zealot& z1)
{
	name = new char[strlen(z1.name) + 1]; // strlen은 문자열의 길이를 반환해주는 함수 (null을 포함하지 않기 떄문에 +1 해주어야함)
	strcpy_s(name, strlen(z1.name) + 1, z1.name);
	hp = z1.hp;
	sd = z1.sd;
	atk = z1.atk;
	posX = z1.posX;
	posY = z1.posY;
	isDead = z1.isDead;
}

Zealot::~Zealot()
{
	std::cout << name << "의 소멸자 호출!" << std::endl;
	delete[] name; // delete[] : 배열을 전체 메모리 해제하라.
}

void Zealot::Move(int x, int y)
{
	posX = x;
	posY = y;
}

int Zealot::Attack()
{
	return atk;
}

void Zealot::Damaged(int Damage)
{
	sd -= Damage;
	if (sd <= 0) {
		hp -= Damage;
	}

	if (hp <= 0 && sd <=0) {
		isDead = true;
	}
}

void Zealot::ShowStatus()
{
	std::cout << "** 질럿 생성 **" << std::endl;
	std::cout << "이름 : " << name << std::endl;
	std::cout << "위치 : " << posX << "," << posY << std::endl;
	std::cout << "공격력 : " << atk << std::endl;
	std::cout << "현재 쉴드 : " << sd << std::endl;
	std::cout << "현재 체력 : " << hp << std::endl;
}


void lecture6_2()
{
	Zealot z1(0, 0, "질럿1");// 클래스 2개이상 생성 후 생성자와 소멸자를 각각 호출시켜 보세요
	Zealot z2(z1); // 복사생성자 호출방식
	// Zealot z2 = z1;  // Zealot z2 = z1 => Zealot z2(z1) 컴파일러가 바꾸어서 실행 
	Marine marine6(3, 3, "마린6");
	marine6.Damaged(z1.Attack());
	marine6.ShowStatus();

	z1.Damaged(marine6.Attack());
	z1.ShowStatus();
	z2.ShowStatus();
}
