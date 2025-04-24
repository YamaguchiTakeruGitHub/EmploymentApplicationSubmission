#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"
#include "../ComponentPhsycs/RightBody/ComponentRightBody.h"
#include "../../../InputDevice/InputManager.h"

/*定数やタグ*/
#include "../../GameTag.h"//タグ
#include "../../../Application/GameConstant.h"//Game全般で扱う定数


//移動の定数
namespace MOVEMENT
{
	/*現状のデフォルトは気持ちの良い操作なので変更したら死！！*/

	static constexpr float k_MAXJUMPTIME = 10.0f;		//ジャンプ力(デフォ10.0f
	static constexpr float k_MINJUMPFORCE = 2.0f;		//低さ（デフォ2.0f
	static constexpr float k_MAXJUMPFORCE = 5.0f;		//高さ(デフォ5.0f
	static constexpr float k_GRAVITY = -0.2f;			//重力（いずれ別におく）(デフォ-0.2f
	
	static constexpr float k_MOVESPEED = 3.0f;			//移動速度

	static constexpr float kANGLE_ROTATION_SPEED = 0.15f;//振り向き速度
}

/// <summary>
/// 行動処理：引数指定：m_transform, m_rightbody
/// </summary>
class ComponentMovement : public Component
{
private:/*インスタンスや関数定義＆タグ定義*/
	/*コンポーネント*/
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;

	/*入力デバイス*/
	std::shared_ptr<InputManager> m_Idm;

	/*プレイヤーの行動処理*/
	void UpdatePlayerMovement();//プレイヤーの行動処理

	void UpdatePlayerJump();//ジャンプ更新処理

private:/*変数定義*/
	/*タグ*/
	std::string m_tag;

	/*プレイヤーの行動系変数*/
	bool m_isJump;					//ジャンプしているかどうか
	bool m_isGround;				//地面にいるかどうか
	bool m_isMove;					//移動中かどうか
	bool m_isAttacking;				//攻撃を行っているかどうか



	float m_jumpPower;				//ジャンプ力
	float m_jumpVelocityY;			//ジャンプの方向と速度：Ｙ
	float m_jumpHoldTime;			//押し込み時間

	/*カメラの向きを考慮したやりかた*/
	float m_conversionCameraHAngle;	//横軸の変換アングル
	float m_conversionCosParam;		//コサインパラメータ
	float m_conversionSinParam;		//サインパラメータ
	float m_targetAngle;			//振り向き先のアングル
	float m_saAngle;				//サーフェスアングル

	/*重力*/
	float m_Gravity;


public:
	ComponentMovement(std::shared_ptr<ComponentTransform> _transform, std::shared_ptr<ComponentRightBody> _rightbody, std::string _tag);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	/// <summary>
	/// 攻撃の際に向いている方向に進む処理
	/// </summary>
	/// <param name="moveLength">移動距離</param>
	/// <returns>position</returns>
	VECTOR Update_AttackMove(float moveLength);

	//==========================================================
	// 方向系
	//==========================================================

	void SetConversionCameraHAngle(const float& _ccHAngle) { m_conversionCameraHAngle = _ccHAngle; }
	float GetConversionCameraHAngle() { return m_conversionCameraHAngle; }

	void SetConversionCosParam(const float& _cCosParam) { m_conversionCosParam = _cCosParam; }
	float GetConversionCosParam() { return m_conversionCosParam; }

	void SetConversionSinParam(const float& _cSinParam) { m_conversionSinParam = _cSinParam; }
	float GetConversionSinParam() { return m_conversionSinParam; }

	/*アングル*/
	void SetAngle(const float& _angle) { m_transform->angle = _angle; }
	float GetAngle() const { return m_transform->angle; }
	
	//==========================================================
	// 行動系
	//==========================================================

	/*地面についているかどうか*/
	void SetIsGround(const bool& _isGround) { m_isGround = _isGround; }
	bool GetIsGround() const { return m_isGround; }

	/*動いているかどうかフラグ*/
	void SetIsMove(const bool& _isMove) { m_isMove = _isMove; }
	bool GetIsMove() const { return m_isMove; }

	//==========================================================
	// ジャンプ系
	//==========================================================
	/*ジャンプしているかどうかフラグ*/
	void SetIsJump(const bool& _isJump) { m_isJump = _isJump; }
	bool GetIsJump() const { return m_isJump; }
	/*ジャンプ力取得*/
	float GetJumpPower() const { return m_jumpPower; }

	//==========================================================
	// 通知系
	//==========================================================

	/*タグ*/
	void SetTag(std::string& _tag) { m_tag = _tag; }
	std::string GetTag() const { return m_tag; }

	/*攻撃中かどうか*/
	void SetIsAttacking(const bool& _isAttacking) { m_isAttacking = _isAttacking; }
	bool GetIsAttacking() const { return m_isAttacking; }

	//==========================================================
	// 重力系
	//==========================================================
	void SetGravity(const float& _gravity) { m_Gravity = _gravity; }
	float GetGravity() const { return m_Gravity; }



};

