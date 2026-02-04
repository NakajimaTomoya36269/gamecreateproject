#pragma once

#include "../stage.h"
#include "vivid.h"

class CReverseMoveFloor
	: public IStage
{
public:
	// コンストラクタ
	CReverseMoveFloor(void);

	// デストラクタ
	~CReverseMoveFloor(void) = default;

	// 初期化
	// position : 床の初期配置座標
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	// スイッチOFF時に自動で左右移動する床の挙動を制御
	void Update(void) override;

	// 描画
	// 逆制御移動床の描画
	void Draw(void) override;

	// 解放
	// 使用リソースの後処理
	void Finalize(void) override;

	// 移動方向変更
	// sw が ON のとき床は停止、OFF のとき自動移動する
	void MoveChange(ISwitch* sw) override;

private:
	// 初期位置（移動範囲の基準点）
	vivid::Vector2	m_StartPosition;

	// 自動移動用の速度ベクトル
	vivid::Vector2	m_MoveVelocity;

	// 移動方向反転フラグ
	// true  : 左方向へ移動
	// false : 右方向へ移動
	bool			m_ChangeMove;

	// 動作状態フラグ
	// true  : 停止状態（スイッチON）
	// false : 自動移動中
	bool			m_ActiveFlag;

	// 床の幅
	static const int	m_width;

	// 床の高さ
	static const int	m_height;

	// 自動移動時の速度
	static const float	m_move_speed;

	// 床の絵のファイルパス
	static const std::string m_floor_texture_path;
};
