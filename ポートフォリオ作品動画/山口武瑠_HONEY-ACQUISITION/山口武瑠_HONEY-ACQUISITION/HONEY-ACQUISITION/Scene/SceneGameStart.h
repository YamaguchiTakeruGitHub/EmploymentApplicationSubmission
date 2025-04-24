#pragma once

class Map;
class SceneManager;
class SceneGameStart
{
public:
	SceneGameStart();
	~SceneGameStart();

	void Init();
	void Update();
	void Draw();
	void Final();

	int Time;
	int StartText;
	int PoText;

	int GSBHandle;

	int StartTime;
	bool StartTimeFlag;

	int FeedhandleStart;

	int GSPlayerHandle;

	int GSPlayerRogoHandle;

	int GSFlashPoint;

	//void SetSceneGameStartSound(int* handle) { m_GameStartSound = *handle; }

private:

	int m_GameStartSound;

};

