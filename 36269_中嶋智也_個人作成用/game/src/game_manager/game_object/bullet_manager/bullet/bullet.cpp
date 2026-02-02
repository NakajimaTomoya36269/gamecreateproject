#include "bullet.h"
#include "../../stage_manager/stage/stage.h"
#include "../../box_collider/box_collider.h"

//------------------------------------------------------------
// 定数定義
//------------------------------------------------------------
const float IBullet::m_scroll_speed = 60.0f; // スクロール影響速度
const float IBullet::m_friction = 0.9f;  // スクロール減衰率

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
// 派生クラスからサイズ・半径・弾IDを受け取る
IBullet::IBullet(int width, int height, float radius, BULLET_ID id)
	: m_Width(width)                    // 幅
	, m_Height(height)                  // 高さ
	, m_Radius(radius)                  // 半径（円判定用）
	, m_BulletID(id)                    // 弾の種類ID
	, m_Rotation(0.0f)                  // 回転角
	, m_ActiveFlag(true)                // 有効フラグ
	, m_Position(vivid::Vector2(0.0f, 0.0f)) // 位置
	, m_Velocity(vivid::Vector2(0.0f, 0.0f)) // 弾自身の速度
	, m_ScrollVelocity(vivid::Vector2(0.0f, 0.0f)) // 背景スクロール影響
	, m_Rect{ 0, 0, m_Width, m_Height } // 描画用矩形
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f)) // 回転中心
	, m_Scale(vivid::Vector2(1.0f, 1.0f)) // 拡大率
{
}

//------------------------------------------------------------
// 初期化処理
//------------------------------------------------------------
// position  : 初期位置
// direction : 発射角（ラジアン）
// speed     : 発射速度
void IBullet::Initialize(const vivid::Vector2& position, float direction, float speed)
{
	m_Position = position;

	// 角度から速度ベクトルを生成
	m_Velocity.x = cos(direction) * speed;
	m_Velocity.y = sin(direction) * speed;

	m_ActiveFlag = true;
	m_ScrollVelocity = vivid::Vector2(0.0f, 0.0f);
	m_Rotation = 0.0f;
}

//------------------------------------------------------------
// 更新処理
//------------------------------------------------------------
void IBullet::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// プレイヤー移動によるスクロール影響
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	if (right_move_key)
	{
		// 右移動時は背景が左に流れる
		m_ScrollVelocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		// 左移動時は背景が右に流れる
		m_ScrollVelocity.x += m_scroll_speed;
	}

	// スクロールによる移動
	m_Position.x += m_ScrollVelocity.x * vivid::GetDeltaTime();

	// 摩擦による減衰
	m_ScrollVelocity.x *= m_friction;

	// 弾自身の移動
	m_Position += m_Velocity;

	// 画面外チェック
	CheckArea();

	// 進行方向に向けて回転
	m_Rotation = atan2(m_Velocity.y, m_Velocity.x);
}

//------------------------------------------------------------
// 描画（派生クラスで実装）
//------------------------------------------------------------
void IBullet::Draw(void)
{
}

//------------------------------------------------------------
// 解放処理（必要に応じて派生で実装）
//------------------------------------------------------------
void IBullet::Finalize(void)
{
}

//------------------------------------------------------------
// ステージとの当たり判定
//------------------------------------------------------------
bool IBullet::CheckHitStage(IStage* stage)
{
	if (!stage) return false;

	// 矩形同士の当たり判定
	if (CBoxCollider::GetInstance().CheckBoxCollision(
		m_Position, m_Width, m_Height,
		stage->GetPosition(), stage->GetWidth(), stage->GetHeight()))
	{
		// ヒットしたら弾を無効化
		m_ActiveFlag = false;
		return true;
	}

	return false;
}

//------------------------------------------------------------
// 位置取得
//------------------------------------------------------------
vivid::Vector2 IBullet::GetPosition(void)
{
	return m_Position;
}

//------------------------------------------------------------
// 中心座標取得（円判定用）
//------------------------------------------------------------
vivid::Vector2 IBullet::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2(m_Radius, m_Radius);
}

//------------------------------------------------------------
// サイズ・状態取得
//------------------------------------------------------------
int IBullet::GetWidth(void) { return m_Width; }
int IBullet::GetHeight(void) { return m_Height; }
float IBullet::GetRadius(void) { return m_Radius; }
bool IBullet::GetActiveFlag(void) { return m_ActiveFlag; }

//------------------------------------------------------------
// 有効フラグ設定
//------------------------------------------------------------
void IBullet::SetActiveFlag(bool active)
{
	m_ActiveFlag = active;
}

//------------------------------------------------------------
// 弾ID取得
//------------------------------------------------------------
BULLET_ID IBullet::GetBulletID(void)
{
	return m_BulletID;
}

//------------------------------------------------------------
// 画面外チェック
//------------------------------------------------------------
void IBullet::CheckArea(void)
{
	// 画面外に出たら無効化
	if (m_Position.x < 0.0f || m_Position.x >(float)vivid::WINDOW_WIDTH ||
		m_Position.y < 0.0f || m_Position.y >(float)vivid::WINDOW_HEIGHT)
	{
		m_ActiveFlag = false;
	}
}
