#pragma once
#include "SceneManager.h"

enum CoinBUT
{
	Push_C
};


class SceneManager;
class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Update();
	void Draw();
	void Final();
	void UpdateTitleAnim1();
	void DrawTitleAnim1();

	int SceneCheang;
	int SceneChangTime;
	bool SceneChangTimeFlag;
	int TitleSrectBerHandle;
	int timeCount;

	int TitleSound;

	int Title_X;
	int Title_Y;

	int TitleHandle;

private:

	int TitleLogo;
	int TitleBotton;
	int flashingPoint;
	CoinBUT Getcoinbut() const;
	int KEY;

	int TitleAnimPlayerHandle;
	int TitleAnimEnemyHandle;
	int TitleAnimEnemyTwoHandle;
	int TitleAnimEnemyThreeHandle;

	int taPx;
	int taPy;
	int taEx;
	int taEy;

public:
	bool TitleBottonFlag;
	int CoinCredits;
	bool CreditsFlag;
	bool PushBottonFlag;
	CoinBUT coinbut;
	bool BrightnessAdjustmentFlag;
	int BrightnessAdjustmentLevl;


};

