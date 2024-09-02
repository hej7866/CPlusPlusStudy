#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// 틱택토 게임
// 3by3 보드판을 만들어야한다 -> 클래스로 표현
// 기능 : 플레이어가 돌을 그린다 x 또는 o insert_x insert_o insert(char c)
// 기능 : x가이기거나 o가 이기거나
// 가로줄 완성, 세로줄 완성, 대각선(왼쪽위 오른쪽아래) (오른쪽위 왼쪽아래)

// cin >> input; 숫자인지 아닌지 판별해주는 isdigit()메서드 활용
// setw() 가로의 길이를 일정하게 맞추어 주는 함수
// 포인터를 클래스로 표현한 것 -> iterator
// 문자열을 클래스로 표현한 것 -> string

class Board
{
private:
	int size; // 3이면 3x3
	string** board; // 2차원 배열 [가로][세로]
public:
	Board();

	void GamePlay();
	// 2차원 배열에 데이터 넣는 함수
	void Insert_x(int posX);
	void Insert_y(int posY);

	// 2차원 배열 안에 데이터가 있는지 없는지 체크하는 함수
	string GetItem(int pos);
	
	bool X_Win();
	bool O_Win();

	int GetSize() { return size; }

};


// cout함수를 이용해서 클래스를 출력하겠다.
ostream& operator<< (ostream& out, const Board& b);
