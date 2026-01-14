#include "floor_switch.h"

const int	CFloorSwitch::m_width = 100;
const int	CFloorSwitch::m_height = 40;

CFloorSwitch::CFloorSwitch(void)
	: ISwitch(m_width, m_height, SWITCH_ID::FLOOR_SWITCH)
{
}

void CFloorSwitch::Draw(void)
{
	vivid::DrawTexture("data\\enemy_a.png", m_Position, 0xff8eff8e);
}
