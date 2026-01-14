#pragma once

#include "vivid.h"
#include "../stage.h"

class CMoveFloor
	: public IStage
{
public:
	// コンストラクタ
	CMoveFloor(void);

	// デストラクタ
	~CMoveFloor(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

	// 移動方向変更
	void MoveChange(ISwitch* sw) override;

private:
	vivid::Vector2			m_StartPosition;// 初めの位置
	vivid::Vector2			m_MoveVelocity;	// 動く速さ
	bool					m_ChangeMove;	// 動く向き変更フラグ

	static const int		m_width;		// 幅
	static const int		m_height;		// 高さ
	static const float		m_move_speed;	// 動く速さ
};