#pragma once

#include "vivid.h"
#include "item_id.h"

class IItem
{
public:
	// コンストラクタ
	IItem(int width, int height, ITEM_ID id);

	// デストラクタ
	virtual ~IItem(void);

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

	// アクティブフラグの取得
	bool GetActive(void);

	// アクティブフラグの設定
	void SetActive(bool active);

	// アイテムIDの取得
	ITEM_ID GetItemID(void);

private:
	int				m_Width;	// 幅
	int				m_Height;	// 高さ
	bool			m_ActiveFlag;// アクティブフラグ
	vivid::Vector2	m_Position;	// 位置
	vivid::Vector2	m_Velocity;	// 速さ
	ITEM_ID			m_ItemID;	// アイテムのID

	static const float	m_scroll_speed;	// スクロールスピード
	static const float	m_friction;		// 摩擦力
};