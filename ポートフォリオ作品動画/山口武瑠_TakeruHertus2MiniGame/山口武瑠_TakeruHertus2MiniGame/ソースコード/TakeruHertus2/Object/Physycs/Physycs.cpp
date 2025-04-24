#include "Physycs.h"

namespace ColInfo
{
	//�ő哖���蔻��|���S����
	constexpr int kMaxColHitPolyNum = 2000;
	//�ǉ����o�������̍ő厎�s��
	constexpr int kMaxColHitTryNum = 16;
	//�ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kColHitSlideLength = 1.0f;
}

/*���Ȃ̂ł��Ƃňڍs*/
namespace
{
	//�ő哖���蔻��|���S����
	constexpr int kMaxColHitPolyNum = 2000;
	//�ǉ����o�������̍ő厎�s��
	constexpr int kMaxColHitTryNum = 16;
	//�ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kColHitSlideLength = 1.0f;
	//�ړ��������𔻒f���邽�߂̕ϐ�
	constexpr float kMove = 0.01f;
	//�ǃ|���S�������|���S�����𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;
	//�ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
	constexpr float kWallPolyHeight = 5.0f;

	//����ł���̎���
	constexpr int kEnableTimeCount = 10;

	//���̍�����ݒ�
	constexpr float kHeadHeight = 40.0f;
	//
}

Physycs::Physycs(std::shared_ptr<Player> _player, std::shared_ptr<MiniGame_1Map> _miniGame_Map1, const std::vector<std::shared_ptr<EnemyFox>>& enemies)
	: m_player(_player)
	, m_miniGame_Map1(_miniGame_Map1)
	, m_enemyFoxs(enemies)
	, m_isEnemyGround{false,false, false}
	, m_isEnmeyWall{ false,false, false }
{
}

void Physycs::Init()
{
	for (int i = 0; i < 3; i++)
	{
		m_isEnemyGround[i] = false;
		m_isEnmeyWall[i] = false;
	}
}

void Physycs::Update()
{
	Update_Player();
	Update_enemyFoxs();
	CheckPlayerEnemyCollisions();//�G�ƃv���C���[�̓����蔻��
}

void Physycs::PolygonHitCapsule(bool& _isGround, bool& _isWall, VECTOR& _resolvePos, float _capsuleHeight, float _capsuleRadius, int _polygonHandle)
{
	VECTOR top = VAdd(_resolvePos, VGet(0, _capsuleHeight, 0));
	VECTOR bottom = VAdd(_resolvePos, VGet(0, _capsuleRadius, 0));

	DrawLine3D(top, bottom, 0xff0000);
	DrawLine3D(top, VAdd(top, VGet(0, _capsuleRadius, 0)), 0xfffff);
	
	m_hitDim = MV1CollCheck_Capsule(_polygonHandle, -1, top, bottom, _capsuleRadius);

	bool isGrounded = false;

	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		
		if (HitCheck_Capsule_Triangle(top, bottom, _capsuleRadius, m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]))
		{
			VECTOR normal = m_hitDim.Dim[i].Normal;
			VECTOR center = m_mathLib->PolygonCenter(m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]);
			VECTOR move = VGet(0, 0, 0);
			VECTOR slide = VGet(0, 0, 0);

			// ����
			if (normal.y >= 1.0f)
			{
				_resolvePos = VAdd(_resolvePos, VGet(0, normal.y - 1.0f, 0));
				isGrounded = true;
			}

			// �X���[�v
			if (normal.y < 1.0f && normal.y >= 0.6f)
			{
				VECTOR slideDirection = VGet(normal.x, 0, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 0.5f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 0.5f);
				_resolvePos = VAdd(_resolvePos, pushOut);

				isGrounded = true;
			}

			// ��
			if (normal.y <= 0.2f && normal.y >= 0.0f)
			{
				VECTOR slideDirection = VGet(normal.x, 0, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 1.0f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				_resolvePos = VAdd(_resolvePos, pushOut);
			}

			//�΂߂̕�
			if (normal.y <= 0.6f && normal.y >= 2.0f)
			{
				// �ǂɉ����ė���
				VECTOR gravity = VGet(0, -1.0f, 0);
				VECTOR slideAlongWall = VCross(normal, gravity);
				slideAlongWall = VNorm(slideAlongWall);
				slideAlongWall = VScale(slideAlongWall, kColHitSlideLength * 1.0f);
				_resolvePos = VAdd(_resolvePos, slideAlongWall);
			}




			// �V��
			if (normal.y < 0.0f)
			{
				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				_resolvePos = VAdd(_resolvePos, pushOut);
			}
		}
	}

	if (!isGrounded)
	{
		_isGround = false;
	}
	else
	{
		_isGround = true;
	}

}

void Physycs::Update_Player()
{
	/*�|���S���Ƃ̐ڐG*/
	VECTOR pos = m_player->GetPosition();	
	PolygonHitCapsule(m_isGround, m_isWall, pos, m_player->GetCapsuleHeight(), m_player->GetRadius(), m_miniGame_Map1->GetModelHandle());
	m_player->SetPosition(pos);
	m_player->SetIsGround(m_isGround);

	/*�J�v�Z���Ƃ̐ڐG*/
}

void Physycs::Update_enemyFoxs()
{
	/*�|���S���Ƃ̐ڐG*/
	VECTOR pos[3];
	for (int i = 0; i < 3; i++)
	{
		pos[i] = m_enemyFoxs[i]->GetPosition();
		PolygonHitCapsule(m_isEnemyGround[i], m_isEnmeyWall[i], pos[i], m_enemyFoxs[i]->GetCapsuleHeight(), m_enemyFoxs[i]->GetRadius(), m_miniGame_Map1->GetModelHandle());
		m_enemyFoxs[i]->SetIsGround(m_isEnemyGround[i]);
		m_enemyFoxs[i]->SetPosition(pos[i]);
	}

	/*�J�v�Z���Ƃ̐ڐG*/
	CheckEnemyCollisions();

}

void Physycs::CheckEnemyCollisions()
{
	for (size_t i = 0; i < m_enemyFoxs.size(); ++i)
	{
		for (size_t j = i + 1; j < m_enemyFoxs.size(); ++j)
		{
			VECTOR pos1 = m_enemyFoxs[i]->GetPosition();
			VECTOR pos2 = m_enemyFoxs[j]->GetPosition();
			float radius1 = m_enemyFoxs[i]->GetRadius();
			float radius2 = m_enemyFoxs[j]->GetRadius();
			float height1 = m_enemyFoxs[i]->GetCapsuleHeight();
			float height2 = m_enemyFoxs[j]->GetCapsuleHeight();

			if (m_mathLib->Capsule_Capsule_HitCheck(pos1, height1, radius1, pos2, height2, radius2))
			{
				// �Փˉ���
				VECTOR resolveVec = m_mathLib->Line_Segment_Line_VECTOR(pos1, height1, pos2, height2);
				VECTOR moveVec = VScale(resolveVec, 0.01f);
				m_enemyFoxs[i]->SetPosition(VAdd(pos1, moveVec));
				m_enemyFoxs[j]->SetPosition(VSub(pos2, moveVec));
			}
		}
	}
}

void Physycs::CheckPlayerEnemyCollisions()
{
	VECTOR playerPos = m_player->GetPosition();
	float playerRadius = m_player->GetRadius();
	float playerHeight = m_player->GetCapsuleHeight();

	for (auto& enemy : m_enemyFoxs)
	{
		VECTOR enemyPos = enemy->GetPosition();
		float enemyRadius = enemy->GetRadius();
		float enemyHeight = enemy->GetCapsuleHeight();

		if (m_mathLib->Capsule_Capsule_HitCheck(playerPos, playerHeight, playerRadius, enemyPos, enemyHeight, enemyRadius))
		{
			// �Փˉ���
			VECTOR resolveVec = m_mathLib->Line_Segment_Line_VECTOR(playerPos, playerHeight, enemyPos, enemyHeight);
			VECTOR moveVec = VScale(resolveVec, 0.01f);
			m_player->SetPosition(VAdd(playerPos, moveVec));
			enemy->SetPosition(VSub(enemyPos, moveVec));
		}
	}
}
