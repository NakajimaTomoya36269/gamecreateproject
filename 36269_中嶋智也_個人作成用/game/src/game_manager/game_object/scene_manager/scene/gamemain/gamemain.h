#pragma once

#include "../scene.h"
#include "vivid.h"
#include "../../../goal/goal.h"
#include "../../../background/background.h"
#include "gamemain_state.h"

class CGamemain : public IScene
{
public:
	// コンストラクタ
	CGamemain(void);

	// デストラクタ
	~CGamemain(void) = default;

	// 初期化
	void Initialize(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

private:
	// プレイ状態の更新
	void UpdatePlay(void);

	// ポーズ状態の更新
	void UpdatePause(void);

	// 状態変更
	void ChangeState(void);

	static const int	m_font_size;		// フォントサイズ

	vivid::Vector2		m_Position;			// 位置

	CGoal				m_goal;				// ゴールクラスのオブジェクト作成
	CBackGround			m_background;		// 背景クラスのオブジェクト作成

	GAMEMAIN_STATE_ID	m_CurrentStateID;	// 現在のゲームメインでの状態
};