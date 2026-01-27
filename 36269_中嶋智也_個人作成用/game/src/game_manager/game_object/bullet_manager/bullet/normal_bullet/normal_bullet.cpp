#include "normal_bullet.h"

const int	CNormalBullet::m_width = 40;
const int	CNormalBullet::m_height = 40;
const float	CNormalBullet::m_radius = 20.0f;

CNormalBullet::CNormalBullet(void)
	: IBullet(m_width, m_height, m_radius, BULLET_ID::NORMAL_BULLET)
{
}

void CNormalBullet::Draw(void)
{
	vivid::DrawTexture("data\\ball.png", m_Position, 0xffffffff, m_Rect, 
						m_Anchor,m_Scale, m_Rotation);
}
