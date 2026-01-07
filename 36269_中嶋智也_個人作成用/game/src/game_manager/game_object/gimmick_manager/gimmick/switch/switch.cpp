#include "switch.h"

const int	CSwitch::m_width = 100.0f;
const int	CSwitch::m_height = 40.0f;

CSwitch::CSwitch(void)
	: IGimmick(m_width, m_height, GIMMICK_ID::SWITCH)
{
}

void CSwitch::Draw(void)
{
}
