#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "../Game.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyTwo.h"
#include "../Feed/PowerFeed.h"
#include "../Enemy/EnemyThree.h"
#include "../Scene/SceneManager.h"

EnemyThree::EnemyThree() :
	EnemyThreeCoordinate_Y		(EnemyThreeData::Pos_Y),						//敵の＜Y座標＞初期化
	EnemyThreeCoordinate_X		(EnemyThreeData::Pos_X),						//敵の＜X座標＞初期化
	ThreeMoveSpeed				(EnemyThreeData::moveSpeed),					//敵の＜速度＞初期化
	ThreeHitDamePos_X			(EnemyThreeData::HitDamagedHandlePos_X),		//画像ハンドル＜HitDamegeHandle＞の＜X座標＞初期化
	ThreeHitDamePos_Y			(EnemyThreeData::HitDamagedHandlePos_Y),		//画像ハンドル＜HitDamegeHandle＞の＜Y座標＞初期化
	ThreeHitDameTime			(EnemyThreeData::AfterTakingDamegeTime),		//プレイヤーと敵があたった際の＜演出時間＞初期化
	ThreeHitPointFlash			(EnemyThreeData::FlashPoint),					//画像ハンドル＜HitDamegeHandle＞の＜フラッシュ演出＞初期化
	ThreeisGameOver				(false),										//ゲームオーバーを判定するための＜フラグ＞初期化
	ThreeBUF					(false),										//バフフラグ
	ThreeHitDamegeGraphHandle	(LoadGraph("img/Damage.png")),					//HitDamegeHandle＜グラフハンドル＞の初期化
	ThreeEnemyGraphHandle		(LoadGraph("img/whitebear.png")),				//m_enemyBlinkyHandle＜グラフハンドル＞の初期化
	ThreeGameOverGraphHandle	(LoadGraph("img/GAMEOVERTEXT.png")),			//m_GameOverHandle＜グラフハンドル＞の初期化
	ThreeBUFEnemyHandle			(LoadGraph("img/whitebearBUF.png")),			//バフ状態の敵＜グラフハンドル＞の初期化
	ThreeDameSoundHandle		(LoadSoundMem("img/Dameg.mp3")),				//DameSoundHandle＜サウンドハンドル＞の初期化
	ThreePowerFeedBUFTime		(EnemyThreeData::BUFTime)						//プレイヤーがパワー餌を取得した際のバフ初期化
{
}

EnemyThree::~EnemyThree()
{
	DeleteGraph					(ThreeEnemyGraphHandle);
	DeleteGraph					(ThreeGameOverGraphHandle);
	DeleteGraph					(ThreeHitDamegeGraphHandle);
	DeleteSoundMem				(ThreeDameSoundHandle);
}

void EnemyThree::Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	EnemyThreeCoordinate_Y		= EnemyThreeData::Pos_Y;
	EnemyThreeCoordinate_X		= EnemyThreeData::Pos_X;
	ThreeMoveSpeed				= EnemyThreeData::moveSpeed;
	ThreeHitDamePos_X			= EnemyThreeData::HitDamagedHandlePos_X;
	ThreeHitDamePos_Y			= EnemyThreeData::HitDamagedHandlePos_Y;
	ThreeHitPointFlash			= EnemyThreeData::FlashPoint;
	ThreeisGameOver				= false;
	ThreeBUF					= false;
	ThreeHitDamegeGraphHandle	= LoadGraph		("img/Damage.png");
	ThreeEnemyGraphHandle		= LoadGraph		("img/panda.png");
	ThreeGameOverGraphHandle	= LoadGraph		("img/GAMEOVERTEXT.png");
	ThreeBUFEnemyHandle			= LoadGraph		("img/BUFpanda.png");
	ThreeDameSoundHandle		= LoadSoundMem	("sound/Dameg.mp3");
}

void EnemyThree::Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		ThreeBUF = true;
	}
	//敵の処理
	if (player.PlayerPos_X >= EnemyThreeCoordinate_X + 1 || player.PlayerPos_X <= EnemyThreeCoordinate_X - 1 || player.PlayerPos_Y >= EnemyThreeCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyThreeCoordinate_Y - 1) //敵の座用より外側にいたときの処理
		if (player.PlayerPos_X >= EnemyThreeCoordinate_X + 1 || player.PlayerPos_X <= EnemyThreeCoordinate_X - 1 || player.PlayerPos_Y >= EnemyThreeCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyThreeCoordinate_Y - 1) //敵の座用より外側にいたときの処理
		{
			if (ThreeBUF == true)
			{
				ThreePowerFeedBUFTime--;

				if (ThreeBUF == true)
				{
					if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
					{
						ThreePowerFeedBUFTime = 30;
					}
				}

				//値が10になったら０にする
				if (ThreePowerFeedBUFTime == 0)
				{
					ThreePowerFeedBUFTime = 60;
					ThreeBUF = false;
				}
			}


			if (player.ClearManager >= 110 && ThreeBUF == false)
			{
				MoveTowardsPlayerThree(player); //A*アルゴリズムを使用したプレイヤーの追跡
			}

			if (player.ClearManager != 244)
			{

				if (player.PlayerPos_X >= EnemyThreeCoordinate_X && player.PlayerPos_X <= EnemyThreeCoordinate_X) //当たり判定＜Ｘ座標＞
				{
					if (player.PlayerPos_Y >= EnemyThreeCoordinate_Y && player.PlayerPos_Y <= EnemyThreeCoordinate_Y) //当たり判定＜Ｘ座標＞
					{
						ThreeHitDameTime = 10; //当たり判定を通過した際にHitDameTimeに値ー＞10入る
						player.PlayerResidue -= 1; //プレイヤーの残機を一つ減らす

						if (player.PlayerResidue == 2) //プレイヤーの残機が２個になったとき
						{
							/*敵の座標とプレイヤーの座標を初期値に戻す*/
							player.PlayerPos_X = EnemyThreeData::PlayerPosReset_X;
							player.PlayerPos_Y = EnemyThreeData::PlayerPosReset_Y;

							EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
							EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;

							enemy.EnemyCoordinate_X = EnemyData::Pos_X;
							enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

							enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;
							enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;

						}

						if (player.PlayerResidue == 1) //プレイヤーの残機が1個になったとき
						{
							/*敵の座標とプレイヤーの座標を初期値に戻す*/
							player.PlayerPos_X = EnemyThreeData::PlayerPosReset_X;
							player.PlayerPos_Y = EnemyThreeData::PlayerPosReset_Y;

							EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
							EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;

							enemy.EnemyCoordinate_X = EnemyData::Pos_X;
							enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

							enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;
							enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;


						}
						if (player.PlayerResidue == 0) //プレイヤーの残機が0個になったとき
						{
							ThreeisGameOver = true; //ゲームオーバー用のフラグにtrueを入れる
						}

					}

				}
			}

		}

	//敵とプレイヤーがあたった時のフラッシュ更新
	if (ThreeHitDameTime > 0)
	{
		// 時間を減らす
		ThreeHitDameTime--;
		//文字点滅の値を追加していく
		ThreeHitPointFlash++;
		//値が10になったら０にする
		if (ThreeHitPointFlash == 20)
		{
			ThreeHitPointFlash = 0;
		}

		// 10秒経過した場合の処理
		if (ThreeHitDameTime >= 0)
		{
			// ここに10秒経過後の処理を追加する
			if (ThreeHitDamePos_X <= 0 && ThreeHitDamePos_X >= 60 && ThreeHitDamePos_Y <= 0 && ThreeHitDamePos_X >= 60)
			{
				ThreeHitDamePos_X += 10;
				ThreeHitDamePos_Y += 10;
			}
			if (ThreeHitDamePos_X >= 60 && ThreeHitDamePos_Y >= 60)
			{
				ThreeHitDamePos_X -= 10;
				ThreeHitDamePos_Y -= 10;
			}
		}
	}

	if (ThreeisGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void EnemyThree::Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	if (ThreeHitDameTime > 0)
	{
		// 時間を減らす
		ThreeHitDameTime--;

		// 10秒経過した場合の処理
		if (ThreeHitDameTime >= 0)
		{
			if (ThreeHitPointFlash == 1 || ThreeHitPointFlash == 2 || ThreeHitPointFlash == 4 || ThreeHitPointFlash == 5 || ThreeHitPointFlash == 8 || ThreeHitPointFlash == 10)
			{
				DrawGraph(ThreeHitDamePos_X, ThreeHitDamePos_Y, ThreeHitDamegeGraphHandle, true);
				PlaySoundMem(ThreeDameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}


	if (ThreeBUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG
	}

	if (ThreeBUF == false)
	{
		DrawGraph(EnemyThreeCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyThreeCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, ThreeEnemyGraphHandle, true);
	}

	if (player.ClearManager <= 120 || ThreeBUF == true)
	{
		DrawGraph(EnemyThreeCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyThreeCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, ThreeBUFEnemyHandle, true);
	}
}

void EnemyThree::Final()
{
	DeleteGraph(ThreeEnemyGraphHandle);
	DeleteGraph(ThreeBUFEnemyHandle);
	DeleteGraph(ThreeHitDamegeGraphHandle);
	DeleteGraph(ThreeGameOverGraphHandle);
	DeleteSoundMem(ThreeDameSoundHandle);
}

void EnemyThree::MoveTowardsPlayerThree(Player& player)
{
	/*std::vector<NodeThree*> path = AStarThree(EnemyThreeCoordinate_X, EnemyThreeCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeThree* nextNode = path[1];
		if (!IsWallThree(nextNode->x, nextNode->y))
		{
			EnemyThreeCoordinate_X = nextNode->x;
			EnemyThreeCoordinate_Y = nextNode->y;
		}
	}*/

	std::vector<NodeThree*> path = AStarThree(EnemyThreeCoordinate_X, EnemyThreeCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeThree* nextNode = path[1];
		if (!IsWallThree(nextNode->x, nextNode->y))
		{
			// 移動速度を考慮して位置を更新
			float deltaX = static_cast<float>(nextNode->x - EnemyThreeCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyThreeCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = ThreeMoveSpeed / distance;
				EnemyThreeCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyThreeCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool EnemyThree::IsWallThree(int x, int y)
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

int EnemyThree::CalculateHeuristicThree(int x1, int y1, int x2, int y2)
{
	//マンハッタン距離を計算するヘリスティック関数
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//ユークリッド距離を計算するヘリステック関数
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}

std::vector<NodeThree*> EnemyThree::AStarThree(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;

	std::priority_queue<NodeThree*, std::vector<NodeThree*>, std::greater<NodeThree*>> openList;
	std::vector<NodeThree*> closedList;

	NodeThree* startNode = new NodeThree(startX, startY, 0, 0, nullptr);

	openList.push(startNode);

	while (!openList.empty())
	{
		NodeThree* currentNode = openList.top();
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)
		{
			std::vector<NodeThree*> path;
			while (currentNode != nullptr)
			{
				path.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		closedList.push_back(currentNode);

		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dx == 0 && dy == 0) continue;


				int nextX = currentNode->x + dx;
				int nextY = currentNode->y + dy;

				if (!IsWallThree(nextX, nextY))
				{
					NodeThree* nextNode = new NodeThree(nextX, nextY, currentNode->g + moveCost, CalculateHeuristicThree(nextX, nextY, goalX, goalY), currentNode);

					if (std::find_if(closedList.begin(), closedList.end(), [&](const NodeThree* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//ゴールに到達できない場合はNULLを返す
	return std::vector<NodeThree*>(NULL);
}


