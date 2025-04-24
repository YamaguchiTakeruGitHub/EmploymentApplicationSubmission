#include "Player.h"
#include "../../GameTag.h"
#include "../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"

/// <summary>
/// プレイヤーのパラメーター
/// </summary>
namespace PLAYER_PARAMETER
{
	static constexpr float POS_X = 0.0f;//X座標
	static constexpr float POS_Y = 0.0f;//Y座標
	static constexpr float POS_Z = 60.0f;  //Z座標

	static constexpr float COMBO_MOVE_2 = 0.2f;//コンボ２の移動距離
	static constexpr float COMBO_MOVE_3 = 0.1f;//コンボ３の移動距離

	static constexpr int COMBO_MAXNUM = 3;//最大コンボ数
	static constexpr float COMBO_RUNTIME = 120.0f;//コンボ制限時間
}

void Player::UpdateState()
{
	if (m_rightbody->direction.x == 0.0f && m_rightbody->direction.z == 0.0f)
	{
		m_state = PlayerState::Idel;
	}
	if (m_movement->GetIsGround() == false)
	{
		m_state = PlayerState::Falling;
	}

}

Player::Player()
	: filename	("")//ファイルの名前
	, Data		()	//ファイルのデータ

	, m_AttackPosition(VGet(0,0,0))
	, m_AttackRadius(0)
{
	/*コンポーネントを生成*/
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentRightBody>();
	m_rightbody = GetComponent<ComponentRightBody>();

	AddComponent<ComponentMovement>(m_transform, m_rightbody, TagCharacterObject::PLAYER);
	m_movement = GetComponent<ComponentMovement>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	AddComponent<ComponentCapsule>(m_transform);
	m_capsule = GetComponent<ComponentCapsule>();

	AddComponent<ComponentAnimation>(m_model);
	m_animation = GetComponent<ComponentAnimation>();

	//コンボシステム
	AddComponent<ComponentComboSystem>();
	m_comboSystem = GetComponent<ComponentComboSystem>();

	//ステータス
	AddComponent<ComponentStatus>();
	m_status = GetComponent<ComponentStatus>(); 

}

Player::~Player()
{
}

void Player::Init()
{
	/*CSVLib初期化*/
	filename = "../Data/GameData/PlayerData.csv";//ファイルのパス
	Data = CSVLib::ReadCSV(filename);			 //ファイルの読み込み

	/*コンポーネントの初期化*/
	Entity::InitComponent();

	/*Transformの初期化*/
	m_transform->position = VGet(PLAYER_PARAMETER::POS_X,	//ポジションの初期位置_X
								 PLAYER_PARAMETER::POS_Y,	//ポジションの初期位置_Y
								 PLAYER_PARAMETER::POS_Z);	//ポジションの初期位置_Z

	m_transform->scale = VGet(CSVLib::GetCell_float(Data, 3, 2),	//モデルのサイズX
							  CSVLib::GetCell_float(Data, 3, 2),	//モデルのサイズY
						      CSVLib::GetCell_float(Data, 3, 2));	//モデルのサイズZ

	/*モデルの初期化*/
	m_model->LoadModel("../Data/Asset/3D/Player/Player.mv1");

	/*カプセルの初期化*/
	m_capsule->radius = CSVLib::GetCell_float(Data,1, 2);	//カプセルの半径
	m_capsule->height = CSVLib::GetCell_float(Data, 2, 2);	//カプセルのサイズ

	/*コンボ初期化*/
	m_comboSystem->SetComboResetTime(PLAYER_PARAMETER::COMBO_RUNTIME);//コンボをリセットする時間
	m_comboSystem->SetComboMaxCount(PLAYER_PARAMETER::COMBO_MAXNUM);//最大コンボ数

	/*ステータス初期化*/
	m_status->SetHp(100.0f);
	m_status->SetAttackValue(10);

	/*攻撃範囲*/
	m_AttackPosition = VGet(0, 0, 0);
	m_AttackRadius = 0.0f;
}

void Player::Update()
{
	/*アニメーションの更新*/
	UpdateAnimation();

	/*ステータスの更新*/
	//m_status->SetHp(100.0f);
	//m_status->SetAttackValue(10);
	
	/*コンポーネントの更新*/
	Entity::UpdateComponent();

	/*行動処理の更新*/
	UpdateMomvement();

	/*コンボ系処理の更新*/
	UpdateCombo();

	/*モデルのアングルと大きさと座標を更新*/
	MV1SetRotationXYZ(m_model->m_modelHandle, VGet(0.0f, m_transform->angle * DX_PI_F / 180.0f, 0.0f));//角度をラジアンに変換してセットする
	MV1SetScale(m_model->m_modelHandle, m_transform->scale);
	MV1SetPosition(m_model->m_modelHandle, m_transform->position);
}

void Player::Draw()
{
	/*コンポーネントの描画*/
	Entity::DrawComponent();

#ifdef _DEBUG
	/*DrawFormatString(0, 40, 0xfffffff, "Player:HP:%f", m_status->GetHp());
	DrawFormatString(0, 60, 0xfffffff, "Player:AttackValue:%d", m_status->GetAttackValue());*/

	// プレイヤーの向いている方向をデバッグ描画
	VECTOR startPos = m_transform->position;
	VECTOR direction = VGet(sinf(m_transform->angle * DX_PI_F / 180.0f), 0.0f, cosf(m_transform->angle * DX_PI_F / 180.0f));
	VECTOR endPos = VAdd(startPos, VScale(direction, 50.0f)); // 50.0f は線の長さ
	//DrawLine3D(startPos, endPos, GetColor(255, 0, 0)); // 赤色で描画

	/*攻撃範囲*/
	m_AttackPosition = VAdd(VAdd(startPos, VGet(0, 30.0f, 0)), VScale(direction, 10.0f));
	m_AttackRadius = 20.0f;

	//DrawSphere3D(VAdd(VAdd(startPos, VGet(0,30.0f,0)), VScale(direction, 10.0f)), 20.0f, 5, 0xffffff, 0xffffff, false);
#endif // _DEBUG

}

void Player::Final()
{
	/*コンポーネントの解放*/
	Entity::FinalComponent();
}


void Player::UpdateCombo()//コンボ系処理
{
	/*コンボ関連*/
	if (m_isAttackCheck == true)
	{
		//次のコンボへ
		m_comboSystem->IncrementCombo();
	}

	//攻撃中であればプレイヤー入力による移動処理を行わない
	//でなければ移動処理を行う
	m_movement->SetIsAttacking(m_comboSystem->GetIsCombo());
}

void Player::UpdateAnimation()//アニメーション系処理
{
	/*歩行中であれば*/
	if (m_movement->GetIsMove() == true && m_movement->GetIsJump() == false)
	{
		m_animation->PlayAnim(8);//Moveアニメーション
	}
	else if (m_movement->GetIsMove() == false && m_movement->GetIsJump() == false)
	{
		m_animation->PlayAnim(4);//Idelアニメーション
	}

	if (m_movement->GetIsJump() == true)
	{
		m_animation->PlayAnim(5);//Jumpアニメーション
	}

	// コンボ数が変わったらアニメーションの再生時間をリセットする
	if (m_comboSystem->GetComboCount() != m_comboSystem->GetComboOldCount())
	{
		m_animation->ResetAnimationNowTime();
		m_comboSystem->SetComboOldCount(m_comboSystem->GetComboCount());
	}

	/*攻撃コンボ*/
	if (m_comboSystem->GetComboCount() == 1)
	{
		m_animation->PlayAnim(0);
	}
	if (m_comboSystem->GetComboCount() == 2)
	{
		m_animation->PlayAnim(1);
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_2);
	}
	if (m_comboSystem->GetComboCount() == 3)
	{
		m_animation->PlayAnim(2);
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_3);
	}
}

void Player::UpdateMomvement()
{
	/*行動の更新(コンストラクタ呼び出し時にタグを設定できるようにしたい)*/
	m_movement->SetTag(TagCharacterObject::PLAYER);

	/*攻撃コンボによる移動処理*/
	if (m_comboSystem->GetComboCount() == 2)
	{
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_2);
	}
	if (m_comboSystem->GetComboCount() == 3)
	{
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_3);
	}
}
