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
	static const int	m_title_font_size;	// タイトルフォントサイズ
	static const int	m_enter_font_size;	// エンターフォントサイズ

	vivid::Vector2		m_Position;			// 位置
	vivid::Vector2		m_TitlePosition;	// タイトルの位置
	vivid::Vector2		m_EnterPosition;	// エンターの位置
	float				m_Angle;			// 角度
	unsigned int		m_Color;			// 色
};