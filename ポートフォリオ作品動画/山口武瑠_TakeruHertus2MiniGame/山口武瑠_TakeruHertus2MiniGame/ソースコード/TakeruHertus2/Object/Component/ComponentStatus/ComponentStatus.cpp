#include "ComponentStatus.h"

ComponentStatus::ComponentStatus()
	: level		(1)//レベル
	, exp		(0)//経験値
	, nextExp	(0)//次の経験値
	, attack	(0)//攻撃力
	, defense	(0)//防御力
	, hp		(0)//体力
	, maxHp		(0)//最大体力
	, mp		(0)//魔力
	, maxMp		(0)//最大魔力
{
}

void ComponentStatus::Init()
{
	level	 = 1;//レベル
	exp		 = 0;//経験値
	nextExp	 = 0;//次の経験値
	attack	 = 0;//攻撃力
	defense	 = 0;//防御力
	hp		 = 0;//体力
	maxHp	 = 0;//最大体力
	mp		 = 0;//魔力
	maxMp	 = 0;//最大魔力
}

void ComponentStatus::Update()
{
}

void ComponentStatus::Draw()
{
}

void ComponentStatus::Final()
{
}

void ComponentStatus::AddExp(int _value)
{
	exp += _value;
	if (exp >= nextExp)
	{
		LevelUp();//レベルアップ
	}
}

void ComponentStatus::LevelUp()
{
	/*レベルアップ処理*/
	level++;
	exp = 0;
	nextExp += 50;
	maxHp += 10;
	maxMp += 5;
	attack += 2;
	defense += 2;
	hp = maxHp;
	mp = maxMp;
}

void ComponentStatus::IsTakeDamage(int _dmg)
{
	int damageTaken = _dmg - defense;//ダメージから防御力分引いた値をダメージとして保存する
	if (damageTaken < 1) damageTaken = 1;//最低１ダメージは受ける
	hp -= damageTaken;
	if (hp <= 0)
	{
		hp = 0;
		/*死亡*/
	}
	else
	{
		/*だーめじを受けた！*/
	}

}

void ComponentStatus::Heal(int _amount)
{
	hp += _amount;
	if (hp > maxHp) hp = maxHp;
	/*HPを回復した！*/
}
