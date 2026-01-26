#include "reverse_move_floor.h"
#include "../../../switch_manager/switch/switch.h"

const int	CReveseMoveFloor::m_width = 300;
const int	CReveseMoveFloor::m_height = 64;
const float CReveseMoveFloor::m_move_speed = 60.0f;

CReveseMoveFloor::CReveseMoveFloor(void)
	: IStage(m_width, m_height, STAGE_ID::REVERSE_MOVE_FLOOR)
	, m_StartPosition(vivid::Vector2(0.0f, 0.0f))
	, m_MoveVelocity(vivid::Vector2(0.0f, 0.0f))
	, m_ChangeMove(false)
	, m_ActiveFlag(false)

{
}

void CReveseMoveFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);
	m_StartPosition = m_Position;
	m_MoveVelocity = vivid::Vector2(0.0f, 0.0f);
	m_ChangeMove = false;
	m_ActiveFlag = false;
}

void CReveseMoveFloor::Update(void)
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

	if (!m_ActiveFlag)
	{
		if (m_Position.x > m_StartPosition.x + (float)m_Width)
		{
			m_ChangeMove = true;
		}
		if (m_Position.x < m_StartPosition.x)
		{
			m_ChangeMove = false;
		}

		if (m_ChangeMove)
		{
			m_MoveVelocity.x = -m_move_speed;
		}
		else
		{
			m_MoveVelocity.x = m_move_speed;
		}
	}
	else
	{
		m_MoveVelocity.x = 0.0f;
	}

	m_Position += m_Velocity * vivid::GetDeltaTime();
	m_StartPosition += m_Velocity * vivid::GetDeltaTime();

	m_Velocity.x *= m_friction;

	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();
	m_MoveVelocity.x *= m_friction;
}

void CReveseMoveFloor::Draw(void)
{
	vivid::DrawTexture("data\\move_floor.png", m_Position);
}

void CReveseMoveFloor::Finalize(void)
{
	IStage::Finalize();
}

void CReveseMoveFloor::MoveChange(ISwitch* sw)
{
	if (!sw) return;

	m_ActiveFlag = sw->GetOnFlag();
}
