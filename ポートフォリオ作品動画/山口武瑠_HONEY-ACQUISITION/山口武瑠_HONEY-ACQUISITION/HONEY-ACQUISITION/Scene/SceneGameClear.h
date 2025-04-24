#pragma once
class Player;
class SceneManager;
class SceneGameClear
{
public:
	
	SceneGameClear();
	~SceneGameClear();

	void Init();
	void Final();
	void Update();
	void Draw();

	int flowerHandle;
	int souzenHandle;
	int beehandle;
	int torideHandle;
	int bakuhatuHandle;
	int kowaretasiroHandle;
	int eeekeyhandle;
	int beePosX;
	int beePosY;



};

