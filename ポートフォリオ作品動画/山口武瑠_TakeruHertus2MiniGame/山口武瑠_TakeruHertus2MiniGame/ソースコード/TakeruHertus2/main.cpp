#include "Application/Application.h"
#include "Scene/Manager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//参照でのインスタンス化を行い
	SceneManager& sceneManager = SceneManager::GetInstance();

	//参照で生成した変数をアプリケーションに渡す
	Application app(sceneManager);//処理の実行

	if (!app.Init_App())//アプリケーションの初期
	{
		return -1;
	}

	app.Run_App();//アプリケーションの実行
	app.close_App();//アプリケーションの解放

	return 0;
}

/*MEMO*/

//2025.2.10 明日やることはコンフィグを作成してボタンの決定とキャンセルのトランスと音量調整とか
			//色々作る
