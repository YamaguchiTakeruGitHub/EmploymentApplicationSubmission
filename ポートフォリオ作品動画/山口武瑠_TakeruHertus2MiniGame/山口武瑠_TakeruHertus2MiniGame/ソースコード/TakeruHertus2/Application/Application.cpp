#include "Application.h"
#include "GameConstant.h"

Application::Application(SceneManager& _sceneManager)
	: m_sceneManager(_sceneManager)
{
}

Application::~Application()
{
	m_sceneManager.Final();//呼び出されるごとに解放
}

bool Application::Init_App()
{
	SetWindowText("Test");//ウィンドウに表示される名前

	ChangeWindowMode(true);//全画面:false ウィンドウ画面:true

	SetGraphMode(GAMECONSTANT::k_WindowWidth, GAMECONSTANT::k_WindowHeigth, 16);//表示する画面の大きさとカラーバッファ

	SetUseDirect3DVersion(DX_DIRECT3D_11);//Direct3Dのバージョンをセットする

	/*DxLibの初期化*/
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	/*エふぇくしあの初期化*/
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//裏画面描画をセット
	SetDrawScreen(DX_SCREEN_BACK);

	//グラフィックモードに変更するかどうか
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	//グラフィックデバイスがなくなったらコールバックする
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	/*3D初期化*/
	SetUseZBuffer3D(true);	//Zバッファを扱うか
	SetWriteZBuffer3D(true);//Zバッファに書き込むか
	SetUseBackCulling(true);//３Dモデル裏面の描画を扱うか

	/*各初期化*/
	m_sceneManager.Init();

	return true;
}

void Application::Run_App()
{
	while (ProcessMessage() != -1)
	{
		//フレーム時刻を格納
		LONGLONG start = GetNowHiPerformanceCount();
		//画面を掃除
		ClearDrawScreen();

		/*各更新*/
		m_sceneManager.Update();
		m_sceneManager.Draw();

		//裏画面と表画面の交換
		ScreenFlip();

		//スペースキー入力によるゲームの強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		//FPSを60で固定
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}
}

void Application::close_App()
{
	/*各解放*/
	m_sceneManager.Final(); //シーンマネージャーの解放
	Effkseer_End();			//エふぇくしあの解放
	DxLib_End();			//DxLibの解放
}
