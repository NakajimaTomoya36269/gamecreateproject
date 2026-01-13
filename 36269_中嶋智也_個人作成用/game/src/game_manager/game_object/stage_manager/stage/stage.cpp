#include "stage.h"
#include "../../character_manager/character_manager.h"
#include "../../box_collider/box_collider.h"

const float IStage::m_scroll_speed = 60.0f;
const float IStage::m_friction = 0.9f;

IStage::IStage(int width, int height, STAGE_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_StageID(id)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
{
}

void IStage::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

void IStage::Update(void)
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

void IStage::Draw(void)
{
}

void IStage::Finalize(void)
{
}

void IStage::MoveChange(IGimmick* gimmick)
{
}

int IStage::GetWidth(void)
{
	return m_Width;
}

int IStage::GetHeight(void)
{
	return m_Height;
}

vivid::Vector2 IStage::GetPosition(void)
{
	return m_Position;
}

STAGE_ID IStage::GetStageID(void)
{
	return m_StageID;
}

bool IStage::CheckHitCharacter(ICharacter* character, float& position_x)
{
	if (!character) return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_Width, m_Height,
		character->GetPosition(), character->GetWidth(), character->GetHeight()))
	{
		if (m_Velocity.x > 0.0f && position_x + (float)character->GetWidth() < m_Position.x)
		{
			position_x = m_Position.x - (float)character->GetWidth();

			m_Velocity.x = 0.0f;

			return true;
		}
		if (m_Velocity.x < 0.0f && position_x > m_Position.x + (float)m_Width)
		{
			position_x = m_Position.x + (float)m_Width;

			m_Velocity.x = 0.0f;

			return true;
		}
	}

	return false;
}
