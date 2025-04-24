#pragma once
#include <string>

namespace TagCharacterObject
{
	static std::string PLAYER = "Player";//プレイヤータグ
	static std::string ENEMY_AILEVEL_LOW = "EnemyAiLevelLow";//低レベルAIの敵
	static std::string ENEMY_AILEVEL_MIDDLE = "EnemyAiLevelMiddle";//中レベルAIの敵
	static std::string ENEMY_AILEVEL_HIGH = "EnemyAiLevelHigh";//高レベルAIの敵
}

namespace TagMapObject
{
	static std::string WALL = "Wall";//壁
	static std::string FLOOR = "Floor";//床
	static std::string CEILING = "Seiling";//天井
}

namespace TagCameraObject
{
	static std::string CONTROL = "cameraControl";//コントロールするカメラ
}

namespace TagFontObject
{
	static std::string TestLetter = "testletter!";
}