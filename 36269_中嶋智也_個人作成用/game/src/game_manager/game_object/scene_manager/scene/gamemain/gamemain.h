#pragma once

#include "../scene.h"
#include "vivid.h"
#include "../../../goal/goal.h"
#include "../../../background/background.h"

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
	static const int	m_font_size;	// フォントサイズ

	vivid::Vector2		m_Position;		// 位置

	CGoal				m_goal;			// ゴールクラスのオブジェクト作成
	CBackGround			m_background;	// 背景クラスのオブジェクト作成
};