#include "SceneTransAnim.h"
#include "DxLib.h"
#include "../Scene/SceneManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


SceneTransAnim::SceneTransAnim() :
	ex					(672),
	ey					(400),
	px					(650),
	py					(400),
	time				(0),

	animPlayerHandle	(LoadGraph("img/BeeLeftAnim.png")),
	animEnemyHandle		(LoadGraph("img/brownbear2.png")),
	animBigFeedHandel	(LoadGraph("img/PowerHoney.png")),
	animEnemyHandHandle	(LoadGraph("img/BrownbearHand .png")),

	AnimSoundHandle_1	(LoadSoundMem("sound/Anim_1.mp3")),
	AnimSoundHandle_2	(LoadSoundMem("sound/Anim_2.wav"))
{
}

SceneTransAnim::~SceneTransAnim()
{
}

void SceneTransAnim::Init()
{
	ex					= 672;
	ey					= 400;
	px					= 614;
	py					= 400;
	time				= 0;

	animBigFeedHandel;
	animEnemyHandle;
	animPlayerHandle ;
	animEnemyHandHandle;

	AnimSoundHandle_1	= LoadSoundMem("sound/Anim_1.mp3");
	AnimSoundHandle_2	= LoadSoundMem("sound/Anim_2.wav");
	PlaySoundMem(AnimSoundHandle_2, DX_PLAYTYPE_LOOP);
}

void SceneTransAnim::Update()
{
	anim1Update();
}

void SceneTransAnim::Draw()
{
	
	anim1Draw();
}

void SceneTransAnim::Final()
{
	DeleteSoundMem(AnimSoundHandle_2);
	DeleteSoundMem(AnimSoundHandle_1);
}

void SceneTransAnim::anim1Update()
{
	if (ex >= -32)
	{
		ex -= 3;
	}

	if (px >= 300)
	{
		px -= 3;
	}

	if (ex <= -32)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Result);
	}
}

void SceneTransAnim::anim1Draw()
{
	DrawGraph		(ex + 40, ey, animEnemyHandle, true);
	DrawGraph		(px, py, animPlayerHandle, true);
	
	if (px <= 300)
	{
		DrawGraph	(px, py, animEnemyHandHandle, true);
		
	}
	if (ex <= 300)
	{
		PlaySoundMem(AnimSoundHandle_1, DX_PLAYTYPE_BACK);
	}

}

void SceneTransAnim::anim2Update()
{
}

void SceneTransAnim::anim2Draw()
{
}


