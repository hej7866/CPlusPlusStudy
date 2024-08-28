#include "GameObject.h"

void Player::Attack(Monster* monster)
{
	cout << "플레이어의 공격!" << endl;
	(*monster).MonsterBeAttacked(this);
}

void Player::BeAttacked(int damage)
{
	cout << "플레이어가 데미지를 " << damage << "만큼받음 !" << endl;

	hp -= damage;

	// 만약에 플레이어가 사망했다면 -> *게임 오버* 함수를 호출한다.
	if (IsDead()) {
		hp = 0;
		cout << "플레이어가 사망하였습니다." << endl;
		exit(0);
	}
}

bool Player::IsDead()
{
	if (hp <= 0) {
		return true;
	}
	else {
		return false;
	}

}

void Player::GetMoney(int money)
{
	cout << "획득한 재화 : " << money << endl;
	(*this).money += money;
}

void Player::GetExp(int exp)
{
	cout << "경험치 획득 : " << exp << endl;
	(*this).exp += exp;
}

vector<Item>* Player::GetInventory()
{
	return &inventory;
}

void Player::ShowStatus()
{
	cout << "현재 체력 : " << hp << endl;
	cout << "현재 공격력 : " << atk << endl;
	cout << "현재 경험차 : " << exp << endl;
	cout << "----플레이어 소지품----" << endl;
	cout << "현재 금액 : " << money << endl;

	// 반복문을 이용해서 아이템의 최대 수. Item 배열[i] -> 아이템 이름, 아이템 번호, 기능 .....
	cout << "현재 아이템 : " << "아직 미구현" << endl;
}

void Slime::MonsterAttack(Player* player)
{
	cout << "슬라임이 공격한다!" << endl;
	(*player).BeAttacked(monsterAtk);
}

void Slime::MonsterBeAttacked(Player* player)
{
	cout << "슬라임이 움츠러들었다!" << endl;
	monsterHp -= (*player).GetAttackPower();

	if (IsDead()) {
		monsterHp = 0;
		cout << "슬라임을 처치했습니다." << endl;
		// exit(0);
		// 아이템 보상
		DropReward(player);
	}
}

void Slime::DropReward(Player* player)
{
	cout << "몬스터 처치 보상" << endl;
	(*monsterReward).RewardExp();
	(*monsterReward).RewardMoney();
	(*monsterReward).RewardItem((*player).GetInventory());
}

bool Slime::IsDead()
{
	if (monsterHp <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Reward::RewardItem(vector<Item>* inventory)
{
	if (item != nullptr) // 아이템이 있을 경우에만 플레이어 inventory에 추가하기 위한 조건
	{
		(*inventory).push_back(*item);
		cout << "아이템 획득" << endl;
		(*item).ShowItemInfo();
	}
}
