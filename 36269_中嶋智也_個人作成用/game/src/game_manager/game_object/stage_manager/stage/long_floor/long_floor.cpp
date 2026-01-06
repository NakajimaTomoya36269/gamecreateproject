#include "long_floor.h"

const int CLongFloor::m_width = 1500;
const int CLongFloor::m_height = 64;

CLongFloor::CLongFloor(void)
	: IStage(m_width, m_height, STAGE_ID::LONG_FLOOR)
{
}

CLongFloor::~CLongFloor(void)
{
}

void CLongFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);

	m_Position = position;
}

void CLongFloor::Draw(void)
{
	vivid::DrawTexture("data\\long_floor.png", m_Position, 0xff000066);
}
