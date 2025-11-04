#pragma once

#include "vivid.h"
#include "../character.h"

class CPlayer 
	: public ICharacter
{
public:
	// コンストラクタ
	CPlayer(void);

	// デストラクタ
	~CPlayer(void);

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

	// 地面の上にいる判定
	//bool OnGround(CStage* stage)override;

	// ジャンプ
	void Jump(void) override;

	// 重力変更
	//void ChangeGravity(void) override;

	// 天井にあたっているかの判定
	//bool CheckHitCeiling(CStage* stage) override;

private:
	// 生存
	void Alive(void) override;

	// 死亡
	void Dead(void) override;

	static const int m_width;						// 幅
	static const int m_height;						// 高さ
	static const int m_max_life;					// 最大ライフ
	static const float m_radius;					// 半径
	static const vivid::Vector2 m_start_position;	// 初期位置
	static const float m_jump_power;				// ジャンプ力

	vivid::Vector2	m_Jump;							// ジャンプ
	float			m_Rotaition;					// 回転

};