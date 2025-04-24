#include "ComponentMovement.h"


void ComponentMovement::UpdatePlayerJump()
{
	//地面に着地しており、ジャンプボタンが押されていたら
	if (m_isGround == true && m_Idm->m_joyPad->isA == true)
	{
		m_jumpHoldTime = 0.0f;
		m_isJump = true;
	}

	//ジャンプ中かつボタンが押され続けているか
	if (m_isJump == true && m_Idm->m_joyPad->isAHold == true)
	{
		m_jumpHoldTime += GAMECONSTANT::k_DELTA_TIME;
		m_jumpHoldTime = min(m_jumpHoldTime, MOVEMENT::k_MAXJUMPTIME);
	}

	//長押し時間が天井まで来たらジャンプを止める
	if (m_isJump == true && (!m_Idm->m_joyPad->isAHold || m_jumpHoldTime >= MOVEMENT::k_MAXJUMPTIME))
	{
		m_jumpPower = MOVEMENT::k_MINJUMPFORCE + (MOVEMENT::k_MAXJUMPFORCE - MOVEMENT::k_MINJUMPFORCE) * (m_jumpHoldTime / MOVEMENT::k_MAXJUMPTIME);
		m_jumpVelocityY = m_jumpPower;
		m_isJump = false;
		m_isGround = false;
	}
	
	//地面についていない場合重力落下させる
	if (m_isGround == false)
	{
		m_jumpVelocityY += m_Gravity * GAMECONSTANT::k_DELTA_TIME;
		m_transform->position.y += m_jumpVelocityY * GAMECONSTANT::k_DELTA_TIME;
	}

	//地面についている場合
	if (m_isGround == true)
	{
		m_jumpVelocityY = 0.0f;
	}

}

void ComponentMovement::UpdatePlayerMovement()
{
	/*左ステックの召喚*/
	float leftSticX = m_Idm->m_joyPad->GetLeftStickX();
	float leftSticY = m_Idm->m_joyPad->GetLeftStickY();

	/*常に制御する変数*/
	//１にならないように毎フレーム０にする
	m_rightbody->direction = VGet(0.0f, 0.0f, 0.0f);

	//常に移動中にならないように毎フレームおろす
	m_isMove = false;

	/*ステックをうごかしている場合*/
	if (leftSticX != 0.0f || leftSticY != 0.0f)
	{
		m_isMove = true;

		auto targetAngleRad = atan2(-leftSticX, leftSticY);//アークタンジェントで2つのユークリッド距離を角度とする
		auto targetangleDeg = targetAngleRad * 180.0f / DX_PI_F;//ラジアンに変換

		auto targetAngle = targetangleDeg - m_conversionCameraHAngle;
		auto angleDifference = targetAngle - m_transform->angle;

		if (angleDifference >= 180.0f)
		{
			angleDifference -= 360.0f;
		}
		else
		if (angleDifference <= -180.0f)
		{
			angleDifference += 360.0f;
		}


		/*アングルと方向を上書き*/
		m_transform->angle += angleDifference * MOVEMENT::kANGLE_ROTATION_SPEED;

		m_rightbody->direction.x = sin(targetAngleRad);
		m_rightbody->direction.z = cos(targetAngleRad);


		
	}

	//もし動いているなら
	if (VSquareSize(m_rightbody->direction) > 0)
	{
		m_rightbody->direction = VNorm(m_rightbody->direction);
	}

	//うごいていたら
	if (m_isMove == true)
	{
		// カメラの角度を考慮した移動ベクトルの計算
		m_conversionSinParam = sin(m_conversionCameraHAngle / 180.0f * DX_PI_F);
		m_conversionCosParam = cos(m_conversionCameraHAngle / 180.0f * DX_PI_F);

		VECTOR tempMoveVector;
		tempMoveVector.x = m_rightbody->direction.x * m_conversionCosParam - m_rightbody->direction.z * m_conversionSinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_rightbody->direction.x * m_conversionSinParam + m_rightbody->direction.z * m_conversionCosParam;

		m_transform->position = VAdd(m_transform->position, tempMoveVector);
	}


}

ComponentMovement::ComponentMovement(std::shared_ptr<ComponentTransform> _transform, std::shared_ptr<ComponentRightBody> _rightbody, std::string _tag)
	/*コンポーネントの参照の初期化*/
	: m_transform				(_transform)
	, m_rightbody				(_rightbody)

	/*プレイヤーの行動*/
	, m_isJump					(false)		//ジャンプしているかどうか
	, m_isGround				(false)		//地面にいるかどうか
	, m_isMove					(false)		//移動中かどうか
	, m_jumpPower				(0.0f)		//ジャンプ力
	, m_jumpVelocityY			(0.0f)		//ジャンプの方向と速度：Ｙ
	, m_jumpHoldTime			(0.0f)		//押し込み時間
	
	, m_conversionCameraHAngle	(0.0f)		//横軸の変換アングル
	, m_conversionCosParam		(0.0f)		//コサインパラメータ
	, m_conversionSinParam		(0.0f)		//サインパラメータ
	, m_targetAngle				(0.0f)		//振り向き先のアングル
	, m_saAngle					(0.0f)		//サーフェスアングル

	, m_Gravity(MOVEMENT::k_GRAVITY)		//重力


{
	/*入力デバイスのインスタンス化*/
	m_Idm = std::make_shared<InputManager>();
}

void ComponentMovement::Init()
{
	/*入力デバイスの初期化*/
	m_Idm->Init();

	/*プレイヤーの行動*/
	m_isJump				 = false;	//ジャンプしているかどうか
	m_isGround				 = false;	//地面にいるかどうか
	m_jumpPower				 = 0.0f;	//ジャンプ力
	m_jumpVelocityY			 = 0.0f;	//ジャンプの方向と速度：Ｙ
	m_jumpHoldTime			 = 0.0f;	//押し込み時間

	/*カメラの向きを考慮したやりかた*/
	m_conversionCameraHAngle = 0.0f;	//横軸の変換アングル
	m_conversionCosParam	 = 0.0f;	//コサインパラメータ
	m_conversionSinParam	 = 0.0f;	//サインパラメータ
	m_targetAngle			 = 0.0f;	//振り向き先のアングル
	m_saAngle				 = 0.0f;	//サーフェスアングル

	m_Gravity = MOVEMENT::k_GRAVITY;		//重力
}

void ComponentMovement::Update()
{
	/*入力デバイスの更新*/
	m_Idm->Update();

	/*各処理の更新(後々タグで管理する)*/
	if (m_tag == TagCharacterObject::PLAYER)
	{
		//攻撃中でなければ
		if (m_isAttacking == false)
		{
			UpdatePlayerMovement();	//行動処理
			UpdatePlayerJump();		//ジャンプ処理
		}
	}
}

void ComponentMovement::Draw()
{
}

void ComponentMovement::Final()
{
}

VECTOR ComponentMovement::Update_AttackMove(float moveLength)
{
	VECTOR forward = VGet(sinf(m_transform->angle * DX_PI_F / 180.0f), 0.0f, cosf(m_transform->angle * DX_PI_F / 180.0f));
	return VAdd(m_transform->position, VScale(forward, moveLength));
}
