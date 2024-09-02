// cin >> input; 숫자인지 아닌지 판별해주는 isdigit()메서드 활용
// setw() 가로의 길이를 일정하게 맞추어 주는 함수
// 포인터를 클래스로 표현한 것 -> iterator
// 문자열을 클래스로 표현한 것 -> string

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>

using namespace std;

class SampleSTD
{
public:
	SampleSTD() {}

	// 콘솔의 출력 관련 도우미 함수 (가로의 길이)
	// setw(숫자) : 숫자 만큼 크기를 채워서 맞춰준다.
	// left 왼쪽정렬 right 오른쪽정렬
	// 빈칸을 괄호안에있는 문자로 채워준다.

	void SetWidthExample()
	{
		int a = 42;
		int b = 12345;
		cout << setfill('=') << left << setw(20) << a << endl;
		cout << setfill('*') << right << setw(20) << b << endl;

		int waitnum;
		cout << "이 예제를 종료하려면 아무 숫자를 입력해주세요." << endl;
		cin >> waitnum;
		system("cls");
	}

	void IsDigitExample()
	{
		// 조건으로 숫자가 아니면 false, true 반환해주는 함수

		if (isdigit('5'))
		{
			cout << "참입니다." << endl;
		}

	}
};

// 포인터
// *ptr : 역참조
// ptr++ : (주소 + 1)
// ++ptr
class Iterator
{
private:
	int* ptr;
public:
	Iterator(int* p) : ptr(p) {}
	
	Iterator* operator++()
	{
		++ptr;
		return this;
	}
	Iterator* operator++(int)
	{
		Iterator* temp = this;
		++(*this);
		return temp;
	}
};

// Iterator 클래스 안에 std가 포함되어있다.
// 클래스 안에 포인터(Iterator 클래스)

