#pragma once

#include "../scene.h"
#include "vivid.h"

class CTitle
	: public IScene
{
public:
	// コンストラクタ
	CTitle(void);

	// デストラクタ
	~CTitle(void) = default;

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
};