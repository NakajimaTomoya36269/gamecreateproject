#include "enemy_b.h"
#include "../../../stage_manager/stage_manager.h"

const int	CEnemyB::m_width = 40;
const int	CEnemyB::m_height = 40;
const float CEnemyB::m_radius = 20.0f;
const int	CEnemyB::m_max_life = 1;

CEnemyB::CEnemyB(void)
	: IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYB)
{
}

CEnemyB::~CEnemyB(void)
{
}

void CEnemyB::Initialize(const vivid::Vector2& position)
{
	IEnemy::Initialize(position);
	m_Life = m_MaxLife = m_max_life;
}

void CEnemyB::Update(void)
{
	IEnemy::Update();
}

void CEnemyB::Draw(void)
{
	vivid::DrawTexture("data\\enemy_b.png", m_Position);
}

void CEnemyB::Finalize(void)
{
}

bool CEnemyB::OnGround(IStage* stage)
{
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Velocity.y > 0.0f && m_Position.y < stage->GetPosition().y + (float)stage->GetHeight())
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
	}
	else
	{
		if (m_Velocity.y < m_max_gravity)
			m_Velocity.y += m_Gravity;
	}	
	return false;
}

void CEnemyB::Alive(void)
{
	IEnemy::Alive();
	m_Position.y -= m_Velocity.y;
	if (m_Position.y < 0.0f || m_Position.y + m_Height >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = ENEMY_STATE::DEAD;
	}
}

void CEnemyB::Dead(void)
{
	m_Active = false;
	IEnemy::Dead();
}
