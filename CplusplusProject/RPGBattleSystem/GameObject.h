#pragma once
#include <string>
#include <iostream>
#include <vector>

// 몬스터와의 전투
// 1. 공격력, 체력


using namespace std;

class Item
{
private:
	string name;
	int index;
public:
	Item() {}
	Item(string name, int index) : name(name), index(index) {}
	void ShowItemInfo()
	{
		cout << "아이템의 이름 : " << name << endl;
		cout << "아이템의 번호 : " << index << endl;
	}
};

class Reward
{
private:
	int exp;
	int money;
	Item* item; // 아이템
public:
	Reward() {}
	Reward(int exp, int money, Item& item) : exp(exp), money(money)
	{
		(*this).item = new Item();
		(*this).item = &item;
	}
	~Reward()
	{
		delete item;
	}

	void RewardItem(vector<Item>* inventory);
	int RewardMoney() { return money; };
	int RewardExp() { return exp; };
};

class Monster;

class Player
{
private:
	int hp; // 체력
	int atk; // 공격력
	int exp; // 경험치
	int money; // 돈
	vector<Item> inventory; // 캐쉬아이템으로 인벤토리 확장권을 팔겠다. 즉, 가변성이있다. (vector) 
public:
	Player() {} // 기본 생성자
	Player(int _hp, int _atk) : hp(_hp), atk(_atk) // 생성자
	{
		cout << "플레이어가 생성됨" << endl;
	}
	~Player() // 소멸자
	{
		cout << "플레이어가 소멸됨" << endl;
	}
	void Attack(Monster* monster); // 공격하다.

		
	void BeAttacked(int damage);// 공격받다.

	// 사망 체크 함수
	bool IsDead();

	int GetAttackPower() { return atk; }
	void GetMoney(int money);
	void GetExp(int exp);
	vector<Item>* GetInventory();

	void ShowStatus();
};

class Monster
{
protected:
	int monsterHp; // 몬스터 체력
	int monsterAtk; // 몬스터 공격력
	Reward* monsterReward; // 보상
public:
	Monster() {}
	Monster(int _monsterHp, int _monsterAtk) : monsterHp(_monsterHp), monsterAtk(_monsterAtk) {} // 생성자
	~Monster() {} // 소멸자

	virtual void MonsterAttack(Player* player) = 0;// 몬스터가 공격하다.

	virtual void MonsterBeAttacked(Player* player) = 0; // 몬스터가 공격받다.

	virtual void DropReward(Player* player) = 0; // Drop Reward
};

class Slime : public Monster
{
public:
	Slime(int monsterHp, int monsterAtk, Reward* rewardPtr) : Monster(monsterHp, monsterAtk)
	{
		cout << "슬라임 생성!" << endl;
	}
	~Slime()
	{
		cout << "슬라임이 소멸됨" << endl;
	}

	void InsertDropItemTable(Reward* rewardPtr)
	{
		monsterReward = new Reward();
		monsterReward = rewardPtr;
	}
	void MonsterAttack(Player* player);

	void MonsterBeAttacked(Player* player);

	void DropReward(Player* player);

	bool IsDead();
};
