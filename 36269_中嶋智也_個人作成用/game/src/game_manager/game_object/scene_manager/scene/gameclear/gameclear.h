#pragma once
#include "../scene.h"
#include "vivid.h"

class CGameClear
	: public IScene
{
public:
	// コンストラクタ
	CGameClear(void);

	// デストラクタ
	~CGameClear(void) = default;

	// 初期化
	void Initialize(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

private:
	static const int	m_font_size;		// フォントサイズ
	static const int	m_gameclear_font_size;	// ゲームクリアフォントサイズ

	vivid::Vector2		m_Position;			// 位置
	vivid::Vector2		m_GameClearPosition;	// ゲームクリアの位置
};