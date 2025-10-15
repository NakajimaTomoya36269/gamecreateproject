#include "character.h"

const float ICharacter::m_move_speed = 0.9f;
const float ICharacter::m_gravity_speed = 1.0f;

ICharacter::ICharacter(int width, int height, float radius, int life,
							CHARACTER_CATEGORY category, CHARACTER_ID character_id)
	: m_Width(width)
	, m_Height(height)
	, m_Radius(radius)
	, m_Life(life)
	, m_MaxLife(life)
	, m_Category(category)
	, m_CharacterID(character_id)
	, m_Active(true)
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

float ICharacter::GetWidth(void)
{
	return m_Width;
}

float ICharacter::GetHeight(void)
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
}

void ICharacter::Dead(void)
{
}
