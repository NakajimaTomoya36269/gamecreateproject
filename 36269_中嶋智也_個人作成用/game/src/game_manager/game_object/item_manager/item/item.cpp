#include "item.h"

//==================================================
// クラス共通定数
//==================================================

// スクロール入力による擬似移動速度
const float IItem::m_scroll_speed = 60.0f;

// 慣性減衰用摩擦係数
const float IItem::m_friction = 0.9f;

//==================================================
// コンストラクタ / デストラクタ
//==================================================
IItem::IItem(int width, int height, float radius, ITEM_ID id)
	: m_Width(width)                         // 描画・判定幅
	, m_Height(height)                       // 描画・判定高さ
	, m_Radius(radius)                       // 円形当たり判定半径
	, m_ItemID(id)                           // アイテム種別
	, m_ActiveFlag(true)                     // 有効フラグ
	, m_Position(vivid::Vector2(0.0f, 0.0f)) // ワールド座標
	, m_Velocity(vivid::Vector2(0.0f, 0.0f)) // スクロール慣性用速度
{
}

IItem::~IItem(void)
{
}

//==================================================
// 初期化
//==================================================
void IItem::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_ActiveFlag = true;
}

//==================================================
// 更新処理
//==================================================
// ・入力に応じたスクロール追従
// ・慣性＋摩擦による自然減速
void IItem::Update(void)
{
	namespace keyboard = vivid::keyboard;

	const bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	const bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	// プレイヤー移動に同期した逆方向スクロール
	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}

	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	// 速度積分（Δt ベース）
	m_Position += m_Velocity * vivid::GetDeltaTime();

	// 摩擦による慣性減衰
	m_Velocity.x *= m_friction;
}

//==================================================
// 描画 / 解放
//==================================================
void IItem::Draw(void)
{
	// 派生クラスで実装
}

void IItem::Finalize(void)
{
	// 現状は明示的な解放処理なし
}

//==================================================
// アクセサ
//==================================================
int IItem::GetWidth(void)
{
	return m_Width;
}

int IItem::GetHeight(void)
{
	return m_Height;
}

float IItem::GetRadius(void)
{
	return m_Radius;
}

vivid::Vector2 IItem::GetPosition(void)
{
	return m_Position;
}

vivid::Vector2 IItem::GetCenterPosition(void)
{
	// 円形当たり判定用中心座標
	return m_Position + vivid::Vector2(m_Radius, m_Radius);
}

bool IItem::GetActive(void)
{
	return m_ActiveFlag;
}

void IItem::SetActive(bool active)
{
	m_ActiveFlag = active;
}

ITEM_ID IItem::GetItemID(void)
{
	return m_ItemID;
}
