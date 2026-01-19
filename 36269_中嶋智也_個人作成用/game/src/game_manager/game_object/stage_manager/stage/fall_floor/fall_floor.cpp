#include "fall_floor.h"

const int	CFallFloor::m_width = 400;
const int	CFallFloor::m_height = 64;
const float CFallFloor::m_fall_speed = 60.0f;
const float CFallFloor::m_return_time = 300.0f;

CFallFloor::CFallFloor(void)
	: IStage(m_width, m_height, STAGE_ID::FALL_FLOOR)
	, m_FallVelocity(vivid::Vector2(0.0f, 0.0f))
	, m_ReturnTimer(0.0f)
	, m_Color(0xffffffff)
{
}

void CFallFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);
	
	m_FallVelocity = vivid::Vector2(0.0f, 0.0f);

	m_ReturnTimer = 0.0f;

	m_Color = 0xffffffff;
}

void CFallFloor::Update(void)
{
	IStage::Update();

	if (m_IsFalled)
	{
		m_FallVelocity.y = m_fall_speed;
	}
	else
	{
		m_FallVelocity.y = 0.0f;
		if (++m_ReturnTimer > m_return_time)
		{
			m_Position.y = m_StartPosition.y;
			m_ReturnTimer -= m_return_time;
		}
	}

	m_Position += m_FallVelocity * vivid::GetDeltaTime();
}

void CFallFloor::Draw(void)
{
	vivid::DrawTexture("data\\move_floor.png", m_Position);
}

void CFallFloor::Finalize(void)
{
	IStage::Finalize();
}
