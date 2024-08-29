#include <iostream>
#include "GameObject.h"

using namespace std;

// Monster class - 추상 클래스로 표현
// reward class - 경험치, 재화, 아이템(아이템 번호, item, quest item)

// player <-> monster 배틀시스템
// battle class. public : bool End() : 플레이어가 죽었을 때, 몬스터가 죽었을 때, 도주를 성공하였을 때
// 무한 반복(전투의 끝을 의미하는 bool)
// 1. player turn (1) 공격 (2) 방어 (3) 도주
// NextTurn
// 2. monster turn (1) 공격

// 몬스터가 죽으며 monster class Has, Is -> Reward Drop Item()
// Player.GetItem(monster* m1);

int main(void)
{
	cout << "RPG BATTLE SYSTEM" << endl;

	Player player(100, 10);
	// player.Attack();

	Item sword("소드", 10);
	Reward slimeReward(50, 1000, sword);
	
	Slime slime(50, 5, &slimeReward);

	int userInput = 0;
	int turn = 1;
	while (true)
	{
		cout << "현재 진행 중인 턴 수 : " << turn << endl;
		cout << "1번. 공격" << endl;
		cout << "2번. ??" << endl;

		cin >> userInput;
		if (userInput == 1)
		{
			player.Attack(&slime);
		}

		cout << "슬라임의 Turn" << endl;
		slime.MonsterAttack(&player);

		if (player.IsDead() || slime.IsDead())
		{
			break;
		}

		turn++;
	}

	// 1. 게임 시작 화면

	// 2. 메인 게임 플레이

	// 페이즈1. Map Adventure(맵을 돌아다니는 기능) ( Step++ RandomEncount : SRand(5 ~ 25))
	// 특정 타일을 밟으면 몬스터랑 조우할지 안할지 랜덤 함수를 돌린다.

	// 페이즈2. Player vs Monser(몬스터를 하나 만들고, 그 몬스터를 이용하여 다른 몬스터를 구현)

	// player 객체 생성
	// monster 객체 생성
	// monster reward 객체 생성

}