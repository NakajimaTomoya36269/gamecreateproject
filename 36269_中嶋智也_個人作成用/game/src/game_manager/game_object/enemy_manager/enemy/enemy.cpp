#include "enemy.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"
#include "../../stage_manager/stage/long_floor/long_floor.h"

/*
==================================================
 Enemy 共通パラメータ（全敵共通）
==================================================
*/
const float IEnemy::m_gravity_speed = 0.5f;	// 重力加速度
const float IEnemy::m_max_gravity = 30.0f;	// 落下速度の上限
const float IEnemy::m_scroll_speed = 60.0f;	// スクロール影響速度
const float IEnemy::m_move_speed = 5.0f;	// 横移動速度
const float IEnemy::m_friction = 0.9f;	// 摩擦（減衰率）
const float IEnemy::m_jump_power = 30.0f;	// ジャンプ力

/*
==================================================
 コンストラクタ
 ・敵のサイズ・当たり判定・ID などを設定
 ・座標や速度は初期値にする
==================================================
*/
IEnemy::IEnemy(int width, int height, float radius, int life, ENEMY_ID enemy_id)
	: m_Width(width)							// 幅
	, m_Height(height)							// 高さ
	, m_Radius(radius)							// 半径
	, m_Life(life)								// 現在ライフ
	, m_MaxLife(life)							// 最大ライフ
	, m_EnemyID(enemy_id)						// 敵ID
	, m_State(ENEMY_STATE::ALIVE)				// 状態（生存）
	, m_Active(true)							// 有効フラグ
	, m_MoveChange(false)						// 移動方向反転フラグ
	, m_Position(vivid::Vector2(0.0f, 0.0f))	// 位置
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))	// 速度
	, m_MoveVelocity(vivid::Vector2(0.0f, 0.0f))// 移動用速度
	, m_Anchor(vivid::Vector2(
		(float)m_Width / 2.0f,
		(float)m_Height / 2.0f))				// 回転・基準点
	, m_Rect{ 0, 0, m_Width, m_Height }			// 矩形当たり判定
	, m_Jump(vivid::Vector2(0.0f, 0.0f))		// ジャンプベクトル
	, m_CurrentStage(nullptr)					// 現在乗っている床
{
}

/*
==================================================
 初期化
 ・位置・速度・状態をリセット
==================================================
*/
void IEnemy::Initialize(const vivid::Vector2& position)
{
	m_Position = position;					// 初期位置
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_MoveVelocity = vivid::Vector2(0.0f, 0.0f);
	m_Jump = vivid::Vector2(0.0f, m_jump_power);
	m_Gravity = m_gravity_speed;
	m_Active = true;
	m_MoveChange = false;
	m_State = ENEMY_STATE::ALIVE;
}

/*
==================================================
 更新処理
 ・敵の状態によって処理を切り替える
==================================================
*/
void IEnemy::Update(void)
{
	switch (m_State)
	{
	case ENEMY_STATE::ALIVE: Alive(); break;
	case ENEMY_STATE::DEAD:  Dead();  break;
	}
}

/*
==================================================
 描画処理
 ・共通描画はなし（派生クラスで描画）
==================================================
*/
void IEnemy::Draw(void)
{
#ifdef _DEBUG
	// デバッグ表示用（必要に応じて使用）
	// vivid::DrawText(40, std::to_string(m_MoveVelocity.x), vivid::Vector2(0.0f, 80.0f));
#endif 
}

/*
==================================================
 解放処理
 ・基本クラスでは特に何もしない
==================================================
*/
void IEnemy::Finalize(void)
{
}

/*
==================================================
 床との当たり判定
 ・敵が床の上にいるかを判定
 ・反発床ならジャンプさせる
==================================================
*/
bool IEnemy::OnGround(IStage* stage)
{
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Position.y + (float)m_Height > stage->GetPosition().y)
		{
			// 床の上に位置を補正
			m_Position.y = stage->GetPosition().y - (float)m_Height;
			m_Velocity.y = 0.0f;

			// 反発床の場合はジャンプ
			if (stage->GetStageID() == STAGE_ID::REPULSION_FLOOR)
			{
				m_Velocity.y -= m_Jump.y;
				return true;
			}

			m_CurrentStage = stage;
			return true;
		}
	}
	else
	{
		// 空中にいる場合は重力を加算
		if (m_Velocity.y < m_max_gravity)
			m_Velocity.y += m_Gravity;
	}

	return false;
}

/*
==================================================
 攻撃処理（共通）
 ・派生クラスでオーバーライド前提
==================================================
*/
void IEnemy::Attack(ICharacter* character)
{
	if (!character) return;
}

/*
==================================================
 各種 Getter / Setter
==================================================
*/
vivid::Vector2 IEnemy::GetPosition(void)
{
	return m_Position;
}

void IEnemy::SetPosition(const vivid::Vector2& position)
{
	m_Position = position;
}

vivid::Vector2 IEnemy::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2(m_Radius, m_Radius);
}

int IEnemy::GetWidth(void)
{
	return m_Width;
}

int IEnemy::GetHeight(void)
{
	return m_Height;
}

bool IEnemy::GetActive(void)
{
	return m_Active;
}

void IEnemy::SetActive(bool active)
{
	m_Active = active;
}

float IEnemy::GetRadius(void)
{
	return m_Radius;
}

/*
==================================================
 移動範囲制御
 ・現在の床の範囲内で左右に往復移動
==================================================
*/
void IEnemy::MoveArea(void)
{
	const float move_area_margin = 50.0f;

	if (!m_CurrentStage) return;

	// 移動範囲の端に来たら方向反転
	if (m_Position.x > m_CurrentStage->GetPosition().x +
		(float)m_CurrentStage->GetWidth() - move_area_margin)
	{
		m_MoveChange = true;
	}
	else if (m_Position.x < m_CurrentStage->GetPosition().x)
	{
		m_MoveChange = false;
	}

	// 移動方向に応じて速度変更
	if (m_MoveChange)
	{
		m_MoveVelocity.x -= m_move_speed;
	}
	else
	{
		m_MoveVelocity.x += m_move_speed;
	}

	// 移動反映
	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();
	m_MoveVelocity.x *= m_friction;
}

/*
==================================================
 生存時の処理
 ・床上移動
 ・スクロールに合わせて補正移動
==================================================
*/
void IEnemy::Alive(void)
{
	MoveArea();

	namespace keyboard = vivid::keyboard;

	// スクロールに追従
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	m_Position.x += m_Velocity.x * vivid::GetDeltaTime();
	m_Velocity.x *= m_friction;
}

/*
==================================================
 死亡時の処理
 ・派生クラスで拡張前提
==================================================
*/
void IEnemy::Dead(void)
{
}
