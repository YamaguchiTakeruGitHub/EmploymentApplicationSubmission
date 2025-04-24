#pragma once

class Player;
class Enemy;

class UI
{
public:
	UI();
	~UI();

	void Init(Player& player, Enemy& enemy);
	void Update(Player& player, Enemy& enemy);
	void Draw(Player& player, Enemy& enemy);
	void Final();

	
	int flashPoint;
	int highScore;

	int playerScoreHandle;


};

