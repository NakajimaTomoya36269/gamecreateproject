#pragma once

#include "vivid.h"
#include "../stage.h"

// 短い床クラス
// ・移動や特殊挙動を持たない固定床
// ・ステージの足場バリエーション用の最小構成クラス
// ・IStage の基本機能（当たり判定・位置管理）のみを利用する
class CShortFloor
	: public IStage
{
public:
	// コンストラクタ
	// ステージIDと当たり判定サイズは基底クラスで設定される
	CShortFloor(void);

	// デストラクタ
	// リソースを直接保持しないため特別な解放処理は不要
	~CShortFloor(void);

	// 初期化
	// 引数の position を床の初期配置座標として設定する
	// ステージ生成時に一度だけ呼ばれる想定
	void Initialize(const vivid::Vector2& position) override;

	// 描画
	// 短い床用テクスチャを現在の位置に描画する
	// ロジック更新は行わない（見た目のみの責務）
	void Draw(void) override;

private:
	// 当たり判定および描画サイズ（固定値）
	static const int		m_width;	// 横幅
	static const int		m_height;	// 高さ
};
