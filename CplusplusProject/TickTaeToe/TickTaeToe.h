#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

// 틱택토 게임
// 보드판    3x3 격자판을 만들어야한다. -> 클래스로 표현 class Board -> 2차원 배열 

// 기능1 : 플레이어가 돌을 그린다.   X 또는 O insert_X insert_O 
// 기능2 : x_Win,  o_Win
// 승리조건 :가로줄 완성,  세로줄 완성, 대각선(왼쪽 오른쪽 아래), 대각선(오른쪽 왼쪽 아래)

// 사용하면 좋은 함수들
// std::cin >> input;   숫자인지 아닌지 판별, std::isdigit()
// std::setw() 가로의 길이를 일정하게 맞추어 주는 함수
// 포인터를 클래스로 표현한 것 -> iterator
// 문자열을 클래스로 표현한 것 -> string

class board
{
	// bMap 들어있는 데이터가 숫자인지 아닌지 체크 하는 함수
	bool isNum(std::string& s);

private:
	int size;            // 크기가 3
	std::string** bMap; // 2차원 배열  [세로][가로]

public:
	board();

	void GamePlay();

	// 2차원 배열에 데이터 넣는 함수
	bool insert_x(int pos);
	bool insert_o(int pos);
	// 2차원 배열 안에 데이터가 있는지 없는지 체크 하는 함수
	std::string get_item(int pos) const;
	std::string get_item(int col, int row) const;

	// 보드판에 들어 있는 값을 출력해주는 함수
	void Print();

	bool x_win();
	bool o_win();

	int GetSize() const
	{
		return size;
	}

};

// std::cout 함수를 이용해서 클래스를 출력하겠다.
std::ostream& operator<< (std::ostream& out, const board& b);