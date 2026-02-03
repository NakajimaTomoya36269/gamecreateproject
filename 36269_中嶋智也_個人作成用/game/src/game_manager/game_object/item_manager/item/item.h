#pragma once

#include "vivid.h"
#include "item_id.h"

//==================================================
// アイテム基底クラス
//==================================================
// スクロール追従・当たり判定情報・有効管理を共通化する抽象基底。
// 派生クラスは「見た目」と「種類定義」に専念する。
class IItem
{
public:
	//==================================================
	// コンストラクタ / デストラクタ
	//==================================================

	// サイズ・当たり判定・アイテム種別を受け取って初期化
	IItem(int width, int height, float radius, ITEM_ID id);

	// 派生クラス破棄を考慮した仮想デストラクタ
	virtual ~IItem(void);

	//==================================================
	// ライフサイクル
	//==================================================

	// 初期配置・状態リセット
	virtual void Initialize(const vivid::Vector2& position);

	// スクロール追従を含む更新処理
	virtual void Update(void);

	// 描画（派生クラスで実装）
	virtual void Draw(void);

	// 解放処理（現状は拡張ポイント）
	virtual void Finalize(void);

	//==================================================
	// アクセサ
	//==================================================

	int GetWidth(void);                 // 幅
	int GetHeight(void);                // 高さ
	float GetRadius(void);              // 当たり判定半径

	vivid::Vector2 GetPosition(void);   // 左上座標
	vivid::Vector2 GetCenterPosition(void); // 円形判定用中心座標

	bool GetActive(void);               // 有効状態取得
	void SetActive(bool active);        // 有効状態設定

	ITEM_ID GetItemID(void);             // アイテム種別取得

protected:
	//==================================================
	// 共通状態
	//==================================================

	int             m_Width;        // 描画・判定幅
	int             m_Height;       // 描画・判定高さ
	float           m_Radius;       // 円形当たり判定半径
	bool            m_ActiveFlag;   // 有効フラグ

	vivid::Vector2  m_Position;     // ワールド座標
	vivid::Vector2  m_Velocity;     // スクロール慣性用速度

	ITEM_ID         m_ItemID;       // アイテム種別

	//==================================================
	// クラス共通パラメータ
	//==================================================

	static const float m_scroll_speed; // スクロール移動量
	static const float m_friction;     // 慣性減衰係数
};
