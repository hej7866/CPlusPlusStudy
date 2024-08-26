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

	void Bark()
	{
		cout << "멍멍" << endl;
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
	void Hunting()
	{
		cout << "사냥개가 사냥을합니다." << endl;
	}

	//void PlayWithMaster() override
	//{
	//	cout << "사냥개와 놀아주었다." << endl;
	//	hungry -= 20;
	//	happy += 10;
	//}
};


class Cat : public Pet
{
public:
	Cat() {}
	Cat(int hungry, int happy) : Pet(hungry, happy) {}

	void Hide()
	{
		cout << "고양이가 숨었습니다." << endl;
	}
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

	// Pet 클래스를 이용해서 고유 함수를 실행시키고 싶다.
	// Pet을 고유 클래스로 타입변환 시키고싶다.
	// 문제. 모든Pet이 상속 받는 하나의 자식 클래스로 변환할 수 없다.
	// 조건이 필요해진다.
	
	// c언어 형변환 (타입)이름;
	// c++언어는 형변환 조건을 추가해서 연산자로 만듦.
	// static_cast, dynamic_cast, reinterpert_cast, const_cast

	void Play2() // Cat, Dog, Bird 고유한 함수를 만들어주세요. dynamic_cast형변환사용, if조건문으로 제한을 걸어서 표현
	{

		HuntDog* huntDog = dynamic_cast<HuntDog*>(myPet);
		if (huntDog != nullptr) {
			(*huntDog).Hunting();
		}
		
		Cat* cat = dynamic_cast<Cat*>(myPet);
		if (cat != nullptr) {
			(*cat).Hide();
		}

		Dog2* dog = dynamic_cast<Dog2*>(myPet);
		if (dog != nullptr) {
			(*dog).Bark();
		}
		/*HuntDog* huntDog = new HuntDog(100, 100);
		(*huntDog).Hunting();*/
	}

	void ShowInfo()
	{
		cout << "소지 금액 : " << money << endl;
		cout << "남은 행동력 : " << activePoint << endl;
		cout << "------펫의 정보------ : " << endl;
		myPet->ShowInfo();
	}
};

// 객체프로그래밍의 다형성 : 동일 형태로 복수의 기능을 구현
// 클래스를 확장할 때 마다 동일 함수의 오버로딩을 구현하는 것을 피하고 하나의 함수로 표현하기 위해서
// PetController의 변수 player.Play(); 형태가 모두 동일합니다.
// 결과는 모두 다릅니다.

// 공통된 함수 virtual PlayWithMaster();
// 이름과 반환 값이 같은 함수를 상속받는 클래스에 선언을 해줘야한다.

// Pet을 상속받는 클래스인데, 각 클래스 고유의 메소드를 실행하는 방법
// Hunting 실행하는 법.. Cat, Hide 실행을 하려면 어떻게 해야하는가?

// PlayWithCat(Cat* cat); (Cat& cat); cat->Hide();
// PlayWithDog(Dog* dog);
// PlayWithBird(Bird* Bird);

// 클래스를 상속하느 이유 첫 번째, PetController에서 Pet을 사용하는 공통된 함수로 한번에 표현한다.
// 두번째, 클래스 확장성. Pet->Dog, Cat, Bird 고유한 함수를 갖게된다. Cat, Dog, Bird 인자로 만드려고 하면 복잡해진다.
// 형변환(자식 <-> 부모) dynamic_cat : 형변환이 불가능하면 nullptr을 반환하는 특징이있다.

void lecture9()
{
	Pet pet(100, 100);
	Dog2 dog(100, 100);
	HuntDog huntDog(100, 100);
	Cat cat(100, 100);

	PetController player(&pet, 1000, 3);
	player.Play();
	player.Play2();
	player.ShowInfo();

	PetController player2(&dog, 1000, 3);
	player2.Play();
	player2.Play2();
	player2.ShowInfo();

	PetController player3(&huntDog, 1000, 3);
	player3.Play();
	player3.Play2();
	player3.ShowInfo();

	PetController player4(&cat, 1000, 3);
	player4.Play();
	player4.Play2();
	player4.ShowInfo();

}