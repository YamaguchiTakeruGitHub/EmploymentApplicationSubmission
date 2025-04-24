#include "EnemyFox.h"
#include "../../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"


EnemyFox::EnemyFox()
	: m_attackDistance	(0.0f)
	, m_chaseDistance	(0.0f)
	, m_targetPostion	(VGet(0.0f,0.0f,0.0f))
	, filename			("")
	, Data				()
{
	/*コンポーネントの生成*/
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
	/*CSVLibの初期化*/
	filename = "../Data/GameData/EnemyData.csv";
	Data = CSVLib::ReadCSV(filename);

	/*状態の初期化*/
	m_attackDistance = CSVLib::GetCell_float(Data, 1, 5);//攻撃判定距離
	m_chaseDistance	 = CSVLib::GetCell_float(Data, 1, 4); //追跡判定距離

	m_targetPostion	 = VGet(0, 0, 0);	 //狙う対象の座標
	m_state			 = EnemyState::Idel; //最初の状態

	/*コンポーネントの初期化*/
	Entity::InitComponent();

	/*Transformの初期化*/
	m_transform->position	 = VGet(0, 100, 0);						//初期ポジション
	m_transform->scale		 = VGet(CSVLib::GetCell_float(Data, 1, 3),	//大きさ＿X
								CSVLib::GetCell_float(Data, 1, 3),	//大きさ＿Y
								CSVLib::GetCell_float(Data, 1, 3));	//大きさ＿Z

	/*カプセルの初期化*/
	m_capsule->radius		 = CSVLib::GetCell_float(Data, 1, 6);//半径
	m_capsule->height		 = CSVLib::GetCell_float(Data, 1, 7);//サイズ


	/*モデルの初期化*/
	m_model->LoadModel("../Data/Asset/3D/Enemy/Enemy_Fox/Enemy_fox.mv1");

	/*ステータスの初期化*/
	m_status->SetHp(100);
	m_status->SetAttackValue(10);
}

void EnemyFox::Update()
{
	/*状態の更新*/
	UpdateState();

	/*死亡通知*/
	CheckDeath();

	/*コンポーネントの更新*/
	Entity::UpdateComponent();

	/*仮*/
	//地面についていない場合重力落下させる
	if (m_isGround == false)
	{
		float m_jumpVelocityY = 2.02f * GAMECONSTANT::k_DELTA_TIME;
		m_transform->position.y -= m_jumpVelocityY * GAMECONSTANT::k_DELTA_TIME;
		m_state = EnemyState::Falling;
	}
	

	/*アングルの更新*/
	m_transform->angle		 = std::atan2(-m_rightbody->direction.x, -m_rightbody->direction.z);//アークタンジェント、ユークリッド距離で向きに変換

	/*大きさ、向き、座標の更新*/
	MV1SetScale			(m_model->m_modelHandle, m_transform->scale);
	MV1SetRotationXYZ	(m_model->m_modelHandle, VGet(0, m_transform->angle, 0));
	MV1SetPosition		(m_model->m_modelHandle, m_transform->position);
}

void EnemyFox::Draw()
{
	/*コンポーネントの描画*/
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
	/*コンポーネントの解放*/
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



