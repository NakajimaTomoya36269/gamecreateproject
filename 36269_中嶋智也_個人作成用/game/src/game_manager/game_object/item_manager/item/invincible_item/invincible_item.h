#pragma once

#include "vivid.h"
#include "../item.h"

class CInvincibleItem
	: public IItem
{
public:
	// コンストラクタ
	CInvincibleItem(void);

	// デストラクタ
	~CInvincibleItem(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

private:
	static const int		m_width;		// 幅
	static const int		m_height;		// 高さ
};