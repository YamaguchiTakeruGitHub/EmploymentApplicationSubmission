#include "DxLib.h"
#include "Game.h"
#include"Scene/SceneManager.h"
#include "Scene/SceneResult.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetWindowText("HaneyAcception");
	SetGraphMode(Game::WindowWidth, Game::WindowHeight - 50, Game::ColorBit);

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(false);//true小さい表示//falseフルスクリーン

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager;

	pScene->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		//画面を覆う半透明(6％の不透明度)の四角を表示している
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16);
		DrawBox(0, 0, 640, 480, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, false);


		pScene->Update();//更新

		pScene->Draw();//描画
		 
		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}


		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	pScene->Final();

	delete pScene;//メモリの解放

	pScene = nullptr;//pSceneを空にする

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}