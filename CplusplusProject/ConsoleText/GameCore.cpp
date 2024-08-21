#include "GameCore.h"
#include "Parser.h"
#include <iostream>

using namespace std;

void InitializeGame(PlayerState& playerstate, WorldState& worldstate)
{
	cout << "??? 섬에 오신것을 환영합니다." << endl;
	cout << "이 곳에 대한 추가 정보를 입력해주세요." << endl;

	playerstate.CurrentMapIndex = 0;
	playerstate.currentPosition.posX = playerstate.newPosition.posX = 3;
	playerstate.currentPosition.posY = playerstate.newPosition.posY = 3;

	// 첫번째 맵에 대한 정보
	{
		std::string MapInfo =
			"###..###"
			"#......#"
			"#......#"
			"#......#"
			"########";

		MapData map = MapData("초원", "경치가 아름다운 곳이다. 앞에 이동할 수 있는 문이 보이는 것 같다.", MapInfo);
		map.MapWidth = 8;
		map.MapPosition.posX = 0;
		map.MapPosition.posY = 0;

		worldstate.MapData.push_back(map);
	}
	// 두번째 맵에 대한 정보
	{
		std::string MapInfo =
			"###..###"
			"#......#"
			"#.%....#"
			"#......#"
			"###..###";

		MapData map = MapData("깊은숲 속", "울창한 수림에 둘러 쌓여 있다. 나뭇잎 사이로 지나갈 수 있는 길이 보인다.", MapInfo);
		map.MapWidth = 8;
		map.MapPosition.posX = 0;
		map.MapPosition.posY = -1;

		worldstate.MapData.push_back(map);
	}
}

void RenderGame(PlayerState& playerstate, const WorldState& worldstate)
{
	// string mapstring = worldState map배열[0] vector[0];
	// mapstring += (playerState.currentPosition "@");

	MapData currentMap = worldstate.MapData[playerstate.CurrentMapIndex]; // 현재 플레이어가 위치한 방 정보를 저장하고 있는 클래스


	std::string mapstring = "";          // 맵을 그리기 위한 string 클래스 변수
	unsigned int currentSpace = 0;

	while (currentSpace < currentMap.MapInfo.size()) { // map 문자열의 전체를 반복해서 확인을 한다.
		char playerToDisplay = currentMap.MapInfo[currentSpace]; // 플레이어의 입력을 받을 변수

		if (currentSpace == PositionToIndex(playerstate.currentPosition, currentMap.MapWidth)) {
			playerToDisplay += '@';
		}

		mapstring += playerToDisplay;

		if (currentSpace % currentMap.MapWidth == (currentMap.MapWidth - 1)) {
			mapstring += "\n";
		}
		currentSpace++;

	}

	cout << mapstring.c_str() << endl; // 맵에 저장되어 있는 문자열이 출력되는 것 까지는 확인했으나 문자열의 개행 문자가 포함되어 있지 않다

}

void GetInput(PlayerState& playerstate, const WorldState& worldstate)
{
	cout << "다음 행동을 입력해주세요 : " << endl;
	cout << "->";
	ConsoleTextCommand command = ParseCommand();

	if (command.commandType == CommandTypeW) {
		playerstate.newPosition.posY = playerstate.currentPosition.posY - 1;
	}
	else if (command.commandType == CommandTypeS) {
		playerstate.newPosition.posY = playerstate.currentPosition.posY + 1;
	}
	else if (command.commandType == CommandTypeD) {
		playerstate.newPosition.posX = playerstate.currentPosition.posX + 1;
	}
	else if (command.commandType == CommandTypeA) {
		playerstate.newPosition.posX = playerstate.currentPosition.posX - 1;
	}

	else if (command.commandType == CommandTypeInventory) {
		// playerstate 클래스 bool 멤버 변수를 만들어준다
		// bool WantToInventory = true; 가지고 있는 아이템을 출력해라!
	}

	cout << endl;
}

void UpdateGame(PlayerState& playerstate, WorldState& worldstate)
{
	MapData currentMap = worldstate.MapData[playerstate.CurrentMapIndex];

	if (isSpaceOutSideMap(playerstate.newPosition, currentMap)) {
		int newRoomIndex = 0;
		int playerExitType = 0; // 0, 1, 2, 3, 4
		Position targetMapPos = currentMap.MapPosition;

		if (playerstate.newPosition.posX < 0) {
			// 서쪽으로 탈출
			targetMapPos.posX--;
			playerExitType = 1;
		}
		else if (playerstate.newPosition.posX >= (int)currentMap.MapWidth) {
			// 동쪽으로 탈출
			targetMapPos.posX++;
			playerExitType = 2;
		}
		else if (playerstate.newPosition.posY < 0) {
			// 북쪽으로 탈출
			targetMapPos.posY--;
			playerExitType = 3;
		}
		else if (playerstate.newPosition.posY >= (int)currentMap.MapInfo.size() / currentMap.MapWidth) {
			// 남쪽으로 탈출
			targetMapPos.posY++;
			playerExitType = 4;
		}

		bool foundMap = false;

		for (int i = 0; i < worldstate.MapData.size(); i++) {
			if (worldstate.MapData[0].MapPosition == targetMapPos) {
				newRoomIndex = i;
				foundMap = true;
				break;
			}
		}

		if (foundMap == true) {
			playerstate.CurrentMapIndex = newRoomIndex;
		}
		else {
			cout << "탈출 하는 맵에 해당하는 정보가 없습니다" << endl;
			playerstate.newPosition = playerstate.currentPosition;
		}
		
	}

	 // 이동이 불가능한 조건 (앞에 벽이있을때, 앞에 아이템이 있을때) ...

	 // 이동이 가능하면 현재 위치를 newPosition으로 변경하라.
	if (isSpaceCanMove(playerstate.newPosition, currentMap)) {
		playerstate.currentPosition = playerstate.newPosition;
	}
	else {
		cout << "이동할 수 없는 공간입니다." << endl;
		playerstate.newPosition = playerstate.currentPosition; // 플레이어가 움직일 수 없기 때문에 원래위치로 돌리는 코드 필요
	}
}

int PositionToIndex(const Position& position, int mapWitth)
{
	return position.posY * mapWitth + position.posX;
}

// 멥을 탈출하면 다른 맵이 나오게 기능을 만든다.
bool isSpaceOutSideMap(const Position& pos, const MapData& currentMap)
{
	return	pos.posY < 0 || // y가 최대 높이보다 작을 때
			pos.posX > 0 || // x가 0보다 작을떄
			pos.posY >= (int)(currentMap.MapInfo.size() / currentMap.MapWidth) || // y가 최저 높이보다 클때
			pos.posX >= (int)(currentMap.MapWidth); // x가 맵 길이보다 클때
}

bool isSpaceCanMove(const Position& pos, const MapData& currentMap)
{
	int spaceIndex = PositionToIndex(pos, currentMap.MapWidth);

	char currentSpace = currentMap.MapInfo[spaceIndex];


	return currentSpace == '.';
}


