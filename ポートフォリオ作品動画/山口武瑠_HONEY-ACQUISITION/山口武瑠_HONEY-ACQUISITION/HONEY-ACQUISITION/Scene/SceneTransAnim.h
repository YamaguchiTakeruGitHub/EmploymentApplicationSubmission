#pragma once

class SceneManager;
class SceneTransAnim
{
public:
	SceneTransAnim();
	~SceneTransAnim();

	void Init();
	void Update();
	void Draw();
	void Final();
	
	void anim1Update();
	void anim1Draw();

	void anim2Update();
	void anim2Draw();

private:
	int animPlayerHandle;
	int animEnemyHandle;
	int animBigFeedHandel;
	int animEnemyHandHandle;

	int ex;
	int ey;
	int px;
	int py;

	int time;

	int AnimSoundHandle_1;
	int AnimSoundHandle_2;


};

