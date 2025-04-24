#pragma once
#include "../Base/Component.h"

/// <summary>
/// サウンドの読み込み、再生、停止を扱う
/// </summary>
class ComponentSound : public Component
{
private:
	int m_soundHandle;//サウンドのハンドル

	bool m_isPlaySound;

public:
	/// <summary>
	/// 呼び出し時にサウンドの解放を行う
	/// </summary>
	~ComponentSound() override;

	/// <summary>
	/// サウンドのロードを行う
	/// </summary>
	/// <param name="_filePath">サウンドのパス</param>
	void LoadSound(const char* _filePath);

	/// <summary>
	/// サウンドを他クラスで取得する
	/// </summary>
	/// <returns>サウンドハンドル</returns>
	int GetSound() const { return m_soundHandle; }

	void Play_Sound(int _playType);
	void Stop_Sound();
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;



};

