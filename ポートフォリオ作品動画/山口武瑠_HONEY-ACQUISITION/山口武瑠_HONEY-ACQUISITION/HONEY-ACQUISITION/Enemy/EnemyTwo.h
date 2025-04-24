#pragma once
#include "..\Player\Player.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>
#include <ctime>
#include <cstdlib>

struct EnemyTwoData
{
	static const int Pos_X				   = 13;				//エネミー2  							＜X座標＞
	static const int Pos_Y				   = 16;				//エネミー2  							＜Y座標＞
	static const int moveSpeed			   = 1;					//エネミー  							＜速度＞
	static const int HitDamagedHandlePos_X = 0;					//プレイヤーと衝突した際の画像ハンドル	＜X座標＞
	static const int HitDamagedHandlePos_Y = 0;					//プレイヤーと衝突した際の画像ハンドル	＜Y座標＞
	static const int AfterTakingDamegeTime = 0;					//ダメージ演出時間の					＜初期値＞
	static const int FlashPoint			   = 0;					//ダメージ演出の際のフラッシュ			＜初期値＞
	static const int PlayerPosReset_X	   = 14;				//衝突した際のプレイヤーの座標リセット	＜X座標＞
	static const int PlayerPosReset_Y	   = 26;				//衝突した際のプレイヤーの座標リセット	＜Y座標＞
	static const int BUFTime			   = 60;				//プレイヤーがパワーフードを取得した時	＜停止バフ＞
};

struct NodeTwo
{
	int x;
	int y;
	int g;
	int h;
	NodeTwo* parent;

	NodeTwo(int x, int y, int g, int h, NodeTwo* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

	int f() const { return g + h; }

};

class PowerFeed;
class Player;
class Enemy;
class EnemyThree;
class EnemyTwo
{
public:
	EnemyTwo();
	~EnemyTwo();

	void Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Final();
	void enemyTwoSetHandle(int* handle) { TwoEnemyGraphHandle = *handle; }

	void MoveTowardsPlayerTwo(Player& player);								//敵１がプレイヤーを追いかける関数
	bool IsWallTwo(int x, int y);									//エネミーが壁を判断するための関数
	int CalculateHeuristicTwo(int x1, int y1, int x2, int y2);				//プレイヤーまでの距離を判断するヘリステック関数
	std::vector<NodeTwo*> AStarTwo(int startX, int startY, int goalX, int GoalY); //Aスターアルゴリズム

	int EnemyTwoCoordinate_X;
	int EnemyTwoCoordinate_Y;

	int TwoMoveSpeed;

	int TwoHitDamePos_X;
	int TwoHitDamePos_Y;

	int TwoEnemyGraphHandle;
	int TwoHitDamegeGraphHandle;
	int TwoGameOverGraphHandle;
	int TwoBUFEnemyHandle;

	int TwoDameSoundHandle;

	int TwoHitDameTime;
	int TwoHitPointFlash;

	bool TwoisGameOver;

	int TwoPowerFeedBUFTime;
	bool TwoBUF;
private:
	

};

