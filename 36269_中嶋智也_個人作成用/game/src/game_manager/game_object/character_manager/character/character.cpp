#include "character.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"

const float ICharacter::m_move_speed = 0.9f;
const float ICharacter::m_gravity_speed = 0.5f;

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
	, m_IsGround(false)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
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
		if (m_Position.y + m_Height >= stage->GetPosition().y)
		{
			m_Position.y = (float)(stage->GetPosition().y + stage->GetHeight() - m_Height);

			m_Gravity = 0.0f;

			return true;
		}
	}
	else
	{
		m_Velocity.y += m_Gravity;
	}

	return false;
}

void ICharacter::Jump(void)
{
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
	Jump();
}

void ICharacter::Dead(void)
{
}
