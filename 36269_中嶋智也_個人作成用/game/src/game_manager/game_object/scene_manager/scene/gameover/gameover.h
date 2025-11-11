#pragma once
#include "../scene.h"
#include "vivid.h"

class CGameOver
	: public IScene
{
public:
	// コンストラクタ
	CGameOver(void);

	// デストラクタ
	~CGameOver(void) = default;

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
	static const int	m_gameover_font_size;	// ゲームオーバーフォントサイズ

	vivid::Vector2		m_Position;			// 位置
	vivid::Vector2		m_GameOverPosition;	// ゲームオーバーの位置
};