#include "ComponentCameraControl.h"


ComponentCameraControl::ComponentCameraControl(std::shared_ptr<ComponentTransform> _transform)	
	: m_transform		(_transform) //参照
	, m_horizontalAngle	(0.0f)		 //水平アングル
	, m_verticalAngle	(0.0f)		 //垂直アングル
	, m_cosParam		(0.0f)		 //コサインパラメータ
	, m_sinParam		(0.0f)		 //サインパラメータ

	, m_isLookOn		(false)		 //ロックオン中かどうか
{
	m_Idm = std::make_shared<InputManager>();//入力デバイスのインスタンス化
}

void ComponentCameraControl::Init()
{
	m_Idm->Init();
	/*Transformの初期化*/
	m_transform->position = VGet(0.0f, 50.0f, 50.0f);

	/*メンバ変数の初期化*/
	m_target			  = VGet(0, 0, 0);//注視点
	m_horizontalAngle	  = 0.0f;		  //水平アングル
	m_verticalAngle		  = 0.0f;		  //垂直アングル
	m_cosParam			  = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);//コサインパラメータ
	m_sinParam			  = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);//サインパラメーター
	m_isLookOn	     	  = false;
}

void ComponentCameraControl::Update()
{
	m_Idm->Update();

	/*右スティックの取得*/
	auto rightStickX = m_Idm->m_joyPad->GetRightStickX();
	auto rightStickY = m_Idm->m_joyPad->GetRightStickY();

	/*事前に変換*/
	bool Left = rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f;
	bool Right = rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f;
	bool Up = rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f;
	bool Down = rightStickY != 0 && rightStickY >= -0.030519 && rightStickY <= 0.0f;

	/*カメラの操作*/
	if (rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f)
	{
		m_horizontalAngle += CAMERACONTROLPARAMETER::ANGLE_SPEED;
		if (m_horizontalAngle >= 180.0f) m_horizontalAngle -= 360.0f;
	}
	if (rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f)
	{
		m_horizontalAngle -= CAMERACONTROLPARAMETER::ANGLE_SPEED;
		if (m_horizontalAngle <= -180.0f) m_horizontalAngle += 360.0f;
	}
	if (rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f)
	{
		m_verticalAngle += CAMERACONTROLPARAMETER::ANGLE_SPEED;
		if (m_verticalAngle >= 70.0f) m_verticalAngle = 70.0f;
	}
	if (rightStickY != 0 && rightStickY >= -0.030519f && rightStickY <= 0.0f)
	{
		m_verticalAngle -= CAMERACONTROLPARAMETER::ANGLE_SPEED;
		if (m_verticalAngle <= -20.0f) m_verticalAngle = -20.0f;
	}

	/*サインコサインパラメーター*/
	m_sinParam = sin(m_verticalAngle / 180.0f * DX_PI_F);
	m_cosParam = cos(m_verticalAngle / 180.0f * DX_PI_F);

	VECTOR tempPosition1, tempPosition2;
	tempPosition1.x = 0.0f;
	tempPosition1.y = m_sinParam * CAMERACONTROLPARAMETER::PLAYER_DISTANCE;
	tempPosition1.z = -m_cosParam * CAMERACONTROLPARAMETER::PLAYER_DISTANCE;

	m_sinParam = sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = cos(m_horizontalAngle / 180.0f * DX_PI_F);

	tempPosition2.x = m_cosParam * tempPosition1.x - m_sinParam * tempPosition1.z;
	tempPosition2.y = tempPosition1.y;
	tempPosition2.z = m_sinParam * tempPosition1.x + m_cosParam * tempPosition1.z;

	m_transform->position = VAdd(tempPosition2, VGet(m_target.x, m_target.y + 50, m_target.z));

	Update_LookOnSystem();//ロックオンシステム
}

void ComponentCameraControl::Draw()
{
#ifdef _DEBUG
	/*if (m_isLookOn == true)
	{
		DrawString(0,300,"ロックオン中", 0xffffff);
	}
	else
	{
		DrawString(0, 300, "ロックオン中ではない", 0xffffff);
	}*/

#endif // _DEBUG

}

void ComponentCameraControl::Final()
{
}

void ComponentCameraControl::Update_LookOnSystem()
{
	//ロックオンする
	if (m_Idm->m_joyPad->isRB == true)
	{
		m_isLookOn = true;//ロックオン中	
		//DrawString(0, 320, "RB押された", 0xffffff);
	}

	//もう一度押されたらロックオンを解除する
	if (m_Idm->m_joyPad->isLB == true)
	{
		m_isLookOn = false;
		//(0, 320, "LB押された", 0xffffff);
	}


}
