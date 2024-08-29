#include "lectures.h"

/*
*  학습 목표 : 함수 템플릿에대한 이해
*  작정일    : 2024-08-29
*  작성자    : 황은중
*/

/*
*  template 키워드 - 일반화 코딩
*  함수 템플릿
*  클래스 템플릿
*/

/*
*  template왜 사용하는가?
*  두 수를 더하는 함수(int 값 return)
*  함수 오버로딩 : 인자까지 포함해서 함수를 구분한다.
*  한번에 int, double, float.... 표현하는 방법이 없을까? template
*/

/*
*  template 사용 방법
*  함수 이름<데이터 타입>( )
*/

/*
*   용어 정리
*  	함수 템플릿 : template <typename T> 함수 정의. 함수를 만드는데 사용하는 템플릿을 의미한다.
*   템플릿 함수 : Add<int>(3,5);
*/

/*
*  함수 템플릿만 만들었는데, 언제 템플릿 함수가 생성되는가?
*  Add<int>(3,5);
*  int Add<int>(int num1, int num2)
* {
*	return num1 + num2;
* }
*  함수 템플릿을 선언하면 불필요한 메모리를 사용하는 것 아닙니까?
*  -> Add<int>(3,5); 코드가 작성되었을 때 (컴파일 시점에) int Add<int> 생성이 된다.
*  -> 컴파일 시점에 T 타입에	해당하는 함수를 만든다면 컴퓨터 속도가 느려지지는 않습니까?
*  -> 컴파일 <-> 런타임 시점 : 프로그램 시작 전에 함수가 전부 만들어 지기 때문에 프로그램 속도에 영향X
*/

/*
*  type T, 꼭 T라는 언어를 사용해야 되는가?
*  -> 다른 문자 사용해도 문제가 없습니다.
*/

template <typename T>
T Add(T num1, T num2)
{
	return num1 + num2;
}

/*
*  함수 템플릿의 전문화(Specializtion)
*/

template <>
char Add(char num1, char num2)
{
	std::cout << num1 << num2 << std::endl;
	return 0;
}

template <typename P>
P Minus(P num1, P num2)
{
	std::cout << "num1 에서 num2를 뺀 값 : ";
	return num1 - num2;
}

template <class C>
C Mulitply(C num1, C num2)
{
	return num1 * num2;
}

template <typename T>
T Divide(T num1, T num2)
{
	return num1 / num2;
}

// 권장 사항 : template <class T> 추천하지 않는다.
// class 클래스 이름 << 키워드와 혼동하는 경우가 있어서 template 키워드로 주로 사용한다.

// 타입의 종류가 두개 이상인 경우

template <typename T1, typename T2>
void ShowData(double a, double b)
{
	std::cout << "a를 T1으로 형변화한 값 : " << (T1)a << std::endl;
	std::cout << "b를 T2로 형변화한 값 : " << (T2)b << std::endl;
}

int Add(int num1, int num2)
{
	return num1 + num2;
}

double Add(double num1, double num2)
{
	return num1 + num2;
}

// Max 비교 (a , b) 큰 수를 리턴해주는 함수
// 문자 비교  aaa < bb : 길이가 더 긴 것을 더 크다.(재정의)	   - strlen(char*) -> 길이 비교
// a93 < b94  : 문자 안의 숫자가 더 큰것을 크다고 한다.(재정의)  - strcom -> 크기 비교


// Max

template <typename T>
T Max(T a, T b)
{
	return a < b ? b : a; // 같으면 a가 나오는 함수

	// 이항위의 코드와 정확히 일치한다.
	//if (a < b)
	//	return b;
	//else if (a > b)
	//	return a;

}

template <>
const char* Max<const char*>(const char* a, const char* b)
{
	return strlen(a) > strlen(b) ? a : b;
}

// Non-type 템플릿 : type이 아닌 템플릿

template <typename T, int val>
T AddValue(T const& curValue)
{
	return curValue + val;
}

const int EVENTMONEY = 10000; // int
const int EVENTEXP = 100;     // double

void lecture12()
{
	std::cout << "int Add(a,b) 출력 : " << Add(3, 5) << std::endl;
	std::cout << "double Add(a,b) 출력 : " << Add(3.4, 5.9) << std::endl;
	std::cout << "T Add<int>(a,b) 출력 : " << Add<int>(3, 5) << std::endl;
	std::cout << "float Add<float>(a,b) 출력 : " << Add<float>(3.4, 5.9) << std::endl;
	std::cout << Add<char>(32, 32) << std::endl;
	std::cout << Minus<int>(10, 5) << std::endl;

	ShowData<float, int>(3.2, 4.5);

	std::cout << "float Divide<float>(a,b) 출력 : " << Divide<float>(3.4, 2.3) << std::endl;

	std::cout << "Add 템플릿 함수의 전문화 " << std::endl;
	int num = Add<char>(97, 98);

	std::cout << "비교 함수 사용 예제" << std::endl;
	std::cout << Max<double>(3.2, 5.9) << std::endl;
	// 함수 템플릿에 <T 타입을 선언하지 않아도> 컴파일러가 묵시적 -> 제대로 변환 해준 경우. 잘못 변환 해준 경우
	std::cout << Max(3.2, 5.4) << std::endl;
	std::cout << Max("aaa", "bb") << std::endl;

	float myExp = 1.1f;
	int myMoney = 500;
	std::cout << "이벤트 후 경험치 : " << AddValue<float, EVENTEXP>(myExp) << std::endl;
	std::cout << "이벤트 후 돈 : " << AddValue<int, EVENTMONEY>(myMoney) << std::endl;
}