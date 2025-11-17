#pragma once
#include "vivid.h"
#include "stage_id.h"
#include "../../character_manager/character/character.h"

class IStage
{
public:
	// コンストラクタ
	IStage(int width, int height, STAGE_ID id);

	// デストラクタ
	virtual ~IStage(void) = default;

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// キャラクターのアタリ判定
	virtual bool CheckHitCharacter(ICharacter* character, float& position_x);

protected:
	static const float	m_scroll_speed;
	static const float	m_friction;

	int					m_Width;
	int					m_Height;
	STAGE_ID			m_StageID;
	vivid::Vector2		m_Position;
	vivid::Vector2		m_Velocity;
};