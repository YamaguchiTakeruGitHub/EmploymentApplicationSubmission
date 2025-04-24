#pragma once


class SceneMain;
class TitleScene;
class SceneResult;
class SceneGameClear;
class SceneTitlestandBy;
class SceneGameStart;
class SceneTransAnim;
class UI;
class SceneFeedGetGameClear;

class SceneManager
{
public:

	typedef enum
	{
		eScene_Title,
		eScene_Main,
		eScene_Result,
		eScene_Clear,
		eScene_TStandBy,
		eScene_GameStart,
		eScene_anim,
		eScene_GameClear,

		eScene_None,
	}eScene;

	 
	
	SceneManager();
	~SceneManager();

	void Init();
	void Final();
	void Update();
	void Draw();

	static void SceneMgr_ChangeScene(eScene NextScene);
	
	void InitalizeModule(eScene scene);
	void FinalizeModule(eScene scene);

	static void ScorePlayerCountManager(int score, int point);

	void addScore(int points);

	bool GameOver_Flag;

	int m_score;

private:

	

	SceneMain*			   m_pMain;
	TitleScene*			   m_pTitle;
	SceneResult*		   m_pResult;
	SceneGameClear*		   m_pClear;
	SceneTitlestandBy*	   m_pTStandBy;
	SceneGameStart*		   m_pGameStart;
	SceneTransAnim*		   m_pTransAnim;
	UI*					   m_pUI;
	SceneFeedGetGameClear* m_pGetGameClear;
};

