#pragma once
class SceneManager;

class SceneTitlestandBy
{
public:
	SceneTitlestandBy();
	~SceneTitlestandBy();

	void init();
	void Update();
	void Draw();
	void Final();

	int playerSTHandle;
	int enemySTHandle;
	int enemySTHandleTwo;
	int enemySTHandleThree;
	int honeySTHandle;
	int powerHoneySTHandle;
	int potechiSTHandle;

	int m_TitleStandBySoundHandle;

	int FeedanimPointFlash;

	int cax;
	int cay;
	int px;
	int py;
	int ex;
	int ey;
	int extwo;
	int eytwo;
	int hx;
	int hy;
	int phx;
	int phy;
	int pox;
	int poy;
	int Pvx;
	int Pvy;
	
	int timeCount;

};

