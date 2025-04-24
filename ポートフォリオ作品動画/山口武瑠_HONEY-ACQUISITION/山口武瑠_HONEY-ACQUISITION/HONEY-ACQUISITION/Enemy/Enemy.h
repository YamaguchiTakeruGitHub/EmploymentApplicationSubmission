#pragma once
#include "..\Player\Player.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>

struct Node
{
	int x;
	int y;
	int g;
	int h;
	Node* parent;

	Node(int x, int y, int g, int h, Node* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

	int f() const { return g + h; }

};

struct EnemyData
{
	static const int Pos_X				    = 13;								//エネミー  							＜X座標＞
	static const int Pos_Y				    = 16;								//エネミー  							＜Y座標＞
	static const int TwoPos_X			    = 13;								//エネミー2  							＜X座標＞
	static const int TwoPos_Y			    = 16;								//エネミー2  							＜Y座標＞
	static const int moveSpeed			    =  1;								//エネミー  							＜速度＞
	static const int HitDamagedHandlePos_X  =  0;								//プレイヤーと衝突した際の画像ハンドル	＜X座標＞
	static const int HitDamagedHandlePos_Y  =  0;								//プレイヤーと衝突した際の画像ハンドル	＜Y座標＞
	static const int AfterTakingDamegeTime  =  0;								//ダメージ演出時間の					＜初期値＞
	static const int FlashPoint			    =  0;								//ダメージ演出の際のフラッシュ			＜初期値＞
	static const int PlayerPosReset_X	    = 14;							    //衝突した際のプレイヤーの座標リセット	＜X座標＞
	static const int PlayerPosReset_Y	    = 26;							    //衝突した際のプレイヤーの座標リセット	＜Y座標＞
	static const int BUFTime				= 60;								//プレイヤーがパワーフードを取得した時	＜停止バフ＞
	static const int DameTime				=  0;
};

class PowerFeed;
class Player;
class EnemyTwo;
class EnemyThree;
class Enemy
{
public:
		 Enemy					();												//EnemyConstructor
		~Enemy					();												//EnemyDestructor
	void Init					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//初期化
	void Update					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//更新
	void Draw					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//描画
	void Final					();												//終了
	void enemyBlinkySetHandle	(int* handle) { EnemyGraphHandle = *handle; }	//SceneMainで参照管理する画像ハンドル関数
	void MoveTowardsPlayer		(Player& player);								//敵１がプレイヤーを追いかける関数
	bool IsWall					(int x, int y);									//エネミーが壁を判断するための関数
	int CalculateHeuristic		(int x1, int y1, int x2, int y2);				//プレイヤーまでの距離を判断するヘリステック関数
	std::vector<Node*> AStar	(int startX, int startY, int goalX, int GoalY); //Aスターアルゴリズム

	int EnemyCoordinate_Y;
	int EnemyCoordinate_X;

	int HitDamePos_X;
	int HitDamePos_Y;

	int EnemyGraphHandle;
	int HitDamegeGraphHandle;
	int GameOverGraphHandle;
	
	int DameSoundHandle;
	
	int HitDameTime;
	int HitPointFlash;
	
	float MoveSpeed;
	
	bool isGameOver;

	int BUFEnemyHandle;

	int PowerFeedBUFTime;
	bool BUF;

};



