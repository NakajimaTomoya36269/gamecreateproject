#include "character.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"
#include "../../enemy_manager/enemy/enemy.h"
#include "../../item_manager/item/item.h"
#include "../../switch_manager/switch/switch.h"
#include "../../bullet_manager/bullet/bullet.h"

/*
================================
  定数定義（キャラクター共通）
================================
*/

// 重力の加速度
const float ICharacter::m_gravity_speed = 1.0f;

// 通常ジャンプ力
const float ICharacter::m_jump_power = 20.0f;

// ジャンプ強化の持続時間
const float ICharacter::m_jump_up_max_time = 1200.0f;

// ジャンプ強化時のジャンプ力
const float ICharacter::m_jump_up_power = 30.0f;

// 無敵時間の最大値
const float ICharacter::m_invincible_max_time = 600.0f;

// 落ちる床が崩れるまでの時間
const float ICharacter::m_fall_time = 600.0f;

// 着地猶予最大時間
const float ICharacter::m_coyote_max_time = 60.0f;

/*
================================
  コンストラクタ
================================
*/
ICharacter::ICharacter(int width, int height, float radius, int life,
	CHARACTER_CATEGORY category, CHARACTER_ID character_id)
	// サイズ関連
	: m_Width(width)
	, m_Height(height)
	, m_Radius(radius)

	// ライフ関連
	, m_Life(life)
	, m_MaxLife(life)

	// キャラクター属性
	, m_Category(category)
	, m_CharacterID(character_id)

	// 初期状態は生存
	, m_State(CHARACTER_STATE::ALIVE)
	, m_Active(true)

	// 状態フラグ初期化
	, m_GravityChange(false)
	, m_JumpUp(false)
	, m_InvincibleFlag(false)

	// 位置・速度
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))

	// 描画基準点（中心）
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))

	// 当たり判定用矩形
	, m_Rect{ 0, 0, m_Width, m_Height }

	// ジャンプ関連
	, m_Jump(vivid::Vector2(0.0f, 0.0f))
	, m_JumpUpTimer(0.0f)

	// 無敵・落下床・着地猶予タイマー
	, m_InvincibleTimer(0.0f)
	, m_FallTimer(0.0f)
	, m_CoyoteTimer(0.0f)
{
}

/*
================================
  デストラクタ
================================
*/
ICharacter::~ICharacter(void)
{
}

/*
================================
  初期化
================================
*/
void ICharacter::Initialize(const vivid::Vector2& position)
{
	// 初期位置設定
	m_Position = position;

	// 速度リセット
	m_Velocity = vivid::Vector2(0.0f, 0.0f);

	// 状態初期化
	m_Active = true;
	m_GravityChange = false;
	m_JumpUp = false;
	m_InvincibleFlag = false;

	// 重力初期化
	m_Gravity = m_gravity_speed;

	// 状態を生存に戻す
	m_State = CHARACTER_STATE::ALIVE;

	// ジャンプ関連初期化
	m_Jump = vivid::Vector2(0.0f, 0.0f);
	m_JumpUpTimer = 0.0f;

	// タイマー初期化
	m_InvincibleTimer = 0.0f;
	m_FallTimer = 0.0f;
	m_CoyoteTimer = 0.0f;
}

/*
================================
  更新処理
================================
*/
void ICharacter::Update(void)
{
	// 状態によって処理を分岐
	switch (m_State)
	{
	case CHARACTER_STATE::ALIVE:
		Alive();
		break;

	case CHARACTER_STATE::DEAD:
		Dead();
		break;
	}
}

/*
================================
  描画（派生クラスで実装）
================================
*/
void ICharacter::Draw(void)
{
}

/*
================================
  解放処理
================================
*/
void ICharacter::Finalize(void)
{
}

/*
================================
  地面判定
================================
*/
bool ICharacter::OnGround(IStage* stage)
{
	if (!stage) return false;

	// 矩形同士の簡易当たり判定
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		// 通常重力時（下に立つ）
		if (m_Position.y + (float)m_Height > stage->GetPosition().y
			&& !m_GravityChange)
		{
			// めり込み補正
			m_Position.y = stage->GetPosition().y - (float)m_Height;
			m_Velocity.y = 0.0f;

			// 反発床なら跳ねる
			if (stage->GetStageID() == STAGE_ID::REPULSION_FLOOR)
			{
				m_Velocity.y -= m_Jump.y / 2.0f;
				m_CoyoteTimer = m_coyote_max_time;
			}

			return true;
		}
		// 逆重力時（天井に立つ）
		else if (m_Position.y < stage->GetPosition().y + (float)stage->GetHeight()
			&& m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();
			m_Velocity.y = 0.0f;
			return true;
		}
	}

	return false;
}

/*
================================
  ジャンプ処理
================================
*/
void ICharacter::Jump(IStage* stage)
{
	if (!stage) return;

	namespace keyboard = vivid::keyboard;

	// ジャンプキー
	bool jump_key = keyboard::Trigger(keyboard::KEY_ID::UP);

	m_CoyoteTimer--;

	// 地面にいる時だけジャンプ
	if (jump_key && (OnGround(stage) || m_CoyoteTimer > 0.0f))
	{
		m_Velocity.y -= m_Jump.y;
		m_CoyoteTimer = 0.0f;
	}

}

/*
================================
  重力反転
================================
*/
void ICharacter::ChangeGravity(IStage* stage)
{
	namespace keyboard = vivid::keyboard;

	bool gravity_change_key = keyboard::Trigger(keyboard::KEY_ID::SPACE);

	// 地面にいる時のみ重力反転
	if (gravity_change_key && OnGround(stage))
	{
		m_GravityChange = !m_GravityChange;
	}
}

/*
================================
  天井判定
================================
*/
bool ICharacter::CheckHitCeiling(IStage* stage)
{
	if (!stage) return false;

	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		// 通常重力
		if (m_Velocity.y < 0.0f && !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();
			m_Velocity.y = 0.0f;
			return true;
		}
		// 逆重力
		else if (m_Velocity.y < 0.0f && m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;
			m_Velocity.y = 0.0f;
			return true;
		}
	}

	return false;
}

/*
================================
  壁当たり判定（右）
================================
*/
bool ICharacter::CheckHitRightWall(IStage* stage)
{
	if (!stage) return false;

	// 矩形同士の簡易当たり判定
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Position.x + (float)m_Width < stage->GetPosition().x)
		{
			m_Position.x = stage->GetPosition().x - (float)m_Width;
			m_Velocity.x = 0.0f;
			return true;
		}
	}

	return false;
}

/*
================================
  壁当たり判定（左）
================================
*/
bool ICharacter::CheckHitLeftWall(IStage* stage)
{
	if (!stage) return false;

	// 矩形同士の簡易当たり判定
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{

		if (m_Position.x > stage->GetPosition().x + (float)stage->GetWidth())
		{
			m_Position.x = stage->GetPosition().x + (float)stage->GetWidth();
			m_Velocity.x = 0.0f;
			return true;
		}
	}

	return false;
}

/*
================================
  敵との当たり判定
================================
*/
bool ICharacter::CheckHitEnemy(IEnemy* enemy)
{
	if (!enemy) return false;

	if (CBoxCollider::GetInstance().CheckCircleCollision(
		m_Position, m_Width, m_Height,
		enemy->GetCenterPosition(), enemy->GetRadius()) && !m_InvincibleFlag)
	{
		m_Life--;
		return true;
	}

	return false;
}

/*
================================
  アイテム取得判定
================================
*/
bool ICharacter::CheckHitItem(IItem* item)
{
	if (!item) return false;

	if (CBoxCollider::GetInstance().CheckCircleCollision(
		m_Position, m_Width, m_Height,
		item->GetPosition(), item->GetRadius()))
	{
		item->SetActive(false);
		return true;
	}

	return false;
}

/*
================================
  スイッチ判定
================================
*/
bool ICharacter::CheckHitSwitch(ISwitch* sw)
{
	namespace keyboard = vivid::keyboard;

	bool switch_on_flag = keyboard::Trigger(keyboard::KEY_ID::DOWN);

	if (!sw) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(
		m_Position, m_Width, m_Height,
		sw->GetPosition(), sw->GetWidth(), sw->GetHeight()))
	{
		if (sw->GetSwitchID() == SWITCH_ID::FLOOR_SWITCH && switch_on_flag)
		{
			sw->OnPress();
		}
		return true;
	}

	return false;
}

/*
================================
  弾との当たり判定
================================
*/
bool ICharacter::CheckHitBullet(IBullet* bullet)
{
	if (!bullet) return false;

	if (CBoxCollider::GetInstance().CheckCircleCollision(
		m_Position, m_Width, m_Height,
		bullet->GetCenterPosition(), bullet->GetRadius()) && !m_InvincibleFlag)
	{
		m_Life--;
		bullet->SetActiveFlag(false);
		return true;
	}

	return false;
}

/*
================================
  ゲッター / セッター
================================
*/
CHARACTER_ID ICharacter::GetCharacterID(void) { return m_CharacterID; }
CHARACTER_CATEGORY ICharacter::GetCategory(void) { return m_Category; }
vivid::Vector2 ICharacter::GetPosition(void) { return m_Position; }
float ICharacter::GetPositionX(void) { return m_Position.x; }
void ICharacter::SetPosition(const vivid::Vector2 position) { m_Position = position; }
int ICharacter::GetWidth(void) { return m_Width; }
int ICharacter::GetHeight(void) { return m_Height; }
float ICharacter::GetGravity(void) { return m_Gravity; }
void ICharacter::SetGravity(float gravity) { m_Gravity = gravity; }

vivid::Vector2 ICharacter::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f);
}

bool ICharacter::GetGravityChange(void) { return m_GravityChange; }
void ICharacter::SetGravityChange(bool gravity) { m_GravityChange = gravity; }

/*
================================
  ゴール判定
================================
*/
bool ICharacter::CheckHitGoal(CGoal& goal)
{
	return CBoxCollider::GetInstance().CheckBoxCollision(
		m_Position, m_Width, m_Height,
		goal.GetPosition(), goal.GetWidth(), goal.GetHeight());
}

/*
================================
  ジャンプ強化
================================
*/
void ICharacter::JumpUp(IItem* item)
{
	if (!item) return;

	if (CheckHitItem(item) && item->GetItemID() == ITEM_ID::JUMP_UP_ITEM)
	{
		m_JumpUp = true;
		m_JumpUpTimer = m_jump_up_max_time;
		m_Jump.y = m_jump_up_power;
	}

	if (m_JumpUp && --m_JumpUpTimer < 0.0f)
	{
		m_Jump.y = m_jump_power;
		m_JumpUp = false;
	}
}

/*
================================
  無敵処理
================================
*/
void ICharacter::Invincible(IItem* item)
{
	if (!item) return;

	if (CheckHitItem(item) && item->GetItemID() == ITEM_ID::INVINCIBLE_ITEM)
	{
		m_InvincibleFlag = true;
		m_InvincibleTimer = m_invincible_max_time;
	}

	if (m_InvincibleFlag && --m_InvincibleTimer < 0.0f)
	{
		m_InvincibleFlag = false;
	}
}

/*
================================
  落下床処理
================================
*/
void ICharacter::FallStage(IStage* stage)
{
	if (!stage) return;

	if (OnGround(stage))
	{
		if (stage->GetStageID() == STAGE_ID::FALL_FLOOR)
		{
			if (++m_FallTimer > m_fall_time)
			{
				stage->Falled();
			}
		}
		else
		{
			m_FallTimer = 0.0f;
		}
	}
}

/*
================================
  生存 / 死亡処理
================================
*/
bool ICharacter::GetActive(void) { return m_Active; }
void ICharacter::SetActive(bool active) { m_Active = active; }
int ICharacter::GetMaxLife(void) { return m_MaxLife; }
int ICharacter::GetLife(void) { return m_Life; }

void ICharacter::Alive(void)
{
	// 重力を加算
	m_Velocity.y += m_Gravity;
}

void ICharacter::Dead(void)
{
}
