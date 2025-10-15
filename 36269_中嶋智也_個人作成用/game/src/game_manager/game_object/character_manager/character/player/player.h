#pragma once

#include "vivid.h"
#include "../character.h"

class CPlayer : public ICharacter
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

private:
	// 生存
	void Alive(void) override;

	// 死亡
	void Dead(void) override;

	static const int m_width;
	static const int m_height;
	static const int m_max_life;
	static const float m_radius;
	static const vivid::Vector2 m_start_position;

};