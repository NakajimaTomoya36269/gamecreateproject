#include "goal.h"

//==================================================
// 定数定義
//==================================================

// ゴール画像の横幅
const int	CGoal::m_width = 128;

// ゴール画像の縦幅
const int	CGoal::m_height = 128;

// スクロール時の移動速度
const float CGoal::m_scroll_speed = 60.0f;

// 摩擦係数（移動後に速度を減衰させる）
const float CGoal::m_friction = 0.9f;

//==================================================
// コンストラクタ
//==================================================
CGoal::CGoal(void)
	: m_Position(0.0f, 0.0f)	// 初期位置
	, m_Velocity(0.0f, 0.0f)	// 初期速度
{
}

//==================================================
// 初期化
// ・ゴールの初期位置を設定
//==================================================
void CGoal::Initialize(const vivid::Vector2& position)
{
	// 位置の設定
	m_Position = position;

	// 速度を初期化
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

//==================================================
// 更新処理
// ・左右キーに応じてスクロール移動
// ・摩擦による減速処理
//==================================================
void CGoal::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// 右移動キー入力
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);

	// 左移動キー入力
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	// 右キーが押されたら左方向へ移動（背景スクロール用）
	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}

	// 左キーが押されたら右方向へ移動（背景スクロール用）
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	// 位置を速度とデルタタイムで更新
	m_Position += m_Velocity * vivid::GetDeltaTime();

	// 摩擦による減速処理
	m_Velocity.x *= m_friction;
}

//==================================================
// 描画処理
//==================================================
void CGoal::Draw(void)
{
	// ゴール画像を現在位置に描画
	vivid::DrawTexture("data\\goal.png", m_Position);
}

//==================================================
// 解放処理
// ・現在は特に処理なし
//==================================================
void CGoal::Finalize(void)
{
}

//==================================================
// 幅の取得
//==================================================
int CGoal::GetWidth(void)
{
	return m_width;
}

//==================================================
// 高さの取得
//==================================================
int CGoal::GetHeight(void)
{
	return m_height;
}

//==================================================
// 位置の取得
//==================================================
vivid::Vector2 CGoal::GetPosition(void)
{
	return m_Position;
}
