#include "character.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"

const float ICharacter::m_move_speed = 0.9f;
const float ICharacter::m_gravity_speed = 0.5f;
const float ICharacter::m_max_gravity = 30.0f;

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
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect{ 0, 0, m_Width, m_Height }
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
	m_Gravity = m_gravity_speed;
	m_State = CHARACTER_STATE::ALIVE;
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

bool ICharacter::OnGround(CStage* stage)
{
	if (!stage)return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height,
		stage->GetPosition(), stage->GetWidth(), stage->GetHeight()))
	{
		if (m_Position.y + m_Height > stage->GetPosition().y && !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;

			m_Velocity.y = 0.0f;

			return true;
		}
		else if (m_Position.y < stage->GetPosition().y + stage->GetHeight() && m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
	}
	else
	{
		if (m_Velocity.y < m_max_gravity)
			m_Velocity.y += m_Gravity;
	}

	return false;
}

void ICharacter::Jump(void)
{
}

void ICharacter::ChangeGravity(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool gravity_change_key = keyboard::Trigger(keyboard::KEY_ID::SPACE);
	bool gravity_change_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A);

	bool gravity_change = gravity_change_key || gravity_change_button;

	if (gravity_change)
	{
		m_GravityChange = !m_GravityChange;
	}
}

bool ICharacter::CheckHitCeiling(CStage* stage)
{
	if (!stage) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height, 
		stage->GetPosition(), stage->GetWidth(), stage->GetHeight()))
	{
		if (m_Position.y < stage->GetPosition().y + (float)stage->GetHeight() && !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
		 else if (m_Position.y + m_Height > stage->GetPosition().y && m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;

			m_Velocity.y = 0.0f;

			return true;
		}
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

bool ICharacter::GetGravityChange(void)
{
	return m_GravityChange;
}

void ICharacter::SetGravityChange(bool gravity)
{
	m_GravityChange = gravity;
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
	if (m_GravityChange)
	{
		m_Position.y -= m_Velocity.y;
	}
	if (!m_GravityChange)
	{
		m_Position.y += m_Velocity.y;
	}
}

void ICharacter::Dead(void)
{
}
