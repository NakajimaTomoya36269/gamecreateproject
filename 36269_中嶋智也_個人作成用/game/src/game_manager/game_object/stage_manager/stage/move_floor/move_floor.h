#pragma once

#include "vivid.h"
#include "../stage.h"

//====================================================
// 可動床クラス
//====================================================
// ・IStage を継承したギミック床
// ・スイッチと連動して左右移動を行う
// ・移動範囲は初期配置位置を基準とする
//
// 設計方針：
// ・スクロール移動（外的要因）と
//   床自身の移動（内的要因）を分離
// ・スイッチ依存は最小限に抑え、
//   状態の ON / OFF のみを受け取る
//====================================================
class CMoveFloor
	: public IStage
{
public:
	// コンストラクタ
	// サイズ・ID はクラス定数で固定
	CMoveFloor(void);

	// デストラクタ
	// リソース管理は基底クラスに委譲
	~CMoveFloor(void) = default;

	// 初期化
	// @param position : 初期配置位置
	// ・移動範囲の基準点として内部に保持
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	// ・スクロールによる位置補正
	// ・スイッチ ON 時のみ床が左右移動
	void Update(void) override;

	// 描画
	// ・現在位置に可動床テクスチャを描画
	void Draw(void) override;

	// 解放
	// ・現在は基底クラスの処理のみ
	void Finalize(void) override;

	// スイッチ連動処理
	// @param sw : 対応するスイッチ
	// ・ON/OFF に応じて床の稼働状態を切り替える
	void MoveChange(ISwitch* sw) override;

private:
	//------------------------------
	// 移動制御用メンバ
	//------------------------------
	vivid::Vector2	m_StartPosition;	// 移動範囲の基準位置
	vivid::Vector2	m_MoveVelocity;		// 床自身の移動速度
	bool			m_ChangeMove;		// 移動方向反転フラグ
	bool			m_ActiveFlag;		// スイッチによる稼働状態

	//------------------------------
	// クラス共通パラメータ
	//------------------------------
	static const int	m_width;		// 床の幅
	static const int	m_height;		// 床の高さ
	static const float	m_move_speed;	// 床の移動速度
	static const std::string m_floor_texture_path;	// 床の絵のファイルパス
};
