#include "EnemyFox.h"
#include "../../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"


EnemyFox::EnemyFox()
	: m_attackDistance	(0.0f)
	, m_chaseDistance	(0.0f)
	, m_targetPostion	(VGet(0.0f,0.0f,0.0f))
	, filename			("")
	, Data				()
{
	/*�R���|�[�l���g�̐���*/
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentRightBody>();
	m_rightbody = GetComponent<ComponentRightBody>();

	AddComponent<ComponentCapsule>(m_transform);
	m_capsule = GetComponent<ComponentCapsule>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();
	
	AddComponent<ComponentAnimation>(m_model);
	m_animation = GetComponent<ComponentAnimation>();

	AddComponent<ComponentStatus>();
	m_status = GetComponent<ComponentStatus>();
}

EnemyFox::~EnemyFox()
{
}

void EnemyFox::Init()
{
	/*CSVLib�̏�����*/
	filename = "../Data/GameData/EnemyData.csv";
	Data = CSVLib::ReadCSV(filename);

	/*��Ԃ̏�����*/
	m_attackDistance = CSVLib::GetCell_float(Data, 1, 5);//�U�����苗��
	m_chaseDistance	 = CSVLib::GetCell_float(Data, 1, 4); //�ǐՔ��苗��

	m_targetPostion	 = VGet(0, 0, 0);	 //�_���Ώۂ̍��W
	m_state			 = EnemyState::Idel; //�ŏ��̏��

	/*�R���|�[�l���g�̏�����*/
	Entity::InitComponent();

	/*Transform�̏�����*/
	m_transform->position	 = VGet(0, 100, 0);						//�����|�W�V����
	m_transform->scale		 = VGet(CSVLib::GetCell_float(Data, 1, 3),	//�傫���QX
								CSVLib::GetCell_float(Data, 1, 3),	//�傫���QY
								CSVLib::GetCell_float(Data, 1, 3));	//�傫���QZ

	/*�J�v�Z���̏�����*/
	m_capsule->radius		 = CSVLib::GetCell_float(Data, 1, 6);//���a
	m_capsule->height		 = CSVLib::GetCell_float(Data, 1, 7);//�T�C�Y


	/*���f���̏�����*/
	m_model->LoadModel("../Data/Asset/3D/Enemy/Enemy_Fox/Enemy_fox.mv1");

	/*�X�e�[�^�X�̏�����*/
	m_status->SetHp(100);
	m_status->SetAttackValue(10);
}

void EnemyFox::Update()
{
	/*��Ԃ̍X�V*/
	UpdateState();

	/*���S�ʒm*/
	CheckDeath();

	/*�R���|�[�l���g�̍X�V*/
	Entity::UpdateComponent();

	/*��*/
	//�n�ʂɂ��Ă��Ȃ��ꍇ�d�͗���������
	if (m_isGround == false)
	{
		float m_jumpVelocityY = 2.02f * GAMECONSTANT::k_DELTA_TIME;
		m_transform->position.y -= m_jumpVelocityY * GAMECONSTANT::k_DELTA_TIME;
		m_state = EnemyState::Falling;
	}
	

	/*�A���O���̍X�V*/
	m_transform->angle		 = std::atan2(-m_rightbody->direction.x, -m_rightbody->direction.z);//�A�[�N�^���W�F���g�A���[�N���b�h�����Ō����ɕϊ�

	/*�傫���A�����A���W�̍X�V*/
	MV1SetScale			(m_model->m_modelHandle, m_transform->scale);
	MV1SetRotationXYZ	(m_model->m_modelHandle, VGet(0, m_transform->angle, 0));
	MV1SetPosition		(m_model->m_modelHandle, m_transform->position);
}

void EnemyFox::Draw()
{
	/*�R���|�[�l���g�̕`��*/
	Entity::DrawComponent();

//#ifdef _DEBUG
//	DrawFormatString(0, 80, 0xfffffff, "Enemy:HP:%f", m_status->GetHp());
//	DrawFormatString(0, 100, 0xfffffff, "Enemy:AttackValue:%d", m_status->GetAttackValue());
//	if (m_isGround == true)
//	{
//		DrawFormatString(0, 120, 0xffffff, "true");
//	}
//	else
//	{
//		DrawFormatString(0, 120, 0xffffff, "false");
//	}
//#endif // _DEBUG


}

void EnemyFox::Final()
{
	/*�R���|�[�l���g�̉��*/
	Entity::FinalComponent();
}

void EnemyFox::UpdateMove(VECTOR& _targetPos)
{
	VECTOR lengs = VSub(_targetPos, m_transform->position);
	float lengsSize = VSize(lengs);

	m_rightbody->direction = VNorm(lengs);
	m_transform->position = VAdd(m_transform->position, VScale(m_rightbody->direction, 0.8f));
}

void EnemyFox::UpdateState()
{
	float distance = VSize(VSub(m_targetPostion, m_transform->position));

	switch (m_state)
	{
	case EnemyFox::EnemyState::Idel:

		m_animation->PlayAnim(3);
		if (distance <= m_chaseDistance)
		{
			m_state = EnemyState::Chase;
		}
		break;

	case EnemyFox::EnemyState::Chase:
		UpdateMove(m_targetPostion);
		m_animation->PlayAnim(8);
		if (distance <= m_attackDistance)
		{
			m_state = EnemyState::Attack;
		}

		if (distance >= m_chaseDistance)
		{
			m_state = EnemyState::Idel;
		}
		break;

	case EnemyFox::EnemyState::Attack:
		m_animation->PlayAnim(6);
		if (distance >= m_attackDistance)
		{
			m_state = EnemyState::Chase;
		}

		break;

	case EnemyState::Falling:
		m_animation->PlayAnim(4);
		if (m_isGround == true)
		{
			m_state = EnemyState::Idel;
		}
		break;

	case EnemyFox::EnemyState::Retreat:
		break;

	case EnemyFox::EnemyState::Deth:
		m_animation->PlayAnim(1);
		if (m_animation->GetIsAnimPlaying() == false)
		{
			m_transform->position = VGet(0, -1000, 0);
			Final();
		}
		break;

	}
}

void EnemyFox::CheckDeath()
{
	if (m_status->GetHp() <= 0)
	{
		m_state = EnemyState::Deth;
	}
}



