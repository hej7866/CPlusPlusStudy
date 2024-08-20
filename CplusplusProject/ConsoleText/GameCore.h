#pragma once
#include <string>
#include <vector>

class Position
{
public:
	int posX;
	int posY;

	// 연산자 오버로딩 사용하세요. 반환값 bool
	// operator -=. ==
	bool operator == (const Position& otherPos) const
	{
		return posX == otherPos.posX && posY == otherPos.posY;
	}

	bool operator != (const Position& otherPos) const
	{
		return !(*this == otherPos);
	}
};


class PlayerState
{
public:
	Position currentPosition; // 현재 플레이어의 위치
	Position newPosition; // 입력 받은 플레이어의 위치
};

// Console Text. 맵 이동 기능
// 현재 맵 정보, 현재 맵에 대한 설명
class MapData
{
	std::string Name;        // Name = "초원";
	std::string Description; // 이 맵의 정보를 작성한다.
	std::string MapInfo;
	unsigned int MapWidth;
public:
	Position MapPosition;    // 맵 마다 시작하는 위치가 다르게하기 위해서 (x,y)를 지정해 주는것
	MapData();
	MapData(std::string Name, std::string Description, std::string MapInfo)
	{
		this->Name = Name;
		this->Description = Description;
		this->MapInfo = MapInfo;
	}
};

class WorldState // 맵이 여러개 있는 World <- 플레이어가 위치해야할 정보를 담고 있는 클래스
{
public:
	std::vector<MapData> MapData;
};

void InitializeGame(PlayerState& playerstate, WorldState& worldstate);
