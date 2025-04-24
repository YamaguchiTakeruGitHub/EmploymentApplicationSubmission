#include "SceneGame.h"
#include "../../Object/GameTag.h"



/*仮なのであとで移行*/
namespace
{
	//最大当たり判定ポリゴン数
	constexpr int kMaxColHitPolyNum = 2000;
	//壁押し出し処理の最大試行回数
	constexpr int kMaxColHitTryNum = 16;
	//壁押し出し時にスライドさせる距離
	constexpr float kColHitSlideLength = 1.0f;
	//移動したかを判断するための変数
	constexpr float kMove = 0.01f;
	//壁ポリゴンか床ポリゴンかを判断するための変数
	constexpr float kWallPolyBorder = 0.4f;
	//壁ポリゴンと判断するための高さ変数
	constexpr float kWallPolyHeight = 5.0f;

	//死んでからの時間
	constexpr int kEnableTimeCount = 10;

	//頭の高さを設定
	constexpr float kHeadHeight = 40.0f;
	//
}


void SceneGame::PlayerControlCamera()
{
	/*カメラの角度を考慮した座標に変換*/
	m_player->SetConversionHorizontalAngle(m_camera->GetHAngle());
	m_player->SetConversionCosParam(m_camera->GetCosParam());
	m_player->SetConversionSinParam(m_camera->GetSinParam());
	m_player->Update();

	m_camera->SetTag(TagCameraObject::CONTROL);

	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->SetTarget(m_player->GetPosition());
	m_camera->SetLookOnTarget(m_enemyFox->GetPosition());

	//m_camera->SetLookOnTarget(m_enemyManager->GetPosition());

	m_camera->Update();
}

SceneGame::SceneGame()
	: m_isLoading(false)//ロード中かどうか
{
	m_player = std::make_shared<Player>();		//プレイヤー
	m_enemyFox = std::make_shared<EnemyFox>();	//狐の敵

	m_enemyManager = std::make_shared<EnemyManager>();

	m_camera = std::make_shared<Camera>();//カメラ

	m_tutorialMap = std::make_shared<TutorialMap>();//チュートリアルマップ

	m_menuSystem = std::make_shared<MenuSystem>();//メニュ全般

	m_command = std::make_shared<Command>();//コマンド

	m_mathLib = std::make_shared<MathLib>();//数学関数

	/*テスト用変数*/
	boxPos = VGet(-400.0f, 0.0f, 0.0f);
	boxSize = VGet(60.0f, 60.0f, 60.0f);

	/*ポリゴンテスト*/
	m_polygon[0].vertex[0] = VGet(100, 0, 0);
	m_polygon[0].vertex[1] = VGet(300, 100, 0);
	m_polygon[0].vertex[2] = VGet(400, 0, 0);

	m_polygon[1].vertex[0] = VGet(0, 0, 0);
	m_polygon[1].vertex[1] = VGet(300, 0, 300);
	m_polygon[1].vertex[2] = VGet(400, 0, 0);

	m_polygon[2].vertex[0] = VGet(0, 20, 0);
	m_polygon[2].vertex[1] = VGet(300, 0, 300);
	m_polygon[2].vertex[2] = VGet(400, 0, 0);

}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_Idm->Init();

	m_player->Init();
	m_enemyFox->Init();


	m_camera->Init();
	m_tutorialMap->Init();

	m_menuSystem->Init();
	m_command->Init();

	m_isLoading = true;//必ず各クラスの後につける

	/*仮ライト*/
	lightHandle = CreateDirLightHandle(VGet(0.0f, 200.0f, 0.0f));

}

void SceneGame::Update()
{
	m_Idm->Update();

	if (m_isLoading)
	{
		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		/*仮ライト*/
		SetLightDirectionHandle(lightHandle, VGet(0, 1, 0));
		SetLightPositionHandle(lightHandle, VGet(0, 200, 0));
	
		if (!m_menuSystem->GetIsMenuOpen())
		{
			m_command->Update();

			m_player->SetIsAttackCheck(m_command->GetIsAttack());//攻撃コマンドが反応しているか

			m_tutorialMap->Update();
			PlayerControlCamera();//プレイヤーの更新と操作カメラの更新

			m_enemyFox->SetTargetPosition(m_player->GetPosition());
			m_enemyFox->Update();


			/*攻撃処理*/
			if (VSize(VSub(m_enemyFox->GetPosition(), m_player->GetAttackPosition())) <= m_enemyFox->GetRadius() + m_player->GetAttackRadius())
			{
				if (m_command->GetIsAttack() == true)
				{
					m_enemyFox->SetIsTakeDamage(m_player->GetAttackValue());
				}
			}


			m_enemyManager->SetTargetPosition(m_player->GetPosition());
			m_enemyManager->Update();
			
		}
		m_menuSystem->Update();
	}
}

void SceneGame::Draw()
{
	if (m_isLoading)
	{
		DrawString(0, 0, "NowLoading...", 0xffffff);

		// ロードの進行状況を計算
		int totalLoadTasks = GetASyncLoadNum(); // 総ロードタスク数を取得する関数（仮定）
		int remainingLoadTasks = GetASyncLoadNum(); // 残りのロードタスク数を取得
		float progress = 1.0f - (static_cast<float>(remainingLoadTasks) / totalLoadTasks);

		// バーの描画
		int barWidth = 200; // バーの幅
		int barHeight = 20; // バーの高さ
		int barX = 100; // バーのX座標
		int barY = 50; // バーのY座標
		DrawBox(barX, barY, barX + static_cast<int>(barWidth * progress), barY + barHeight, 0x00ff00, TRUE); // プログレスバー
		DrawBox(barX, barY, barX + barWidth, barY + barHeight, 0xffffff, false);

		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{

		m_tutorialMap->Draw();
#ifdef _DEBUG
		/*グリッドのデバッグ表示*/
		/*m_tutorialMap->DrawGrid(1000, 100, 0.0f);
		m_tutorialMap->DrawGrid(1000, 100, 100.0f);*/
		m_tutorialMap->DrawBox(boxPos, boxSize);


#endif // _DEBUG

		m_player->Draw();
		m_enemyFox->Draw();
		m_enemyManager->Draw();

		m_camera->Draw();


		SavePoint();

		IsTestPhsycse();
		IsTestPhsycseEnemy();
		CapsuleHitResolve();
		
		m_command->Draw();
		m_menuSystem->Draw();
	}
}

void SceneGame::Final()
{
	m_tutorialMap->Final();
	m_player->Final();
	m_enemyFox->Final();
	m_enemyManager->Final();
	
	m_camera->Final();
	m_menuSystem->Final();
	m_command->Final();

	DeleteLightHandle(lightHandle);
}


void SceneGame::IsTestPhsycse()
{
	VECTOR top = VAdd(m_player->GetPosition(), VGet(0, m_player->GetCapsuleHeight(), 0));
	VECTOR bottom = VAdd(m_player->GetPosition(), VGet(0, m_player->GetRadius(), 0));

	DrawLine3D(top, bottom, 0xff0000);
	DrawLine3D(top, VAdd(top, VGet(0, m_player->GetRadius(), 0)), 0xfffff);
	//DrawLine3D(bottom, VAdd(bottom, VGet(0, m_player->GetRadius(), 0)), 0xfffff);

	m_hitDim = MV1CollCheck_Capsule(m_tutorialMap->GetModelHandle(), -1, top, bottom, m_player->GetRadius());

	bool isGrounded = false;

	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		//DrawTriangle3D(m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2], 0xffff00, true);

		if (HitCheck_Capsule_Triangle(top, bottom, m_player->GetRadius(), m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]))
		{
			VECTOR normal = m_hitDim.Dim[i].Normal;
			VECTOR center = m_mathLib->PolygonCenter(m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]);
			VECTOR move = VGet(0, 0, 0);
			VECTOR slide = VGet(0, 0, 0);

			// 平面
			if (normal.y >= 1.0f)
			{
				m_player->SetPosition(VAdd(m_player->GetPosition(), VGet(0, normal.y - 1.0f, 0)));
				isGrounded = true;
			}

			// スロープ
			if (normal.y < 1.0f && normal.y >= 0.6f)
			{
				VECTOR slideDirection = VGet(normal.x, 0, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 0.5f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 0.5f);
				m_player->SetPosition(VAdd(m_player->GetPosition(), pushOut));

				isGrounded = true;
			}

			//// スロープ
			//if (normal.y < 1.0f && normal.y >= 0.6f)
			//{
			//	VECTOR slideDirection = VGet(normal.x, 0.3f, normal.z);
			//	slideDirection = VNorm(slideDirection);
			//	slide = VScale(slideDirection, kColHitSlideLength * 0.3f);

			//	VECTOR pushOut = VScale(normal, kColHitSlideLength * 0.3f);
			//	m_player->SetPosition(VAdd(m_player->GetPosition(), pushOut));

			//	isGrounded = true;
			//}

			// 壁
			if (normal.y <= 0.2f && normal.y >= 0.0f)
			{
				VECTOR slideDirection = VGet(normal.x, 0, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 1.0f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				m_player->SetPosition(VAdd(m_player->GetPosition(), pushOut));

				
			}

			//斜めの壁
			if (normal.y <= 0.6f && normal.y >= 2.0f)
			{
				// 壁に沿って落下
				VECTOR gravity = VGet(0, -1.0f, 0);
				VECTOR slideAlongWall = VCross(normal, gravity);
				slideAlongWall = VNorm(slideAlongWall);
				slideAlongWall = VScale(slideAlongWall, kColHitSlideLength * 1.0f);
				m_player->SetPosition(VAdd(m_player->GetPosition(), slideAlongWall));
			}




			// 天井
			if (normal.y < 0.0f)
			{
				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				m_player->SetPosition(VAdd(m_player->GetPosition(), pushOut));
			}
		}
	}

	if (!isGrounded)
	{
		m_player->SetIsGround(false);
	}
	else
	{
		m_player->SetIsGround(true);
	}

}

void SceneGame::IsTestPhsycseEnemy()
{
	// EnemyFoxの当たり判定

	//VECTOR enemyTop = VAdd(m_enemyManager->GetPosition(), VGet(0, m_enemyManager->GetCapsuleHeight(), 0));
	//VECTOR enemyBottom = VAdd(m_enemyManager->GetPosition(), VGet(0, m_enemyManager->GetCapsuleRadius(), 0));
	//
	//DrawLine3D(enemyTop, enemyBottom, 0x00ff00);
	//DrawLine3D(enemyTop, VAdd(enemyTop, VGet(0, m_enemyManager->GetCapsuleRadius(), 0)), 0xfffff);

	//m_hitDim = MV1CollCheck_Capsule(m_tutorialMap->GetModelHandle(), -1, enemyTop, enemyBottom, m_enemyManager->GetCapsuleRadius());

	//for (int i = 0; i < m_hitDim.HitNum; i++)
	//{
	//	if (HitCheck_Capsule_Triangle(enemyTop, enemyBottom, m_enemyManager->GetCapsuleRadius(), m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]))
	//	{
	//		VECTOR normal = m_hitDim.Dim[i].Normal;
	//		VECTOR center = m_mathLib->PolygonCenter(m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]);
	//		VECTOR move = VGet(0, 0, 0);
	//		VECTOR slide = VGet(0, 0, 0);

	//		if (normal.y >= 1.0f)
	//		{
	//			m_enemyManager->SetPosition((VAdd(m_enemyManager->GetPosition(), VGet(0, normal.y - 1.0f, 0))));
	//			m_enemyManager->SetIsGround(true);
	//		}

	//		if (normal.y < 1.0f && normal.y >= 0.6f)
	//		{
	//			VECTOR slideDirection = VGet(normal.x, 1.0f, normal.z);
	//			slideDirection = VNorm(slideDirection);
	//			slide = VScale(slideDirection, kColHitSlideLength * 0.5f);

	//			VECTOR pushOut = VScale(normal, kColHitSlideLength * 0.5f);
	//			m_enemyManager->SetPosition(VAdd(m_enemyManager->GetPosition(), pushOut));
	//			m_enemyManager->SetIsGround(true);
	//		}

	//		if (normal.y <= 0.2f && normal.y >= 0.0f)
	//		{
	//			VECTOR slideDirection = VGet(normal.x, 0, normal.z);
	//			slideDirection = VNorm(slideDirection);
	//			slide = VScale(slideDirection, kColHitSlideLength * 1.0f);

	//			VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
	//			m_enemyManager->SetPosition(VAdd(m_enemyManager->GetPosition(), pushOut));
	//		}

	//		if (normal.y <= 0.6f && normal.y >= 2.0f)
	//		{
	//			VECTOR gravity = VGet(0, -1.0f, 0);
	//			VECTOR slideAlongWall = VCross(normal, gravity);
	//			slideAlongWall = VNorm(slideAlongWall);
	//			slideAlongWall = VScale(slideAlongWall, kColHitSlideLength * 1.0f);
	//			m_enemyManager->SetPosition(VAdd(m_enemyManager->GetPosition(), slideAlongWall));
	//		}

	//		if (normal.y < 0.0f)
	//		{
	//			VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
	//			m_enemyManager->SetPosition(VAdd(m_enemyManager->GetPosition(), pushOut));
	//		}

	//		DrawFormatString(0, 200 + i * 20, 0xffffff, "enemy normal(%f,%f,%f)", normal.x, normal.y, normal.z);
	//	}
	//}

	/*単体*/

	VECTOR enemyTop = VAdd(m_enemyFox->GetPosition(), VGet(0, m_enemyFox->GetCapsuleHeight(), 0));
	VECTOR enemyBottom = VAdd(m_enemyFox->GetPosition(), VGet(0, m_enemyFox->GetRadius(), 0));

	DrawLine3D(enemyTop, enemyBottom, 0x00ff00);
	DrawLine3D(enemyTop, VAdd(enemyTop, VGet(0, m_enemyFox->GetRadius(), 0)), 0xfffff);

	m_hitDim = MV1CollCheck_Capsule(m_tutorialMap->GetModelHandle(), -1, enemyTop, enemyBottom, m_enemyFox->GetRadius());

	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		if (HitCheck_Capsule_Triangle(enemyTop, enemyBottom, m_enemyFox->GetRadius(), m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]))
		{
			VECTOR normal = m_hitDim.Dim[i].Normal;
			VECTOR center = m_mathLib->PolygonCenter(m_hitDim.Dim[i].Position[0], m_hitDim.Dim[i].Position[1], m_hitDim.Dim[i].Position[2]);
			VECTOR move = VGet(0, 0, 0);
			VECTOR slide = VGet(0, 0, 0);

			m_enemyFox->SetIsGround(true);


			if (normal.y >= 1.0f)
			{
				m_enemyFox->SetPosition(VAdd(m_enemyFox->GetPosition(), VGet(0, normal.y - 1.0f, 0)));
				m_enemyFox->SetIsGround(true);
			}

			if (normal.y < 1.0f && normal.y >= 0.6f)
			{
				VECTOR slideDirection = VGet(normal.x, 1.0f, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 0.5f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 0.5f);
				m_enemyFox->SetPosition(VAdd(m_enemyFox->GetPosition(), pushOut));
				m_enemyFox->SetIsGround(true);
			}

			if (normal.y <= 0.2f && normal.y >= 0.0f)
			{
				VECTOR slideDirection = VGet(normal.x, 0, normal.z);
				slideDirection = VNorm(slideDirection);
				slide = VScale(slideDirection, kColHitSlideLength * 1.0f);

				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				m_enemyFox->SetPosition(VAdd(m_enemyFox->GetPosition(), pushOut));
			

			}

			if (normal.y <= 0.6f && normal.y >= 2.0f)
			{
				VECTOR gravity = VGet(0, -1.0f, 0);
				VECTOR slideAlongWall = VCross(normal, gravity);
				slideAlongWall = VNorm(slideAlongWall);
				slideAlongWall = VScale(slideAlongWall, kColHitSlideLength * 1.0f);
				m_enemyFox->SetPosition(VAdd(m_enemyFox->GetPosition(), slideAlongWall));
			

			}

			if (normal.y < 0.0f)
			{
				VECTOR pushOut = VScale(normal, kColHitSlideLength * 1.0f);
				m_enemyFox->SetPosition(VAdd(m_enemyFox->GetPosition(), pushOut));
			}

			//DrawFormatString(0, 200 + i * 20, 0xffffff, "enemy normal(%f,%f,%f)", normal.x, normal.y, normal.z);
		}
		else
		{
			m_enemyFox->SetIsGround(false);
		}
	}
	
}

void SceneGame::CapsuleHitResolve()
{
	VECTOR segment1 = VGet(0, 0, 0);
	VECTOR segment2=VGet(0,0,0);

	segment1 = m_mathLib->Line_Segment_Point_VECTOR(m_player->GetPosition(), VAdd(m_player->GetPosition(), VGet(0, m_player->GetCapsuleHeight(), 0)), segment2);
	segment2 = m_mathLib->Line_Segment_Point_VECTOR(m_enemyFox->GetPosition(), VAdd(m_enemyFox->GetPosition(), VGet(0, m_enemyFox->GetCapsuleHeight(), 0)), segment1);
	//segment2 = m_mathLib->Line_Segment_Point_VECTOR(m_enemyManager->GetPosition(), VAdd(m_enemyManager->GetPosition(), VGet(0, m_enemyManager->GetCapsuleHeight(), 0)), segment1);



	VECTOR segmentLineToLine = VSub(segment1, segment2);

	if (VSize(segmentLineToLine) <= m_player->GetRadius() + m_enemyFox->GetRadius())
	{
		DrawLine3D(segment1, segment2, 0xff0000);
		VECTOR pushBack = VScale(VNorm(segmentLineToLine), m_player->GetRadius() + m_enemyFox->GetRadius() - VSize(segmentLineToLine));
		m_player->SetPosition(VAdd(m_player->GetPosition(), pushBack));

		VECTOR pushBack2 = VScale(VNorm(segmentLineToLine), m_player->GetRadius() + m_enemyFox->GetRadius() - VSize(segmentLineToLine));
		m_enemyFox->SetPosition(VSub(m_enemyFox->GetPosition(), pushBack2));
	}

	/*複数*/
	/*if (VSize(segmentLineToLine) <= m_player->GetRadius() + m_enemyManager->GetCapsuleRadius())
	{
		DrawLine3D(segment1, segment2, 0xff0000);
		VECTOR pushBack = VScale(VNorm(segmentLineToLine), m_player->GetRadius() + m_enemyManager->GetCapsuleRadius() - VSize(segmentLineToLine));
		m_player->SetPosition(VAdd(m_player->GetPosition(), pushBack));

		VECTOR pushBack2 = VScale(VNorm(segmentLineToLine), m_player->GetRadius() + m_enemyManager->GetCapsuleRadius() - VSize(segmentLineToLine));
		m_enemyManager->SetPosition(VSub(m_enemyManager->GetPosition(), pushBack2));
	}*/

}

void SceneGame::SavePoint()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) TestHiScore++;
	
	if (VSize(VSub(m_savePointPos, m_player->GetPosition())) <= m_savePointRadius + m_player->GetRadius())
	{
		m_command->SetIsSpecialCommands(true);

		DrawSphere3D(m_savePointPos, m_savePointRadius, 5, 0xff0000, 0xff0000, false);
		if (CheckHitKey(KEY_INPUT_A) != 0)
		{
			SaveGame();
		}
	}
	else
	{
		DrawSphere3D(m_savePointPos, m_savePointRadius, 5, 0xffffff, 0xffffff, false);
		m_command->SetIsSpecialCommands(false);
	}

}

void SceneGame::SaveGame()
{
	FILE* file;
	errno_t err = fopen_s(&file, "../Data/SaveData/SaveData1.dat", "wb");

	if (err != 0)
	{
#ifdef _DEBUG
		// ファイルオープンに失敗した場合のエラーメッセージ
		DrawFormatString(0, 40, 0xffffff, "Failed to open file for writing: %d", err);

#endif // _DEBUG

	}

	if (file)
	{
		size_t written = fwrite(&TestHiScore, sizeof(TestHiScore), 1, file);
		if (written != 1)
		{
#ifdef _DEBUG
			// 書き込みに失敗した場合のエラーメッセージ
			DrawFormatString(0, 40, 0xffffff, "Failed to write data to file: value:%d", written);

#endif // _DEBUG


		}
		fclose(file);
	}

}



//memo
//多分現状はカプセルの線に当たったら補正されるようになっているから、カプセルの半径も考慮した接触にしてあげる