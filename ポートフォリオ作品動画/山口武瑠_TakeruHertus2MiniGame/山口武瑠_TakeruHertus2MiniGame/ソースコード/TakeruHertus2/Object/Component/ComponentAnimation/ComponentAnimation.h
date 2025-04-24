#pragma once
#include "../Base/Component.h"
#include "../ComponentModel/ComponentModel.h"

/// <summary>
/// アニメーション定数
/// </summary>
namespace ANIMATION
{
	static constexpr float PLAY_ANIM_BLEND_SPEED = 1.0f;//アニメーションブレンドの速度
	static constexpr float PLAY_ANIM_SPEED = 0.5f;		//通常アニメーションの速度
}

/// <summary>
/// アニメーションのコンポーネント：引数指定：ComponentModel
/// </summary>
class ComponentAnimation : public Component
{
private:
	std::shared_ptr<ComponentModel> m_model;//アニメーションを扱うためにコンポーネントモデルを参照させる


	/*ブレンドで使用するアニメーションの変数*/
	int		m_blendPlayAnim1;				// 再生しているアニメーション１のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	m_blendAnimPlayCount1;			// 再生しているアニメーション１の再生時間
	int		m_blendPlayAnim2;				// 再生しているアニメーション２のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	m_blendAnimPlayCount2;			// 再生しているアニメーション２の再生時間
	float	m_blendAnimBlendRate;			// 再生しているアニメーション１と２のブレンド率
	float   m_blendAnimTotalTime;			// アニメーションの総再生時間

	//ブレンドアニメーションの更新
	void UpdatePlayBlendAnim();

	/*通常のアニメーション変数*/
	float m_anim_TotalTime;
	float m_anim_NowTime;
	int m_animIndex;
	int m_newAnimIndex;

	//通常アニメーションの更新
	void UpdatePlayAnim();

	/*アニメーション再生フラグ*/
	bool m_isPlayingAnimation;


	/*アニメーションの再生区間を設定する*/
	float m_loopStartTime;
	float m_loopEndTime;

public:
	/// <summary>
	///　アニメーションコンポーネント（引数指定：モデルコンポーネント）
	/// </summary>
	/// <param name="_model">モデルコンポーネント</param>
	ComponentAnimation(std::shared_ptr<ComponentModel> _model);
	
	/// <summary>
	/// ブレンドされたアニメーションの再生
	/// </summary>
	/// <param name="_playBlendAnim"></param>
	void PlayBlendAnim(int _playBlendAnim);

	/// <summary>
	/// 通常アニメーションの再生
	/// </summary>
	/// <param name="_playAnim"></param>
	void PlayAnim(int _playAnim);

	//アニメーションの再生時間をリセットする
	void ResetAnimationNowTime();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	//********************************************************//
	//	セッターとゲッター
	//********************************************************//

	/// <summary>
	/// アニメーションが再生中かのフラグ
	/// </summary>
	/// <returns></returns>
	bool GetIsAnimPlaying() const { return m_isPlayingAnimation; }

};

