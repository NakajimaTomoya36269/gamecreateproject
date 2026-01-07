#include "switch.h"

const int	CSwitch::m_width = 100;
const int	CSwitch::m_height = 40;

CSwitch::CSwitch(void)
	: IGimmick(m_width, m_height, GIMMICK_ID::SWITCH)
{
}

void CSwitch::Draw(void)
{
}
