#include "Sound.h"
#include "DxLib.h"

Sound::Sound() :
	Se_Player_1(LoadSoundMem("SE_1_PlayerSE.mp3")),
	SePlayerMove(PlaySoundMem(Se_Player_1, DX_PLAYTYPE_LOOP))
{
}

Sound::~Sound()
{
}

void Sound::Init()
{
	Se_Player_1;
	SePlayerMove;
}

void Sound::Update()
{
}

void Sound::Draw()
{
}

void Sound::Final()
{
}

void Sound::PlaySeMovePlayer_1()
{
	SePlayerMove;
	WaitTimer(5000);
}
