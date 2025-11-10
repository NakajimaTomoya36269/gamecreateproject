#include "stage.h"
#include "../../character_manager/character_manager.h"
#include "../../box_collider/box_collider.h"

const int CStage::m_width = 300;
const int CStage::m_height = 64;
const float CStage::m_scroll_speed = 60.0f;
const float CStage::m_friction = 0.9f;

CStage::CStage(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
{
}

void CStage::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

void CStage::Update(void)
{
	namespace keyboard = vivid::keyboard;

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

	m_Position += m_Velocity * vivid::GetDeltaTime();

	m_Velocity.x *= m_friction;
}

void CStage::Draw(void)
{
	vivid::DrawTexture("data\\floor.png", m_Position,0xff000000);
}

void CStage::Finalize(void)
{
}

int CStage::GetWidth(void)
{
	return m_width;
}

int CStage::GetHeight(void)
{
	return m_height;
}

vivid::Vector2 CStage::GetPosition(void)
{
	return m_Position;
}

bool CStage::CheckHitCharacter(ICharacter* character, float& position_x)
{
	if (!character) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_width, m_height,
		character->GetPosition(), character->GetWidth(), character->GetHeight()))
	{
		if (m_Velocity.x > 0.0f && position_x + (float)character->GetWidth() < m_Position.x)
		{
			position_x = m_Position.x - (float)character->GetWidth();

			m_Velocity.x = 0.0f;

			return true;
		}
		if (m_Velocity.x < 0.0f && position_x > m_Position.x + (float)m_width)
		{
			position_x = m_Position.x + (float)m_width;

			m_Velocity.x = 0.0f;

			return true;
		}
	}

	return false;
}
