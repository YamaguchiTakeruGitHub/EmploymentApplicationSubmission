#pragma once
class PauseScene
{
public:
	PauseScene();
	~PauseScene();

	void Init();
	void Update();
	void Draw();
	void End();

	bool PauseBottonFlag;

private:
	int PauseBgGraphHandle;

};

