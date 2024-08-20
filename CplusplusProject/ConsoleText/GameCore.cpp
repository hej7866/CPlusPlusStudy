#include "GameCore.h"
#include <iostream>


void InitializeGame(PlayerState& playerstate, WorldState& worldstate)
{
	std::cout << "??? 섬에 오신것을 환영합니다." << std::endl;
	std::cout << "이 곳에 대한 추가 정보를 입력해주세요." << std::endl;

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
		map.MapPosition.posX = 0;
		map.MapPosition.posY = 0;

		worldstate.MapData.push_back(map);
	}
}
