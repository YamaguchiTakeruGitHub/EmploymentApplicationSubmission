#include "Player.h"
#include "../../GameTag.h"
#include "../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"

/// <summary>
/// �v���C���[�̃p�����[�^�[
/// </summary>
namespace PLAYER_PARAMETER
{
	static constexpr float POS_X = 0.0f;//X���W
	static constexpr float POS_Y = 0.0f;//Y���W
	static constexpr float POS_Z = 60.0f;  //Z���W

	static constexpr float COMBO_MOVE_2 = 0.2f;//�R���{�Q�̈ړ�����
	static constexpr float COMBO_MOVE_3 = 0.1f;//�R���{�R�̈ړ�����

	static constexpr int COMBO_MAXNUM = 3;//�ő�R���{��
	static constexpr float COMBO_RUNTIME = 120.0f;//�R���{��������
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
	: filename	("")//�t�@�C���̖��O
	, Data		()	//�t�@�C���̃f�[�^

	, m_AttackPosition(VGet(0,0,0))
	, m_AttackRadius(0)
{
	/*�R���|�[�l���g�𐶐�*/
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

	//�R���{�V�X�e��
	AddComponent<ComponentComboSystem>();
	m_comboSystem = GetComponent<ComponentComboSystem>();

	//�X�e�[�^�X
	AddComponent<ComponentStatus>();
	m_status = GetComponent<ComponentStatus>(); 

}

Player::~Player()
{
}

void Player::Init()
{
	/*CSVLib������*/
	filename = "../Data/GameData/PlayerData.csv";//�t�@�C���̃p�X
	Data = CSVLib::ReadCSV(filename);			 //�t�@�C���̓ǂݍ���

	/*�R���|�[�l���g�̏�����*/
	Entity::InitComponent();

	/*Transform�̏�����*/
	m_transform->position = VGet(PLAYER_PARAMETER::POS_X,	//�|�W�V�����̏����ʒu_X
								 PLAYER_PARAMETER::POS_Y,	//�|�W�V�����̏����ʒu_Y
								 PLAYER_PARAMETER::POS_Z);	//�|�W�V�����̏����ʒu_Z

	m_transform->scale = VGet(CSVLib::GetCell_float(Data, 3, 2),	//���f���̃T�C�YX
							  CSVLib::GetCell_float(Data, 3, 2),	//���f���̃T�C�YY
						      CSVLib::GetCell_float(Data, 3, 2));	//���f���̃T�C�YZ

	/*���f���̏�����*/
	m_model->LoadModel("../Data/Asset/3D/Player/Player.mv1");

	/*�J�v�Z���̏�����*/
	m_capsule->radius = CSVLib::GetCell_float(Data,1, 2);	//�J�v�Z���̔��a
	m_capsule->height = CSVLib::GetCell_float(Data, 2, 2);	//�J�v�Z���̃T�C�Y

	/*�R���{������*/
	m_comboSystem->SetComboResetTime(PLAYER_PARAMETER::COMBO_RUNTIME);//�R���{�����Z�b�g���鎞��
	m_comboSystem->SetComboMaxCount(PLAYER_PARAMETER::COMBO_MAXNUM);//�ő�R���{��

	/*�X�e�[�^�X������*/
	m_status->SetHp(100.0f);
	m_status->SetAttackValue(10);

	/*�U���͈�*/
	m_AttackPosition = VGet(0, 0, 0);
	m_AttackRadius = 0.0f;
}

void Player::Update()
{
	/*�A�j���[�V�����̍X�V*/
	UpdateAnimation();

	/*�X�e�[�^�X�̍X�V*/
	//m_status->SetHp(100.0f);
	//m_status->SetAttackValue(10);
	
	/*�R���|�[�l���g�̍X�V*/
	Entity::UpdateComponent();

	/*�s�������̍X�V*/
	UpdateMomvement();

	/*�R���{�n�����̍X�V*/
	UpdateCombo();

	/*���f���̃A���O���Ƒ傫���ƍ��W���X�V*/
	MV1SetRotationXYZ(m_model->m_modelHandle, VGet(0.0f, m_transform->angle * DX_PI_F / 180.0f, 0.0f));//�p�x�����W�A���ɕϊ����ăZ�b�g����
	MV1SetScale(m_model->m_modelHandle, m_transform->scale);
	MV1SetPosition(m_model->m_modelHandle, m_transform->position);
}

void Player::Draw()
{
	/*�R���|�[�l���g�̕`��*/
	Entity::DrawComponent();

#ifdef _DEBUG
	/*DrawFormatString(0, 40, 0xfffffff, "Player:HP:%f", m_status->GetHp());
	DrawFormatString(0, 60, 0xfffffff, "Player:AttackValue:%d", m_status->GetAttackValue());*/

	// �v���C���[�̌����Ă���������f�o�b�O�`��
	VECTOR startPos = m_transform->position;
	VECTOR direction = VGet(sinf(m_transform->angle * DX_PI_F / 180.0f), 0.0f, cosf(m_transform->angle * DX_PI_F / 180.0f));
	VECTOR endPos = VAdd(startPos, VScale(direction, 50.0f)); // 50.0f �͐��̒���
	//DrawLine3D(startPos, endPos, GetColor(255, 0, 0)); // �ԐF�ŕ`��

	/*�U���͈�*/
	m_AttackPosition = VAdd(VAdd(startPos, VGet(0, 30.0f, 0)), VScale(direction, 10.0f));
	m_AttackRadius = 20.0f;

	//DrawSphere3D(VAdd(VAdd(startPos, VGet(0,30.0f,0)), VScale(direction, 10.0f)), 20.0f, 5, 0xffffff, 0xffffff, false);
#endif // _DEBUG

}

void Player::Final()
{
	/*�R���|�[�l���g�̉��*/
	Entity::FinalComponent();
}


void Player::UpdateCombo()//�R���{�n����
{
	/*�R���{�֘A*/
	if (m_isAttackCheck == true)
	{
		//���̃R���{��
		m_comboSystem->IncrementCombo();
	}

	//�U�����ł���΃v���C���[���͂ɂ��ړ��������s��Ȃ�
	//�łȂ���Έړ��������s��
	m_movement->SetIsAttacking(m_comboSystem->GetIsCombo());
}

void Player::UpdateAnimation()//�A�j���[�V�����n����
{
	/*���s���ł����*/
	if (m_movement->GetIsMove() == true && m_movement->GetIsJump() == false)
	{
		m_animation->PlayAnim(8);//Move�A�j���[�V����
	}
	else if (m_movement->GetIsMove() == false && m_movement->GetIsJump() == false)
	{
		m_animation->PlayAnim(4);//Idel�A�j���[�V����
	}

	if (m_movement->GetIsJump() == true)
	{
		m_animation->PlayAnim(5);//Jump�A�j���[�V����
	}

	// �R���{�����ς������A�j���[�V�����̍Đ����Ԃ����Z�b�g����
	if (m_comboSystem->GetComboCount() != m_comboSystem->GetComboOldCount())
	{
		m_animation->ResetAnimationNowTime();
		m_comboSystem->SetComboOldCount(m_comboSystem->GetComboCount());
	}

	/*�U���R���{*/
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
	/*�s���̍X�V(�R���X�g���N�^�Ăяo�����Ƀ^�O��ݒ�ł���悤�ɂ�����)*/
	m_movement->SetTag(TagCharacterObject::PLAYER);

	/*�U���R���{�ɂ��ړ�����*/
	if (m_comboSystem->GetComboCount() == 2)
	{
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_2);
	}
	if (m_comboSystem->GetComboCount() == 3)
	{
		m_transform->position = m_movement->Update_AttackMove(PLAYER_PARAMETER::COMBO_MOVE_3);
	}
}
