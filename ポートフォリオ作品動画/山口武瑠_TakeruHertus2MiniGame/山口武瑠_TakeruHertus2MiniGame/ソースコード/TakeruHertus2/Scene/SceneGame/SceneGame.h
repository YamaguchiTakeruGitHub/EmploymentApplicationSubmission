#pragma once
#include "../Base/SceneBase.h"
#include "SceneGameCommon.h"
#include "../../MathLib/MathLib.h"

/*���Ȃ̂ł��Ƃňڍs���܂�*/
namespace ColInfo
{
	//�ő哖���蔻��|���S����
	constexpr int kMaxColHitPolyNum = 2000;
	//�ǉ����o�������̍ő厎�s��
	constexpr int kMaxColHitTryNum = 16;
	//�ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kColHitSlideLength = 1.0f;
}


class SceneGame : public SceneBase
{
private:
    /*�L�����N�^�[*/
	std::shared_ptr<Player> m_player;       //�v���C���[
    std::shared_ptr<EnemyFox> m_enemyFox;   //�ς̓G

	/*�G�}�l�[�W���[*/
	std::shared_ptr<EnemyManager> m_enemyManager;//�G�̃}�l�[�W��

    /*�J����*/
	std::shared_ptr<Camera> m_camera;       //�J����
	/*�}�b�v*/
	std::shared_ptr<TutorialMap> m_tutorialMap;//�`���[�g���A���}�b�v

	/*���j���S��*/
	std::shared_ptr<MenuSystem> m_menuSystem;
	
	/*�R�}���h�n*/
	std::shared_ptr<Command> m_command;


	/*���w�֐�*/
	std::shared_ptr<MathLib> m_mathLib;

	/*�ϐ��錾*/
	bool m_isLoading;//���[�h�����ǂ���
	bool m_isOpenMenu;//���j���[���J���Ă��邩�ǂ���

	//bool m_isBattle;//�퓬�����ǂ���

	void PlayerControlCamera();


public:
	SceneGame();
	~SceneGame()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void IsTestPhsycse();
	void IsTestPhsycseEnemy();

	void CapsuleHitResolve();


private:
	bool m_isLookOn = false;


	/*�Z�[�u�e�X�g����*/
	VECTOR m_savePointPos = VGet(0,20,0);
	float m_savePointRadius = 50.0f;
	void SavePoint();
	void SaveGame();
	int TestHiScore = 0;


	/*�e�X�g�p�ϐ�*/
	VECTOR boxPos;
	VECTOR boxSize;

	/*�����C�g*/
	int lightHandle;

	/*�����蔻��̃e�X�g*/
	struct Polygon
	{
		VECTOR vertex[3];
		VECTOR Normal = VGet(0,0,0);
		VECTOR center = VGet(0,0,0);
	}m_polygon[3];

	MV1_COLL_RESULT_POLY_DIM m_hitDim{};




};

