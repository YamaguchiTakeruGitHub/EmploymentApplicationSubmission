#include "DxLib.h"
#include "../Game.h"
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../Feed/PowerFeed.h"
#include "..\Enemy\EnemyTwo.h"
#include "../Enemy/EnemyThree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>



Enemy::Enemy() :	
	EnemyCoordinate_Y		(EnemyData::Pos_Y),							//敵の＜Y座標＞初期化
	EnemyCoordinate_X		(EnemyData::Pos_X),							//敵の＜X座標＞初期化
	MoveSpeed				(EnemyData::moveSpeed),						//敵の＜速度＞初期化
	HitDamePos_X			(EnemyData::HitDamagedHandlePos_X),			//画像ハンドル＜HitDamegeHandle＞の＜X座標＞初期化
	HitDamePos_Y			(EnemyData::HitDamagedHandlePos_Y),			//画像ハンドル＜HitDamegeHandle＞の＜Y座標＞初期化
	HitDameTime				(EnemyData::AfterTakingDamegeTime),			//プレイヤーと敵があたった際の＜演出時間＞初期化
	HitPointFlash			(EnemyData::FlashPoint),					//画像ハンドル＜HitDamegeHandle＞の＜フラッシュ演出＞初期化
	isGameOver				(false),									//ゲームオーバーを判定するための＜フラグ＞初期化
	BUF						(false),									//バフフラグ
	HitDamegeGraphHandle	(LoadGraph("img/Damage.png")),				//HitDamegeHandle＜グラフハンドル＞の初期化
	EnemyGraphHandle		(LoadGraph("img/brownbear.png")),			//m_enemyBlinkyHandle＜グラフハンドル＞の初期化
	GameOverGraphHandle		(LoadGraph("img/GAMEOVERTEXT.png")),		//m_GameOverHandle＜グラフハンドル＞の初期化
	BUFEnemyHandle			(LoadGraph("img/brownbearSleepOne.png")),	//バフ効果をくらった際の敵＜グラフハンドル＞の初期化
	DameSoundHandle			(LoadSoundMem("img/Dameg.mp3")),			//DameSoundHandle＜サウンドハンドル＞の初期化
	PowerFeedBUFTime		(EnemyData::BUFTime)						//プレイヤーがパワー餌を取得した際のバフ初期化
{
}

Enemy::~Enemy()
{
	DeleteGraph(EnemyGraphHandle);
	DeleteGraph(GameOverGraphHandle);
	DeleteGraph(HitDamegeGraphHandle);
	DeleteSoundMem(DameSoundHandle);
}

void Enemy::Init(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	EnemyCoordinate_Y	  = EnemyData::Pos_Y;
	EnemyCoordinate_X	  = EnemyData::Pos_X;
	MoveSpeed			  = EnemyData::moveSpeed;
	HitDamePos_X		  = EnemyData::HitDamagedHandlePos_X;
	HitDamePos_Y		  = EnemyData::HitDamagedHandlePos_Y;
	HitPointFlash	  	  = EnemyData::FlashPoint;
	HitDameTime			  = EnemyData::DameTime;
	isGameOver			  = false;
	BUF					  = false;
	HitDamegeGraphHandle  = LoadGraph("img/Damage.png");
	EnemyGraphHandle	  = LoadGraph("img/brownbear.png");
	GameOverGraphHandle	  = LoadGraph("img/GAMEOVERTEXT.png");
	BUFEnemyHandle        = LoadGraph("img/brownbearSleepOne.png");
	DameSoundHandle		  = LoadSoundMem("sound/Dameg.mp3");
}

void Enemy::Update(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		BUF = true;
	}
	//敵の処理
	if (player.PlayerPos_X >= EnemyCoordinate_X + 1 || player.PlayerPos_X <= EnemyCoordinate_X - 1 || player.PlayerPos_Y >= EnemyCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyCoordinate_Y - 1) //敵の座用より外側にいたときの処理
	{
		if (BUF == true)
		{
			PowerFeedBUFTime--;

			if (BUF == true)
			{
				if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
				{
					PowerFeedBUFTime = 30;
				}
			}

			//値が10になったら０にする
			if (PowerFeedBUFTime == 0)
			{
				PowerFeedBUFTime = 60;
				BUF = false;
			}
		}

		if (BUF == false)
		{
			MoveTowardsPlayer(player); //A*アルゴリズムを使用したプレイヤーの追跡
		}

		if (player.ClearManager != 244)
		{
			if (player.PlayerPos_X >= EnemyCoordinate_X && player.PlayerPos_X <= EnemyCoordinate_X) //当たり判定＜Ｘ座標＞
			{
				if (player.PlayerPos_Y >= EnemyCoordinate_Y && player.PlayerPos_Y <= EnemyCoordinate_Y) //当たり判定＜Ｘ座標＞
				{
					HitDameTime = 10; //当たり判定を通過した際にHitDameTimeに値ー＞10入る
					player.PlayerResidue -= 1; //プレイヤーの残機を一つ減らす

					if (player.PlayerResidue == 2) //プレイヤーの残機が２個になったとき
					{
						/*敵の座標とプレイヤーの座標を初期値に戻す*/
						player.PlayerPos_X = EnemyData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyData::PlayerPosReset_Y;

						EnemyCoordinate_Y = EnemyData::Pos_Y;
						EnemyCoordinate_X = EnemyData::Pos_X;

						enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
					}

					if (player.PlayerResidue == 1) //プレイヤーの残機が1個になったとき
					{
						/*敵の座標とプレイヤーの座標を初期値に戻す*/
						player.PlayerPos_X = EnemyData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyData::PlayerPosReset_Y;

						EnemyCoordinate_Y = EnemyData::Pos_Y;
						EnemyCoordinate_X = EnemyData::Pos_X;

						enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
					}
					if (player.PlayerResidue == 0) //プレイヤーの残機が0個になったとき
					{
						isGameOver = true; //ゲームオーバー用のフラグにtrueを入れる
					}
				}
			}
		}
	}
	
	//敵とプレイヤーがあたった時のフラッシュ更新
	if (HitDameTime > 0)
	{
		// 時間を減らす
		HitDameTime--;
		//文字点滅の値を追加していく
		HitPointFlash++;
		//値が10になったら０にする
		if (HitPointFlash == 20)
		{
			HitPointFlash = 0;
		}

		// 10秒経過した場合の処理
		if (HitDameTime >= 0)
		{
			// ここに10秒経過後の処理を追加する
			if (HitDamePos_X <= 0 && HitDamePos_X >= 60 && HitDamePos_Y <= 0 && HitDamePos_X >= 60)
			{
				HitDamePos_X += 10;
				HitDamePos_Y += 10;
			}
			if (HitDamePos_X >= 60 && HitDamePos_Y >= 60)
			{
				HitDamePos_X -= 10;
				HitDamePos_Y -= 10;
			}
		}
	}

	if (isGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void Enemy::Draw(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	if (HitDameTime > 0)
	{
		// 時間を減らす
		HitDameTime--;

		// 10秒経過した場合の処理
		if (HitDameTime >= 0)
		{
			if (HitPointFlash == 1 || HitPointFlash == 2 || HitPointFlash == 4 || HitPointFlash == 5 || HitPointFlash == 8 || HitPointFlash == 10)
			{
				DrawGraph(HitDamePos_X, HitDamePos_Y, HitDamegeGraphHandle, true);
				PlaySoundMem(DameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}

	if (BUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG

	}

	if (BUF == false)
	{
		DrawGraph(EnemyCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, EnemyGraphHandle, true);
	}
	
	if (BUF == true)
	{
		DrawGraph(EnemyCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, BUFEnemyHandle, true);
	}
}

void Enemy::Final()
{
	DeleteGraph(EnemyGraphHandle);
	DeleteGraph(GameOverGraphHandle);
	DeleteGraph(HitDamegeGraphHandle);
	DeleteGraph(BUFEnemyHandle);
	DeleteSoundMem(DameSoundHandle);
}



void Enemy::MoveTowardsPlayer(Player& player)
{
	/*std::vector<Node*> path = AStar(eb_x, eb_y, player.px, player.py);

	if (!path.empty())
	{
		Node* nextNode = path[1];
		if (!IsWall(nextNode->x, nextNode->y))
		{
			eb_x = nextNode->x;
			eb_y = nextNode->y;
		}
	}*/
	
	std::vector<Node*> path = AStar(EnemyCoordinate_X, EnemyCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		Node* nextNode = path[1];
		if (!IsWall(nextNode->x, nextNode->y))
		{
			// 移動速度を考慮して位置を更新
			float deltaX = static_cast<float>(nextNode->x - EnemyCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = MoveSpeed / distance;
				EnemyCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool Enemy::IsWall(int x, int y)
{
	//マップの範囲外は壁とみなす
	if (x < 1 || x >= Game::MapChipWidth || y < 1 || y >= Game::MapChipHeight)
	{
		return true;
	}

	//MapDataの変数１を返す)
	return Game::MapData[y][x] == 1;
	//return Game::MapData[x][y] == 1;
}

int Enemy::CalculateHeuristic(int x1, int y1, int x2, int y2)
{
	//マンハッタン距離を計算するヘリスティック関数
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//ユークリッド距離を計算するヘリステック関数
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}


std::vector<Node*> Enemy::AStar(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;//移動コストの定義

	std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> openList;//オープンリストを作成する。ノードのポインタを昇順に格納する
	std::vector<Node*> closedList;//クローズリストを作成する。ノードのポインタを格納する。

	Node* startNode = new Node(startX, startY, 0, 0, nullptr);//スタートノードを作成する。
	
	openList.push(startNode);//スタートノードをオープンリストに追加する。push -> openList(kyu-)

	while (!openList.empty())//オープンリストが空でない間、探索を続ける。
	{
		Node* currentNode = openList.top();//オープンリスト空コストが最小のノードを取得する
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)//最初のノードがゴールに到達したかチェックする
		{
			std::vector<Node*> path;//ゴールに到達した場合パスを構築する。
			while (currentNode != nullptr) 
			{
				// ゴールからスタートまでのパスを逆順にパスベクターに追加する
				{
					path.push_back(currentNode);
					currentNode = currentNode->parent;
				}
			}
			std::reverse(path.begin(), path.end());// パスを正しい順序に並び替える
			return path; // パスを返す
		}
		
		closedList.push_back(currentNode);// 現在のノードをクローズドリストに追加する

		
		//// 4方向の移動を試す
		//for (int dy = -1; dy <= 1; ++dy += 2)
		//{
		//	for (int dx = -1; dx <= 1; ++dx)
		//	{
		//		if (dx == 0 && dy == 0) continue;
			
		

		// 8方向の移動を試す
		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dx == 0 && dy == 0) continue;//現在の位置はスキップする

				// 次の移動先の座標を計算する
				int nextX = currentNode->x + dx;
				int nextY = currentNode->y + dy;

				if (!IsWall(nextX, nextY))//次の座標が壁でない場合
				{
					//次のノードを作成する
					Node* nextNode = new Node(nextX, nextY, currentNode->g + moveCost, CalculateHeuristic(nextX, nextY, goalX, goalY), currentNode);

					// クローズドリストにノードが含まれていない場合、オープンリストに追加する
					if (std::find_if(closedList.begin(), closedList.end(), [&](const Node* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//ゴールに到達できない場合はNULLを返す
	return std::vector<Node*>(NULL);
}



