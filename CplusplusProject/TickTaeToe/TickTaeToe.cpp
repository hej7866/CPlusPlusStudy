#include "TickTaeToe.h"

bool board::isNum(std::string& s) // 3x3  , 4x4   10, 99   
{
	// 조건 : bMap 데이터가 숫자면 true,  문자면 false;
	std::string::const_iterator it = s.begin();

	while (it != s.end() && std::isdigit(*it))
	{
		++it;
	}

	return !s.empty() && it == s.end();
}

board::board() // 생성자. size 3.
{
	size = 3;
	bMap = new std::string * [size];

	// 이차원배열[세로][가로]

	for (int i = 0; i < size; i++)
	{
		bMap[i] = new std::string[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::string num = std::to_string((i * size) + j);
			bMap[i][j] = num;
		}
	}
}

bool board::insert_x(int pos)
{
	int col = pos / size;
	int row = pos % size;

	// 숫자를 X로 바꾸겠다. 조건 : O, X 없을 때만
	if (isNum(bMap[col][row]))
	{
		bMap[col][row] = "X";
		return true;
	}
	else
	{
		return false;
	}

}

bool board::insert_o(int pos)
{
	int col = pos / size;
	int row = pos % size;

	if (isNum(bMap[col][row]))
	{
		bMap[col][row] = "O";
		return true;
	}
	else
	{
		return false;
	}
}

std::string board::get_item(int pos) const
{
	// 7   ->  bMap[세로(0~)x Size + 가로(0~)] col = 2, row = 2

	int col = pos / size;
	int row = pos % size;

	return bMap[col][row];
}

std::string board::get_item(int col, int row) const
{
	return bMap[col][row];
}

void board::Print()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << bMap[i][j];
		}
	}
}

bool board::x_win()
{
	// 1. 가로 줄 완성
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; i < size; j++)
		{
			if (bMap[i][j] != "X")
				break;
			if (j == (size - 1))
				return true;
		}
	}

	// 2. 세로 줄 완성

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; i < size; j++)
		{
			if (bMap[i][j] != "X")
				break;
			if (i == (size - 1))
				return true;
		}
	}

	// 3. 왼쪽 위 - > 아래 대각선

	for (int i = 0; i < size; i++)
	{
		if (bMap[i][i] != "X")
			break;
		if (i == (size - 1))
			return true;
	}

	// 4. 오른 위 - > 왼쪽 아래 대각선
	for (int i = 0; i < size; i++)
	{
		if (bMap[(size - 1) - i][i] != "X")
			break;
		if (i == (size - 1))
			return true;
	}

	return false;
}

bool board::o_win()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; i < size; j++)
		{
			if (bMap[i][j] != "O")
				break;
			if (j == (size - 1))
				return true;
		}
	}

	// 2. 세로 줄 완성

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; i < size; j++)
		{
			if (bMap[i][j] != "O")
				break;
			if (i == (size - 1))
				return true;
		}
	}

	// 3. 왼쪽 위 - > 아래 대각선

	for (int i = 0; i < size; i++)
	{
		if (bMap[i][i] != "O")
			break;
		if (i == (size - 1))
			return true;
	}

	// 4. 오른 위 - > 왼쪽 아래 대각선
	for (int i = 0; i < size; i++)
	{
		if (bMap[(size - 1) - i][i] != "O")
			break;
		if (i == (size - 1))
			return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const board& b)
{
	for (int i = 0; i < b.GetSize(); ++i)
	{
		out << std::endl;

		for (int j = 0; j < b.GetSize(); ++j)
		{
			out << "----";
		}
		out << "-" << std::endl << "│";

		for (int j = 0; j < b.GetSize(); ++j)
		{
			std::string item = b.get_item(i, j);
			int len = item.length();

			if (len <= 1)
				out << std::setw(2) << item << std::setw(2) << "│";
			else if (len == 2)
				out << std::setw(1) << item << std::setw(2) << "│";
			else if (len == 3)
				out << std::setw(0) << item << std::setw(2) << "│";
		}
	}
	out << std::endl;
	for (int j = 0; j < b.GetSize(); ++j)
	{
		out << "----";
	}
	out << "-";
	out << std::endl;
	return out;
}

void board::GamePlay()
{
	bool xTurn = true; // 1p 항상 먼저 실행한다.
	while (!x_win() && !o_win())
	{
		// X와 O의 턴을 만들어 준다.

		std::cout << std::string(30, '\n');
		std::cout << *this;


		if (xTurn)
		{
			bool inserted = false;

			while (!inserted) // insert_X 정상적으로 true됐을 때 while문이 종료된다.
			{
				int pos;
				std::cout << "X의 차례입니다. 숫자를 입력해주세요." << std::endl;
				std::cin >> pos;
				inserted = insert_x(pos);
			}

			xTurn = false;
		}
		else if (!xTurn)
		{
			bool inserted = false;

			while (!inserted) // insert_X 정상적으로 true됐을 때 while문이 종료된다.
			{
				int pos;
				std::cout << "O의 차례입니다. 숫자를 입력해주세요." << std::endl;
				std::cin >> pos;
				inserted = insert_o(pos);
			}

			xTurn = true;
		}
	}

	if (x_win())
	{
		std::cout << "X의 승리입니다." << std::endl;
	}
	else
	{
		std::cout << "O의 승리입니다." << std::endl;
	}

}