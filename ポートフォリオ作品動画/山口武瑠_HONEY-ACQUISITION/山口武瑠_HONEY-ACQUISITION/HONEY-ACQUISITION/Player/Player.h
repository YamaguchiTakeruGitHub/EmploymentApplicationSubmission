#pragma once

/*****************************～説明書～*************************************/
//①コメントの末尾の＜＞に変更してもよい値かを記入しております。			 /
//②初期値または変更不と書いてある値の変更はしないでください。				 /
//③変更可能な値の中で位置座標を変更する際は変更された方が調整してください。 /  
/****************************************************************************/

#include "../Game.h"		//ゲームヘッダー
#include "../Feed/Feed.h"	//フードヘッダー
#include "../Enemy/Enemy.h"	//エネミーヘッダー

/// <summary>
/// ≪ユーザー定義≫
/// プレイヤーのデータ値変数
/// </summary>
struct PlayerData
{
	static constexpr int ComplexPosX			 =  0;	//虚数用変数　		＜ X座標 /初期値 /変更不＞
	static constexpr int ComplexPosY			 =  0;	//虚数用変数　		＜ Y座標 /初期値 /変更不＞
	static const     int Pos_X					 = 14;	//プレイヤー　		＜ X座標 /初期値 /変更可＞
	static const     int Pos_Y					 = 26;	//プレイヤー　		＜ Y座標 /初期値 /変更可＞
	static const     int PrevPos_X				 =	0;	//前フレーム位置	＜ X座標 /初期値 /変更不＞
	static const     int PrevPos_Y				 =  0;	//前フレーム位置	＜ Y座標 /初期値 /変更不＞
	static const     int KeyNumber				 =  0;	//キー		　		＜初期値         /変更不＞
	static const	 int FrameNumber			 = 60;	//フレーム制御		＜初期値         /変更不＞
	static const	 int ClearNumber			 =  0;	//クリア用	　		＜初期値         /変更不＞
	static const	 int RemainingMachines		 =  3;	//プレイヤー　		＜  残機         /変更可＞
	static const	 int ScoreContainer			 =  0;	//スコア			＜初期値         /変更可＞
	static const	 int InputKeyContainer		 =  0;	//キー情報	　		＜初期値         /変更不＞
	static const	 int InputKeyContainerOne	 =  1;	//上キー情報　		＜固定値         /変更不＞
	static const	 int InputKeyContainerTwo	 =  2;  //下キー情報		＜固定値　　　　 /変更不＞
	static const	 int InputKeyContainerThree	 =  3;	//左キー情報		＜固定値　　　　 /変更不＞
	static const     int InputKeyContainerFour	 =  4;	//右キー情報		＜固定値　　　　 /変更不＞
};


/// <summary>
/// ≪ユーザー定義≫方向enum
/// </summary>
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Feed;
class Enemy;
class SceneManager;
class Sound;
class UI;

class Player
{
public:
	Player();
	~Player();

	void Init(Enemy& enemy, UI& ui);
	void Update(Enemy& enemy, Feed& feed, UI& ui);
	void Draw(Enemy& enemy, UI& ui);
	void Final();

	Direction GetCurrentDirection() const;

	void ChangeDirection(Direction newDirection);

	void playerSetHandle(int* handle) { m_playerHandle = *handle; }

	bool isWall(int x, int y);

	void FileWritingScore(int S);

	void UpdatePlayerEffect();
	void DrawPlayerEffect();

	int PlayerPos_X;
	int PlayerPos_Y;

	int ky;
	int kx;
	
	int PrevPlayerPox_X;
	int PrevPlayerPox_Y;
	
	int ClearManager;


	int score;
 
	int FrameRate;

	int m_playerHandle;

	bool Player_GameOverFlag;

	int ResidueHandle;
	int ResidueHandle2;
	int ResidueHandle3;


	int PlayerResidue;
	

	
	int BeeHandleUp;
	int BeeHandleDown;
	int BeeHandleRight;
	int BeeHandleLeft;

	bool AnimUP;
	bool AnimDOWN;
	bool AnimLEFT;
	bool AnimRIGHT;

	int UPThought;
	int DownThought;
	int LeftThought;
	int RightThought;

	int PreviousKey;
	int PlayerMapData[36][28];
	
	bool UpFlag;
	bool DownFlag;
	bool LeftFlag;
	bool RightFlag;

private:
	
	int KEY;

	Direction currentDirection;
};

