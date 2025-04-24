#include "ComponentAnimation.h"

void ComponentAnimation::UpdatePlayBlendAnim()
{
	//ブレンド率が１以下の場合は１に近づける
	if (m_blendAnimBlendRate < 1.0f)
	{
		//ブレンドレートにスピードを加算する
		m_blendAnimBlendRate += ANIMATION::PLAY_ANIM_BLEND_SPEED;
		
		//以上になれば
		if (m_blendAnimBlendRate > 1.0f)
		{
			//固定
			m_blendAnimBlendRate = 1.0f;
		}
	}

	//再生しているブレンドアニメーション１の処理
	if (m_blendPlayAnim1 != -1)
	{
		//アニメーションの総時間を取得
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->m_modelHandle, m_blendPlayAnim1);
		//時間を進める
		m_blendAnimPlayCount1 += ANIMATION::PLAY_ANIM_BLEND_SPEED;
		//再生時間が総時間に達したら再生時間をループ
		if (m_blendAnimPlayCount1 >= m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount1 = fmod(m_blendAnimPlayCount1, m_blendAnimTotalTime);
		}
		//変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model->m_modelHandle, m_blendPlayAnim1, m_blendAnimPlayCount1);
		//アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model->m_modelHandle, m_blendPlayAnim1, m_blendAnimBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (m_blendPlayAnim2 != -1)
	{
		// アニメーションの総時間を取得
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->m_modelHandle, m_blendPlayAnim2);

		// 再生時間を進める
		m_blendAnimPlayCount2 += ANIMATION::PLAY_ANIM_BLEND_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (m_blendAnimPlayCount2 > m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount2 = fmod(m_blendAnimPlayCount2, m_blendAnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model->m_modelHandle, m_blendPlayAnim2, m_blendAnimPlayCount2);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model->m_modelHandle, m_blendPlayAnim2, 1.0f - m_blendAnimBlendRate);
	}

}

void ComponentAnimation::UpdatePlayAnim()
{
	//アニメーションのインデックスについて、MV1Attachanimは中で加算される仕組みを持っているがために、
	//実際にアニメーションを実行画面で見るとぐちゃぐちゃになったり、吹っ飛んで行ったりする
	//これを防ぐために、アニメーションをタイミングででタッチしせねばならない
	if (m_newAnimIndex != m_animIndex)
	{
		m_animIndex = m_newAnimIndex;	//現在のインデックスに新しいインデックスを代入
		m_anim_NowTime = 0.0f;		//再生時間をリセットする
	}
	//再生時間を進める
	m_anim_NowTime += ANIMATION::PLAY_ANIM_SPEED;
	//アニメーションの再生時間をセットする
	MV1SetAttachAnimTime(m_model->m_modelHandle, m_animIndex, m_anim_NowTime);
	//アニメーション中のフラグを立てる
	m_isPlayingAnimation = true;

	//再生時間が総時間を上回ったら
	if (m_anim_NowTime >= MV1GetAttachAnimTotalTime(m_model->m_modelHandle, m_animIndex))
	{
		m_anim_NowTime = 0.0f;			//再生時間をリセット
		m_isPlayingAnimation = false;	//アニメーション中フラグをおろす
	}
}

void ComponentAnimation::PlayBlendAnim(int _playBlendAnim)
{
	// 再生中のモーション２が有効だったらデタッチする
	if (m_blendPlayAnim2 != -1)
	{
		m_blendPlayAnim2 = -1;
		MV1DetachAnim(m_model->m_modelHandle, m_blendPlayAnim2);
	}

	// 今まで再生中のモーション１だったものの情報を２に移動する
	m_blendPlayAnim2 = m_blendPlayAnim1;
	m_blendAnimPlayCount2 = m_blendAnimPlayCount1;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	m_blendPlayAnim1 = MV1AttachAnim(m_model->m_modelHandle, _playBlendAnim);
	m_blendAnimPlayCount1 = 0.0f;

	// ブレンド率は再生中のモーション２が有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
	m_blendAnimBlendRate = m_blendPlayAnim2 == -1 ? 1.0f : 0.0f;
}

void ComponentAnimation::PlayAnim(int _playAnim)
{
	//アニメーションをでタッチして
	m_animIndex = MV1DetachAnim(m_model->m_modelHandle, m_animIndex);
	//新しいアニメーションをアタッチする
	m_newAnimIndex = MV1AttachAnim(m_model->m_modelHandle, _playAnim);
}

void ComponentAnimation::ResetAnimationNowTime()
{
	m_anim_NowTime = 0;
}

ComponentAnimation::ComponentAnimation(std::shared_ptr<ComponentModel> _model)
	: m_model(_model)

	/*ブレンドアニメーション*/
	, m_blendPlayAnim1(-1)		  //アニメーション1のインデックス
	, m_blendAnimPlayCount1(0.0f) //アニメーション1再生カウント
	, m_blendPlayAnim2(-1)		  //アニメーション2のインデックス
	, m_blendAnimPlayCount2(0.0f) //アニメーション2再生カウント
	, m_blendAnimBlendRate(0.0f)  //アニメーションのブレンド率	
	, m_blendAnimTotalTime(0.0f)  //アニメーションの総時間

	/*通常アニメーション*/
	, m_animIndex(-1)			  //アニメーションのインデックス
	, m_newAnimIndex(-1)		  //新しいアニメーションのインデックス
	, m_anim_TotalTime(0.0f)	  //アニメーションの総時間
	, m_anim_NowTime(0.0f)	      //再生時間

	/*フラグ*/
	, m_isPlayingAnimation(false) //アニメーション再生中フラグ

	/*特定の区間を再生するアニメーション*/
	, m_loopStartTime(0.0f)
	, m_loopEndTime(0.0f)
{
}


void ComponentAnimation::Init()
{
	/*ブレンドアニメーション*/
	m_blendPlayAnim1 = -1;
	m_blendAnimPlayCount1 = 0.0f;
	m_blendPlayAnim2 = -1;
	m_blendAnimPlayCount2 = 0.0f;
	m_blendAnimBlendRate = 1.0f;
	m_blendAnimTotalTime = 0.0f;

	/*通常アニメーション*/
	m_animIndex = -1;
	m_newAnimIndex = -1;

	m_anim_TotalTime = 0.0f;
	m_anim_NowTime = 0.0f;

	/*アニメーション再生のフラグ*/
	m_isPlayingAnimation = false;

	/*特定の区間再生する*/
	m_loopStartTime = 0.0f;
	m_loopEndTime = 0.0f;
}

void ComponentAnimation::Update()
{
	//通常アニメーションの更新
	UpdatePlayAnim();
	//ブレンドアニメーションの更新
	UpdatePlayBlendAnim();
}

void ComponentAnimation::Draw()
{
}

void ComponentAnimation::Final()
{
}
