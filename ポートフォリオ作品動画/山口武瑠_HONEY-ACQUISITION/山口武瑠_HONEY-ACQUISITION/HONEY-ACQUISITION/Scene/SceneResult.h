#pragma once
class SceneResult
{
public:
	SceneResult();
	~SceneResult();

	void Init();
	void Update();
	void Draw();
	void Final();
	
	
	int arrowPos_x;
	int arrowPos_y;

	int BoxPos_x1;
	int BoxPos_x2;
	int BoxPos_y1;
	int BoxPos_y2;

	int ArrowPosX;
	int ArrowPosY;

	bool EndGameBotton;

	int ResultSoundHandle;

private:
	int ResultHandle;
	int TitleBackHandle;
	int ArrowHandle;
	int RetryHandle;

	int hakaHanlde;

};

