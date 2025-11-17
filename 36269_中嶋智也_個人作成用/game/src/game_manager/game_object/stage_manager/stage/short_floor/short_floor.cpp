#include "short_floor.h"

const int CShortFloor::m_width = 300;
const int CShortFloor::m_height = 64;

CShortFloor::CShortFloor(void)
	: IStage(m_width, m_height, STAGE_ID::SHORT_FLOOR)
{
}

CShortFloor::~CShortFloor(void)
{
}

void CShortFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);

	m_Position = position;
}

void CShortFloor::Draw(void)
{
	vivid::DrawTexture("data\\short_floor.png", m_Position, 0xff000000);
}
