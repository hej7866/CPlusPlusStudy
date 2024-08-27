#pragma once
#include <iostream>

using namespace std;

class Player
{
private:
	int hp; // 체력
	int atk; // 공격력
public:
	Player(int _hp, int _atk) // 생성자
	{
		hp = _hp;
		atk = _atk;
	}
	~Player();// 소멸자

	void Attack(Monster* monster) // 공격하다.
	{
		
	}
		
	void BeAttacked(Monster* monster) // 공격받다.
	{

	}
};

class Monster
{
private:
	int monsterHp; // 몬스터 체력
	int monsterAtk; // 몬스터 공격력
	string name;
	Reward* monsterReward; // 보상
public:
	Monster(int _monsterHp, int _monsterAtk) // 생성자
	{
		monsterHp = _monsterHp;
		monsterAtk = _monsterAtk;
	}
	~Monster(); // 소멸자

	virtual void MonsterAttack(Player* player) = 0;// 몬스터가 공격하다.

	virtual void MonsterBeAttacked(Player* player) = 0; // 몬스터가 공격받다.

	virtual void DropReward() = 0; // Drop Reward
};

class Slime : public Monster
{

};

class Reward
{
	int exp;
	int money;
	Item* item; // 아이템
};

class Item
{

};