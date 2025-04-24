#pragma once
#include <DxLib.h>
#include <string>

namespace KEY_BOARD
{
	static constexpr int KEY_BUFFER = 256;
}

class KeyBoard
{
private:
	char keys[KEY_BOARD::KEY_BUFFER] = { 0 };
	char oldKyes[KEY_BOARD::KEY_BUFFER] = { 0 };

public:

	void Update();

	bool IsPressed(int _key);

	bool IsTriggered(int _key);

};

