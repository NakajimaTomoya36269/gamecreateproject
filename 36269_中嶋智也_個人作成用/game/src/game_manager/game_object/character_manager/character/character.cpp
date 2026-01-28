#include "character.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"
#include "../../enemy_manager/enemy/enemy.h"
#include "../../item_manager/item/item.h"
#include "../../switch_manager/switch/switch.h"
#include "../../bullet_manager/bullet/bullet.h"

const float ICharacter::m_gravity_speed = 0.5f;
const float ICharacter::m_max_gravity = 30.0f;
const float ICharacter::m_jump_power = 70.0f;
const float ICharacter::m_jump_up_max_time = 1200.0f;
const float ICharacter::m_jump_up_power = 100.0f;
const float ICharacter::m_invincible_max_time = 600.0f;
const float ICharacter::m_fall_time = 600.0f;

ICharacter::ICharacter(int width, int height, float radius, int life,
	CHARACTER_CATEGORY category, CHARACTER_ID character_id)
	: m_Width(width)
	, m_Height(height)
	, m_Radius(radius)
	, m_Life(life)
	, m_MaxLife(life)
	, m_Category(category)
	, m_CharacterID(character_id)
	, m_State(CHARACTER_STATE::ALIVE)
	, m_Active(true)
	, m_GravityChange(false)
	, m_JumpUp(false)
	, m_InvincibleFlag(false)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect{ 0, 0, m_Width, m_Height }
	, m_Jump(vivid::Vector2(0.0f, 0.0f))
	, m_JumpUpTimer(0.0f)
	, m_InvincibleTimer(0.0f)
	, m_FallTimer(0.0f)
{
}

ICharacter::~ICharacter(void)
{
}

void ICharacter::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_Active = true;
	m_GravityChange = false;
	m_JumpUp = false;
	m_InvincibleFlag = false;
	m_Gravity = m_gravity_speed;
	m_State = CHARACTER_STATE::ALIVE;
	m_Jump = vivid::Vector2(0.0f, 0.0f);
	m_JumpUpTimer = 0.0f;
	m_InvincibleTimer = 0.0f;
	m_FallTimer = 0.0f;
}

void ICharacter::Update(void)
{
	switch (m_State)
	{
	case CHARACTER_STATE::ALIVE: Alive(); break;
	case CHARACTER_STATE::DEAD:	Dead();	break;
	}
}

void ICharacter::Draw(void)
{
}

void ICharacter::Finalize(void)
{
}

bool ICharacter::OnGround(IStage* stage)
{
	if (!stage)return false;

	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Position.y + (float)m_Height > stage->GetPosition().y
			&& !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;

			m_Velocity.y = 0.0f;

			if (stage->GetStageID() == STAGE_ID::REPULSION_FLOOR)
			{
				m_Velocity.y -= m_Jump.y / 2.0f;
			}

			return true;
		}
		else if (m_Position.y < stage->GetPosition().y + (float)stage->GetHeight()
			&& m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
	}
	if (m_Velocity.y < m_max_gravity)
		m_Velocity.y += m_Gravity;

	return false;
}

void ICharacter::Jump(IStage* stage)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool jump_key = keyboard::Trigger(keyboard::KEY_ID::UP);
	//bool jump_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B);

	//bool jump = jump_key || jump_button;

	if (jump_key && OnGround(stage))
	{
		m_Velocity.y -= m_Jump.y;
	}

	if (!m_GravityChange)
		m_Position.y += m_Velocity.y * vivid::GetDeltaTime();
	else
		m_Position.y -= m_Velocity.y * vivid::GetDeltaTime();
}

void ICharacter::ChangeGravity(IStage* stage)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool gravity_change_key = keyboard::Trigger(keyboard::KEY_ID::SPACE);
	//bool gravity_change_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A);

	//bool gravity_change = gravity_change_key || gravity_change_button;

	if (gravity_change_key && OnGround(stage))
	{
		m_GravityChange = !m_GravityChange;
	}
}

bool ICharacter::CheckHitCeiling(IStage* stage)
{
	if (!stage) return false;

	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Velocity.y < 0.0f && m_Position.y < stage->GetPosition().y + (float)stage->GetHeight() && !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
		 else if (m_Velocity.y < 0.0f && m_Position.y + (float)m_Height > stage->GetPosition().y && m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;

			m_Velocity.y = 0.0f;

			return true;
		}
	}

	return false;
}

bool ICharacter::CheckHitRightWall(IStage* stage)
{
	if (!stage) return false;

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

bool ICharacter::CheckHitLeftWall(IStage* stage)
{
	if (!stage) return false;

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

bool ICharacter::CheckHitEnemy(IEnemy* enemy)
{
	if (!enemy) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height,
		enemy->GetPosition(), enemy->GetWidth(), enemy->GetHeight()) && !m_InvincibleFlag)
	{
		m_Life--;
		return true;
	}
	return false;
}

bool ICharacter::CheckHitItem(IItem* item)
{
	if (!item) return false;

	if (m_Position.x + (float)m_Width > item->GetPosition().x &&
		m_Position.x < item->GetPosition().x + (float)item->GetWidth() &&
		m_Position.y + (float)m_Height > item->GetPosition().y &&
		m_Position.y < item->GetPosition().y + (float)item->GetHeight())
	{
		item->SetActive(false);

		return true;
	}

	return false;
}

bool ICharacter::CheckHitSwitch(ISwitch* sw)
{
	namespace keyboard = vivid::keyboard;

	bool switch_on_flag = keyboard::Trigger(keyboard::KEY_ID::DOWN);

	if (!sw) return false;

	if (m_Position.x + (float)m_Width > sw->GetPosition().x &&
		m_Position.x < sw->GetPosition().x + (float)sw->GetWidth() &&
		m_Position.y + (float)m_Height > sw->GetPosition().y &&
		m_Position.y < sw->GetPosition().y + (float)sw->GetHeight())
	{
		if (sw->GetSwitchID() == SWITCH_ID::FLOOR_SWITCH && switch_on_flag)
		{
			sw->OnPress();
		}

		return true;
	}

	return false;
}

bool ICharacter::CheckHitBullet(IBullet* bullet)
{
	if (!bullet) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height,
		bullet->GetPosition(), bullet->GetWidth(), bullet->GetHeight()) && !m_InvincibleFlag)
	{
		m_Life--;

		bullet->SetActiveFlag(false);

		return true;
	}

	return false;
}

CHARACTER_ID ICharacter::GetCharacterID(void)
{
	return m_CharacterID;
}

CHARACTER_CATEGORY ICharacter::GetCategory(void)
{
	return m_Category;
}

vivid::Vector2 ICharacter::GetPosition(void)
{
	return m_Position;
}

float ICharacter::GetPositionX(void)
{
	return m_Position.x;
}

void ICharacter::SetPosition(const vivid::Vector2 position)
{
	m_Position = position;
}

int ICharacter::GetWidth(void)
{
	return m_Width;
}

int ICharacter::GetHeight(void)
{
	return m_Height;
}

float ICharacter::GetGravity(void)
{
	return m_Gravity;
}

void ICharacter::SetGravity(float gravity)
{
	m_Gravity = gravity;
}

vivid::Vector2 ICharacter::GetCenterPosition(void)
{
	return m_Position + vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f);
}

bool ICharacter::GetGravityChange(void)
{
	return m_GravityChange;
}

void ICharacter::SetGravityChange(bool gravity)
{
	m_GravityChange = gravity;
}

bool ICharacter::CheckHitGoal(CGoal& goal)
{
	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height,
		goal.GetPosition(), goal.GetWidth(), goal.GetHeight()))
	{
		return true;
	}
	return false;

}

void ICharacter::JumpUp(IItem* item)
{
	if (!item) return;

	if (CheckHitItem(item))
	{
		if (item->GetItemID() == ITEM_ID::JUMP_UP_ITEM)
		{
			m_JumpUp = true;
			m_JumpUpTimer = m_jump_up_max_time;
			m_Jump.y = m_jump_up_power;
		}
	}

	if (m_JumpUp)
	{
		if (--m_JumpUpTimer < 0.0f)
		{
			m_Jump.y = m_jump_power;
			m_JumpUp = false;
		}
	}

}

void ICharacter::Invincible(IItem* item)
{
	if (!item) return;

	if (CheckHitItem(item))
	{
		if (item->GetItemID() == ITEM_ID::INVINCIBLE_ITEM)
		{
			m_InvincibleFlag = true;
			m_InvincibleTimer = m_invincible_max_time;
		}
	}

	if (m_InvincibleFlag)
	{
		if (--m_InvincibleTimer < 0.0f)
		{
			m_InvincibleFlag = false;
		}
	}

}

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

bool ICharacter::GetActive(void)
{
	return m_Active;
}

void ICharacter::SetActive(bool active)
{
	m_Active = active;
}

int ICharacter::GetMaxLife(void)
{
	return m_MaxLife;
}

int ICharacter::GetLife(void)
{
	return m_Life;
}

void ICharacter::Alive(void)
{
}

void ICharacter::Dead(void)
{
}
