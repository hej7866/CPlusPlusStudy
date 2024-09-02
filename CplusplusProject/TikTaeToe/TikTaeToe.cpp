#include "TikTaeToe.h"



Board::Board() {}

Board::Board(int size)
{
	board = new string * [size];
	for (int i = 0; i < size; i++)
	{
		board[i] = new string[size];
		for (int j = 0; j < size; j++)
		{
			board[i][j] = "#";
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < size; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

void Board::GamePlay()
{
	while (true)
	{
		// 게임이 종료되면 승리를 선언하고 메인화면으로 돌아간다.
	}
}

void Board::PrintBoard()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

void Board::Insert_x(int pos)
{

}

void Board::Insert_y(int pos)
{

}

string Board::GetItem(int pos)
{
	return string();
}

bool Board::X_Win()
{
	return false;
}

bool Board::O_Win()
{
	return false;
}

//ostream& operator<<(ostream& out, const Board& b)
//{
//	// TODO: 여기에 return 문을 삽입합니다.
//}
