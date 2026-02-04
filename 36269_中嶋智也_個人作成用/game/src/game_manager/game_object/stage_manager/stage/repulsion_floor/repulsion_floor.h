#pragma once

#include "../stage.h"
#include "vivid.h"

// 反発床クラス
// プレイヤーやオブジェクトが接触した際に、
// 特殊な反応（反発・押し戻し等）を引き起こすことを想定したステージ要素
class CRepulsionFloor
	: public IStage
{
public:
	// コンストラクタ
	// ステージサイズおよび STAGE_ID は実装側で固定定義し、
	// 外部からの変更を許可しない設計とする
	CRepulsionFloor(void);

	// デストラクタ
	// 動的リソースを保持しないため default 指定
	~CRepulsionFloor(void) = default;

	// 初期化処理
	// 配置座標のみを外部から受け取り、
	// 振る舞い（反発処理）は Update / 衝突処理側に委譲する
	void Initialize(const vivid::Vector2& position) override;

	// 描画処理
	// ロジックとは独立した純粋なレンダリング責務のみを持つ
	void Draw(void) override;

private:
	// 論理的な当たり判定サイズ
	static const int m_width;   // 幅
	static const int m_height;  // 高さ

	static const std::string m_floor_texture_path;	// 床の絵のファイルパス
};
