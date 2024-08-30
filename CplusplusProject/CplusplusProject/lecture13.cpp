#include "lectures.h"

using namespace std;
/*
*  학습 목표 : 클래스 템플릿에대한 이해
*  작정일    : 2024-08-30
*  작성자    : 황은중
*/

/*
*  template 키워드
*  코드를 위한 틀을 만드는 것
*/
class One;

template <typename T>
void Plus(T a, T b)
{
	cout << a << "+" << b << "=" << a + b << endl;
}


template <typename T1, typename T2>
void SomeFunc(T1 a, T2 b) {}


template <typename T1>
void SomeFunc(T1 a, int b) {}


class One
{
public:
	void operator+(const One& one)
	{
		cout << "a + b의 연산자 오버로딩 출력" << endl;
	}
};

template<typename T>
class Point
{
private:
	T posX;
	T posY;
public:
	Point() {}
	Point(T x, T y) : posX(x), posY(y) {}
	void Show()
	{
		cout << "posX : " << posX << endl;
		cout << "posY : " << posY << endl;
	}
};

/*
* 클래스 템플릿과 함수 템플릿의 차이점
* 함수 템플릿은 함수를 호출 시에 <type>을 명시하지 않으면 인자를 통해서 타입을 유추한다. (묵시적으로 템플릿 함수를 선언한다.)
* 만약 일반함수가 존재한다면 일반 함수가 먼저 사용된다.
* 클래스 템플릿은 묵시적으로 타입을 지정해주는 기능이없다. 따라서 반드시 타입을 지정해주어야한다
*/

// non type template<typename T, int val>

template<typename T, int N>
class MyArray // 우리가 직접 만드는 배열
{
private:
	T data[N]; // N크기만큼 배열을 선언하겠다.
public:
	MyArray() {}
	MyArray(T(&arr)[N]) // 배열을 복사해서 저장하는 생성자
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = arr[i];
		}
	}

	T* GetArray() { return data; }
	int Size() { return N; }

	void ShowInfo()
	{
		for (int i = 0; i < N; i++)
		{
			cout << data[i] << ",";
		}
		cout << endl;
	}
};

/*
* C++ << 언리얼 엔진, 클래스 만드는 법을 배웠다 -> 객체 지향 프로그래밍의 특징들이있었다.
* 추상화 : 현실에 존재하지 않는 것도 코드로 표현하는 것
* 정보은닉, 캡슐화 -> 프로그래머 실수를 방지
* 다형성
* STL << Standard Template Library
* - 안전성이 보장이된다.
* - Template : 데이터 타입을 모두 대응하는 일반화 프로그래밍
* Vector<Item> 가변 배열 << 자료 구조
*/

// 플레이어 <-> 몬스터 배틀 시스템 
// 배틀종료시스템, 점수 시스템, 저장기능, 종료기능, 시작기능, 불러오기기능.. (게임을 관리해주는 기능들)
// GameManager 클래스를 만들어보자

// 점수, 저장 GameManager GM; 
// 시작, 종료 GameManager GM2; 
// 클래스가 한개만 존재해야 하는 패턴화 -> 싱글톤 패턴
// template 클래스를 표현하면 -> 싱글톤 패턴이 필요한 클래스를 모두 사용할 수 있다.
// 상속 + 템플릿 클래스


template<typename T>
class SingleTon
{
	// 반드시 객체가 하나만 있어야 한다.
private:
	static T* singleTon;
public:
	SingleTon() {}
	virtual ~SingleTon() {}
	static T* GetSingleTon()
	{
		if (nullptr == singleTon)
		{
			singleTon = new T;
		}
		return singleTon;
	}

	static void Release()
	{
		delete singleTon;
		singleTon == nullptr;
	}
};

// 이부분 없으면 에러가남
template<typename T>
T* SingleTon<T>::singleTon = nullptr;

class GameManager : public SingleTon<GameManager>
{
private:
	int score;
public:
	GameManager() {}
	~GameManager() {}
	GameManager(int s) : score(s) {}
	int GetScore() { return score; }
	void SetScore(int val) { score = val; }

	// 게임시작, 게임 종료, 게임 저장 ....
	void GamaStart()
	{
		cout << "게임 시작" << endl;
	}
	void GamaEnd()
	{
		cout << "게임 종료" << endl;
	}
	void GamaSave()
	{
		cout << "게임 저장" << endl;
	}
};

// GameData 플레이타임, 현재 진행중인 챕터..
class GamaData : public SingleTon<GamaData>
{
private:
	int areaInfo; // 1번지역
public:
	GamaData() {}
	
	int GetAreaInfo() { return areaInfo; }
	void SetAreaInfo(int area) { areaInfo = area; }
};

void lecture13()
{
	Plus<int>(3, 5);

	Point<int> p1(1, 2);
	p1.Show();
	Point<float> p2(1.1, 2.2);
	p2.Show();

	// 배열
	int arrNum[3] = { 1, 5, 9 };
	MyArray<int, 3> myArray(arrNum);
	cout << "MyArray 클래스의 크기 : " << myArray.Size() << endl;
	myArray.ShowInfo();

	double arrDouble[4] =  { 1.1, 5.1, 9.3, 4.3 };
	MyArray<double, 4> myArrayD(arrDouble);
	cout << "MyArray 클래스의 크기 : " << myArrayD.Size() << endl;
	myArrayD.ShowInfo();

	cout << "GamaManager 클래스" << endl;

	GameManager* gm = GameManager::GetSingleTon();
	gm->SetScore(100);
	GameManager* gm2 = GameManager::GetSingleTon();
	gm2->SetScore(150);
	cout << gm->GetScore() << endl;
	cout << gm2->GetScore() << endl;

	// 게임 시작
	gm->GamaStart();
	// 게임 메뉴

	// 메인 플레이

	// 종료
	gm->GamaEnd();

	GamaData* gameData = GamaData::GetSingleTon();
	gameData->SetAreaInfo(10);
	cout << gameData->GetAreaInfo() << endl;

	GamaData* gameData2 = GamaData::GetSingleTon();
	cout << gameData2->GetAreaInfo() << endl;
}