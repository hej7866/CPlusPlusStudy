#include "lectures.h"

using namespace std;
/*
*  학습 목표 : 클래스 상속2
*  작정일    : 2024-08-23
*  작성자    : 황은중
*/

/*
* 객체 포인터 참조 관계
* 씨플플에서 포인터 변수는 해당 객체를 직접 혹은 간접적으로 가르킬 수 있다.
* Dog : public Pet
* Pet* pet; : 가능
* Pet* dog; : 상속된 클래스를 부모 포인터가 가르킬 수 있다.
* Dog* dog;
* Dog* pet; : 컴파일 에러 : 문법적으로 자식 클래스 포인터가 부모 클래스를 직접 가르키는 것을 막아두었다. -> 형변환을 시키면 가능하다.
* (Pet)Dog
*/

/*
* 정리 : 클래스의 확장성에 대한 문제를 개선하기 위한 방안1.
* Cat클래스도 Play(Dog* dog) Play(Cat* cat), Feed 함수로 표현
* Cat과 Dog를 동시에 상속하는 Pet클래스를 인자로 넘겨준다.
* Play(Play* pet) <- Dog
*/

/*
* 부모 클래스를 인자로 사용해서 범용성 있는 함수를 구현하였다.
* void Play(Pet* pet) <- Dog
*/

/*
* 부모 클래스를 인자로 사용해서 범용성 있는 함수를 구현하였다.
* void Play(Pet* pet) -> pet를 상속받는 모든 클래스를 범용적으로 표현가능하게 함.
* 문제가 발생했다. pet을 상속받는 Dog, HuntDog 자식 클래스와 부모 클래스가 같은 함수를 구현을 했는데
* -> 부모가 갖고 있는 함수를 자식 버전으로 변경하고 싶다.
* 가상 함수, override 키워드
* virtual 키워드 -> 가상 함수
* override 키워드 -> virtual과 함께 사용된다.
*/

/*
* Pet*     a  = pet;  (o)
* Pet*     b  = dog;  (o)
* Pet*     c  = hdog; (o)
* 
* Dog*     a  = pet;  (x)
* Dog*     b  = dog;  (o)
* Dog*     c  = hdog; (o)
* 
* HuntDog* a  = hdog; (o)
* HuntDog* b  = dog;  (x)
* HuntDog* c  = pet;  (x)
*/

class Pet // 플레이어가 추상적인 대상으로 접근할 수 있는 객체
{
protected:
	int hungry;
	int happy;
public:
	Pet();
	Pet(int hungry, int happy) : hungry(hungry), happy(happy)
	{
		cout << "Pet을 생성했습니다." << endl;
	}
	void ShowInfo()
	{
		cout << "배고픔 : " << hungry << endl;
		cout << "행복도 : " << happy << endl;
	}
	virtual void PlayWithMaster()
	{
		cout << "펫과 놀아주었다." << endl;
		hungry -= 10;
		happy += 5;
	}
};

class Dog2 : public Pet
{
public:
	Dog2() {}
	Dog2(int hungry, int happy) : Pet(hungry, happy)
	{
		cout << "개를 생성했습니다." << endl;
	}
	void PlayWithMaster() override // virtual 함수로 작성된 함수가 있으면 반드시 이 함수로 override해라.
	{
		cout << "개와 놀아주었다." << endl;
		hungry -= 10;
		happy += 5;
	}
};

class HuntDog : public Dog2
{
public:
	HuntDog() {}
	HuntDog(int hungry, int happy) : Dog2(hungry, happy)
	{
		cout << "사냥개를 생성했습니다." << endl;
	}
	void Hunting();

	//void PlayWithMaster() override
	//{
	//	cout << "사냥개와 놀아주었다." << endl;
	//	hungry -= 20;
	//	happy += 10;
	//}
};

class Cat : public Pet
{

};

class PetController
{
private:
	Pet* myPet;
	int money;
	int activePoint;

	void UseActivePoint()
	{
		cout << "행동력을 1 소모했습니다." << endl;
		activePoint--;
		cout << "남은 행동력 : " << activePoint << endl;
	}
public:
	PetController() {};
	PetController(Pet* pet, int money, int activePoint) : money(money), activePoint(activePoint)
	{
		myPet = pet;
	}
	void EarnMoney(int pay)
	{
		cout << pay << "만큼 돈을 소모하였습니다." << endl;
		UseActivePoint();
		money += pay;

	}
	void Play()
	{
		myPet->PlayWithMaster();
		UseActivePoint();
	}
	void ShowInfo()
	{
		cout << "소지 금액 : " << money << endl;
		cout << "남은 행동력 : " << activePoint << endl;
		cout << "------펫의 정보------ : " << endl;
		myPet->ShowInfo();
	}
};

void lecture9()
{
	Pet pet(100, 100);
	Dog2 dog(100, 100);
	HuntDog huntDog(100, 100);
	PetController player(&pet, 1000, 3);
	player.Play();
	player.ShowInfo();

	PetController player2(&dog, 1000, 3);
	player2.Play();
	player.ShowInfo();

	PetController player3(&huntDog, 1000, 3);
	player2.Play();
	player.ShowInfo();
}