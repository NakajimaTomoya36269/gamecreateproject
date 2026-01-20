#pragma once
#include "vivid.h"
#include "stage_id.h"
#include "../../character_manager/character/character.h"

class ISwitch;

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

	virtual void MoveChange(ISwitch* sw);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// ステージIDの取得
	STAGE_ID GetStageID(void);

	// 落下フラグの取得
	bool GetIsFalled(void);

	// 落下フラグの設定
	void SetIsFalled(bool fall_flag);

	// 落下
	void Falled(void);

	// キャラクターのアタリ判定
	virtual bool CheckHitCharacter(ICharacter* character, float& position_x);

protected:
	static const float	m_scroll_speed;			// スクロールスピード
	static const float	m_friction;				// 摩擦力

	int					m_Width;				// 幅
	int					m_Height;				// 高さ
	STAGE_ID			m_StageID;				// ステージID
	vivid::Vector2		m_Position;				// 位置
	vivid::Vector2		m_StartPosition;		// 開始位置
	vivid::Vector2		m_Velocity;				// 速さ
	bool				m_IsFalled;				// 落下フラグ
};