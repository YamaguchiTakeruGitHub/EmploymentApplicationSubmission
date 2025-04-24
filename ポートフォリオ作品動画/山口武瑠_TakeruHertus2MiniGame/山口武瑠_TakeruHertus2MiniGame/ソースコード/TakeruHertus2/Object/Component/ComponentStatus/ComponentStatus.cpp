#include "ComponentStatus.h"

ComponentStatus::ComponentStatus()
	: level		(1)//���x��
	, exp		(0)//�o���l
	, nextExp	(0)//���̌o���l
	, attack	(0)//�U����
	, defense	(0)//�h���
	, hp		(0)//�̗�
	, maxHp		(0)//�ő�̗�
	, mp		(0)//����
	, maxMp		(0)//�ő喂��
{
}

void ComponentStatus::Init()
{
	level	 = 1;//���x��
	exp		 = 0;//�o���l
	nextExp	 = 0;//���̌o���l
	attack	 = 0;//�U����
	defense	 = 0;//�h���
	hp		 = 0;//�̗�
	maxHp	 = 0;//�ő�̗�
	mp		 = 0;//����
	maxMp	 = 0;//�ő喂��
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
		LevelUp();//���x���A�b�v
	}
}

void ComponentStatus::LevelUp()
{
	/*���x���A�b�v����*/
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
	int damageTaken = _dmg - defense;//�_���[�W����h��͕��������l���_���[�W�Ƃ��ĕۑ�����
	if (damageTaken < 1) damageTaken = 1;//�Œ�P�_���[�W�͎󂯂�
	hp -= damageTaken;
	if (hp <= 0)
	{
		hp = 0;
		/*���S*/
	}
	else
	{
		/*���[�߂����󂯂��I*/
	}

}

void ComponentStatus::Heal(int _amount)
{
	hp += _amount;
	if (hp > maxHp) hp = maxHp;
	/*HP���񕜂����I*/
}
