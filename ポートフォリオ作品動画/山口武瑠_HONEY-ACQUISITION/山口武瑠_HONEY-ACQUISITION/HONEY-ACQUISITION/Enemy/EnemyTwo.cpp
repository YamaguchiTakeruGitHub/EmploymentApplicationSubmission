#include <queue>
#include <cmath>
#include <vector>
#include <iostream>
#include "../Game.h"
#include "../Player/Player.h"
#include "../Feed/PowerFeed.h"
#include "../Enemy/EnemyTwo.h"
#include "../Enemy/EnemyThree.h"
#include "../Scene/SceneManager.h"

EnemyTwo::EnemyTwo():
	EnemyTwoCoordinate_Y		(EnemyTwoData::Pos_Y),						//敵の＜Y座標＞初期化
	EnemyTwoCoordinate_X		(EnemyTwoData::Pos_X),						//敵の＜X座標＞初期化
	TwoMoveSpeed				(EnemyTwoData::moveSpeed),					//敵の＜速度＞初期化
	TwoHitDamePos_X				(EnemyTwoData::HitDamagedHandlePos_X),		//画像ハンドル＜HitDamegeHandle＞の＜X座標＞初期化
	TwoHitDamePos_Y				(EnemyTwoData::HitDamagedHandlePos_Y),		//画像ハンドル＜HitDamegeHandle＞の＜Y座標＞初期化
	TwoHitDameTime				(EnemyTwoData::AfterTakingDamegeTime),		//プレイヤーと敵があたった際の＜演出時間＞初期化
	TwoHitPointFlash			(EnemyTwoData::FlashPoint),				//画像ハンドル＜HitDamegeHandle＞の＜フラッシュ演出＞初期化
	TwoisGameOver				(false),								//ゲームオーバーを判定するための＜フラグ＞初期化
	TwoBUF						(false),								//バフフラグ
	TwoHitDamegeGraphHandle		(LoadGraph("img/Damage.png")),			//HitDamegeHandle＜グラフハンドル＞の初期化
	TwoEnemyGraphHandle			(LoadGraph("img/whitebear.png")),		//m_enemyBlinkyHandle＜グラフハンドル＞の初期化
	TwoGameOverGraphHandle		(LoadGraph("img/GAMEOVERTEXT.png")),	//m_GameOverHandle＜グラフハンドル＞の初期化
	TwoBUFEnemyHandle			(LoadGraph("img/whitebearBUF.png")),	//バフ状態の敵＜グラフハンドル＞の初期化
	TwoDameSoundHandle			(LoadSoundMem("img/Dameg.mp3")),		//DameSoundHandle＜サウンドハンドル＞の初期化
	TwoPowerFeedBUFTime			(EnemyTwoData::BUFTime)					//プレイヤーがパワー餌を取得した際のバフ初期化
{
}

EnemyTwo::~EnemyTwo()
{
	DeleteGraph					(TwoEnemyGraphHandle);
	DeleteGraph					(TwoGameOverGraphHandle);
	DeleteGraph					(TwoHitDamegeGraphHandle);
	DeleteSoundMem				(TwoDameSoundHandle);
}

void EnemyTwo::Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	EnemyTwoCoordinate_Y		= EnemyTwoData::Pos_Y;
	EnemyTwoCoordinate_X		= EnemyTwoData::Pos_X;
	TwoMoveSpeed				= EnemyTwoData::moveSpeed;
	TwoHitDamePos_X				= EnemyTwoData::HitDamagedHandlePos_X;
	TwoHitDamePos_Y				= EnemyTwoData::HitDamagedHandlePos_Y;
	TwoHitPointFlash			= EnemyTwoData::FlashPoint;
	TwoisGameOver				= false;
	TwoBUF						= false;
	TwoHitDamegeGraphHandle		= LoadGraph		("img/Damage.png");
	TwoEnemyGraphHandle			= LoadGraph		("img/whitebear.png");
	TwoGameOverGraphHandle		= LoadGraph		("img/GAMEOVERTEXT.png");
	TwoBUFEnemyHandle			= LoadGraph		("img/whitebearBUF.png");
	TwoDameSoundHandle			= LoadSoundMem	("sound/Dameg.mp3");
}

void EnemyTwo::Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		TwoBUF = true;
	}
	//敵の処理
	if (player.PlayerPos_X >= EnemyTwoCoordinate_X + 1 || player.PlayerPos_X <= EnemyTwoCoordinate_X - 1 || player.PlayerPos_Y >= EnemyTwoCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyTwoCoordinate_Y - 1) //敵の座用より外側にいたときの処理
	if (player.PlayerPos_X >= EnemyTwoCoordinate_X + 1 || player.PlayerPos_X <= EnemyTwoCoordinate_X - 1 || player.PlayerPos_Y >= EnemyTwoCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyTwoCoordinate_Y - 1) //敵の座用より外側にいたときの処理
	{
		if (TwoBUF == true)
		{
			TwoPowerFeedBUFTime--;
			
			if (TwoBUF == true)
			{
				if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
				{
					TwoPowerFeedBUFTime = 60;
				}
			}
			
			//値が10になったら０にする
			if (TwoPowerFeedBUFTime == 0)
			{
				TwoPowerFeedBUFTime = 60;
				TwoBUF = false;
			}
		}
		

		if (player.ClearManager >= 110 && TwoBUF == false)
		{
			MoveTowardsPlayerTwo(player); //A*アルゴリズムを使用したプレイヤーの追跡
		}

		if (player.ClearManager != 244)
		{

			if (player.PlayerPos_X >= EnemyTwoCoordinate_X && player.PlayerPos_X <= EnemyTwoCoordinate_X) //当たり判定＜Ｘ座標＞
			{
				if (player.PlayerPos_Y >= EnemyTwoCoordinate_Y && player.PlayerPos_Y <= EnemyTwoCoordinate_Y) //当たり判定＜Ｘ座標＞
				{
					TwoHitDameTime = 10; //当たり判定を通過した際にHitDameTimeに値ー＞10入る
					player.PlayerResidue -= 1; //プレイヤーの残機を一つ減らす

					if (player.PlayerResidue == 2) //プレイヤーの残機が２個になったとき
					{
						/*敵の座標とプレイヤーの座標を初期値に戻す*/
						player.PlayerPos_X = EnemyTwoData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyTwoData::PlayerPosReset_Y;

						EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemy.EnemyCoordinate_X = EnemyData::Pos_X;
						enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;


					}

					if (player.PlayerResidue == 1) //プレイヤーの残機が1個になったとき
					{
						/*敵の座標とプレイヤーの座標を初期値に戻す*/
						player.PlayerPos_X = EnemyTwoData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyTwoData::PlayerPosReset_Y;

						EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemy.EnemyCoordinate_X = EnemyData::Pos_X;
						enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;


					}
					if (player.PlayerResidue == 0) //プレイヤーの残機が0個になったとき
					{
						TwoisGameOver = true; //ゲームオーバー用のフラグにtrueを入れる
					}

				}

			}
		}

	}

	//敵とプレイヤーがあたった時のフラッシュ更新
	if (TwoHitDameTime > 0)
	{
		// 時間を減らす
		TwoHitDameTime--;
		//文字点滅の値を追加していく
		TwoHitPointFlash++;
		//値が10になったら０にする
		if (TwoHitPointFlash == 20)
		{
			TwoHitPointFlash = 0;
		}

		// 10秒経過した場合の処理
		if (TwoHitDameTime >= 0)
		{
			// ここに10秒経過後の処理を追加する
			if (TwoHitDamePos_X <= 0 && TwoHitDamePos_X >= 60 && TwoHitDamePos_Y <= 0 && TwoHitDamePos_X >= 60)
			{
				TwoHitDamePos_X += 10;
				TwoHitDamePos_Y += 10;
			}
			if (TwoHitDamePos_X >= 60 && TwoHitDamePos_Y >= 60)
			{
				TwoHitDamePos_X -= 10;
				TwoHitDamePos_Y -= 10;
			}
		}
	}

	if (TwoisGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void EnemyTwo::Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	if (TwoHitDameTime > 0)
	{
		// 時間を減らす
		TwoHitDameTime--;

		// 10秒経過した場合の処理
		if (TwoHitDameTime >= 0)
		{
			if (TwoHitPointFlash == 1 || TwoHitPointFlash == 2 || TwoHitPointFlash == 4 || TwoHitPointFlash == 5 || TwoHitPointFlash == 8 || TwoHitPointFlash == 10)
			{
				DrawGraph(TwoHitDamePos_X, TwoHitDamePos_Y, TwoHitDamegeGraphHandle, true);
				PlaySoundMem(TwoDameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}


	if (TwoBUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG
	}

	if (TwoBUF == false)
	{
		DrawGraph(EnemyTwoCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyTwoCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, TwoEnemyGraphHandle, true);
	}
	
	if (player.ClearManager <= 110 || TwoBUF == true)
	{
		DrawGraph(EnemyTwoCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyTwoCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, TwoBUFEnemyHandle, true);
	}
}

void EnemyTwo::Final()
{
	DeleteGraph(TwoBUFEnemyHandle);
	DeleteGraph(TwoEnemyGraphHandle);
	DeleteGraph(TwoHitDamegeGraphHandle);
	DeleteGraph(TwoGameOverGraphHandle);
	DeleteSoundMem(TwoDameSoundHandle);
}

void EnemyTwo::MoveTowardsPlayerTwo(Player& player)
{
	/*std::vector<NodeTwo*> path = AStarTwo(EnemyTwoCoordinate_X, EnemyTwoCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeTwo* nextNode = path[1];
		if (!IsWallTwo(nextNode->x, nextNode->y))
		{
			EnemyTwoCoordinate_X = nextNode->x;
			EnemyTwoCoordinate_Y = nextNode->y;
		}
	}*/

	std::vector<NodeTwo*> path = AStarTwo(EnemyTwoCoordinate_X, EnemyTwoCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeTwo* nextNode = path[1];
		if (!IsWallTwo(nextNode->x, nextNode->y))
		{
			// 移動速度を考慮して位置を更新
			float deltaX = static_cast<float>(nextNode->x - EnemyTwoCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyTwoCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = TwoMoveSpeed / distance;
				EnemyTwoCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyTwoCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool EnemyTwo::IsWallTwo(int x, int y)
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

int EnemyTwo::CalculateHeuristicTwo(int x1, int y1, int x2, int y2)
{
	//マンハッタン距離を計算するヘリスティック関数
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//ユークリッド距離を計算するヘリステック関数
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}

std::vector<NodeTwo*> EnemyTwo::AStarTwo(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;

	std::priority_queue<NodeTwo*, std::vector<NodeTwo*>, std::greater<NodeTwo*>> openList;
	std::vector<NodeTwo*> closedList;

	NodeTwo* startNode = new NodeTwo(startX, startY, 0, 0, nullptr);

	openList.push(startNode);

	while (!openList.empty())
	{
		NodeTwo* currentNode = openList.top();
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)
		{
			std::vector<NodeTwo*> path;
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

				if (!IsWallTwo(nextX, nextY))
				{
					NodeTwo* nextNode = new NodeTwo(nextX, nextY, currentNode->g + moveCost, CalculateHeuristicTwo(nextX, nextY, goalX, goalY), currentNode);

					if (std::find_if(closedList.begin(), closedList.end(), [&](const NodeTwo* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//ゴールに到達できない場合はNULLを返す
	return std::vector<NodeTwo*>(NULL);
}
