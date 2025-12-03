#include "repulsion_floor.h"

const int CRepulsionFloor::m_width = 100;
const int CRepulsionFloor::m_height = 100;

CRepulsionFloor::CRepulsionFloor(void)
	: IStage(m_width, m_height, STAGE_ID::REPULSION_FLOOR)
{
}

void CRepulsionFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);
	m_Position = position;
}

void CRepulsionFloor::Draw(void)
{
	vivid::DrawTexture("data\\repulsion_floor.png", m_Position);
}
