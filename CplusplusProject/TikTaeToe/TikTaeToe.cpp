#include "TikTaeToe.h"


Board::Board() {}

Board::Board(int size)
{
	this->size = size;

	board = new string*[size];
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
	cout << "틱택토 게임에 오신것을 환영합니다." << endl;
	cout << "보드의 사이즈는 " << size << "입니다" << endl;
	cout << "보드의 가장 좌측 하단의 좌표는 (1,1)이며 가장 우측 상단의 좌표는" << "(" << size << "," << size << ")" << "입니다." << endl;
	cout << "따라서 착수할 수 있는 x좌표와 y좌표의 범위는 " << 1 << "~" << size << "입니다." << endl;

	int count = 0;
	while (!X_Win() && !O_Win())
	{
		int posX;
		int posY;
		PrintBoard();
		if (count % 2 == 0)
		{
			cout << "O를 착수할 곳의 X 좌표를 입력하시오 : ";
			cin >> posX;
			cout << "O를 착수할 곳의 Y 좌표를입력하시오 : ";
			cin >> posY;
			if (Check(posX, posY))
			{
				Insert_O(posX, posY);
				count++;
			}
			else
			{
				cout << "그 곳엔 착수할 수 없습니다. 다시 착수해주세요." << endl;
			}
		}
		else
		{
			cout << "X를 착수할 곳의 X 좌표를 입력하시오 : ";
			cin >> posX;
			cout << "X를 착수할 곳의 Y 좌표를입력하시오 : ";
			cin >> posY;
			if (Check(posX, posY))
			{
				Insert_X(posX, posY);
				count++;
			}
			else
			{
				cout << "그 곳엔 착수할 수 없습니다. 다시 착수해주세요." << endl;
			}
		}
	}
	if (X_Win())
	{
		cout << "X가 승리하였습니다 !! " << endl;
	}
	else if (O_Win())
	{
		cout << "O가 승리하였습니다 !! " << endl;
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

void Board::Insert_O(int posX, int posY)
{
	board[size - posY][posX - 1] = "O";
}

void Board::Insert_X(int posX, int posY)
{
	board[size - posY][posX - 1] = "X";
}


bool Board::Check(int posX, int posY)
{
	if (posX < 1 || posY < 1 || posX > size + 1 || posY > size + 1)
	{
		return false;
	}
	else if (board[size - posY][posX - 1] == "X" || board[size - posY][posX - 1] == "O")
	{
		return false;
	}
	return true;
}

string Board::GetItem(int pos) const
{
	return string();
}

string Board::GetItem(int col, int row) const
{
	return string();
}

bool Board::X_Win()
{
	bool isXwin = false;
	// 가로 OR 세로 한줄 완성
	for (int i = 0; i < size; i++)
	{
		int Xcount = 0;
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == "X" || board[j][i] == "X")
			{
				Xcount++;
			}
		}
		if (Xcount == 5)
		{
			isXwin = true;
			break;
		}
	}

	// 오른쪽 아래 대각선
	int XDownCrossCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (board[i][i] == "X")
		{
			XDownCrossCount++;
		}
		if (XDownCrossCount == 5)
		{
			isXwin = true;
			break;
		}
	}

	// 오른쪽 위 대각선
	int XUpCrossCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (board[size - 1 - i][i] == "X")
		{
			XUpCrossCount++;
		}
		if (XUpCrossCount == 5)
		{
			isXwin = true;
			break;
		}
	}
	return isXwin;
}

bool Board::O_Win()
{
	bool isOwin = false;
	// 가로 OR 세로 한줄 완성
	for (int i = 0; i < size; i++)
	{
		int Ocount = 0;
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == "O" || board[j][i] == "O")
			{
				Ocount++;
			}
		}
		if (Ocount == 5)
		{
			isOwin = true;
			break;
		}
	}

	// 오른쪽 아래 대각선
	int ODownCrossCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (board[i][i] == "O")
		{
			ODownCrossCount++;
		}
		if (ODownCrossCount == 5)
		{
			isOwin = true;
			break;
		}
	}

	// 오른쪽 위 대각선
	int OUpCrossCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (board[size - 1 - i][i] == "O")
		{
			OUpCrossCount++;
		}
		if (OUpCrossCount == 5)
		{
			isOwin = true;
			break;
		}
	}
	return isOwin;
}

//ostream& operator<<(ostream& out, const Board& b)
//{
//	for (int i = 0; i < b.size; i++)
//	{
//		for (int j = 0; j < b.size; j++)
//		{
//			out << b.board[i][j];
//		}
//		out << endl;
//	}
//	return out;
//}
