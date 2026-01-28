#include "enemy_d.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../character_manager/character_manager.h"
#include "../../../../../utility/utility.h"

const int	CEnemyD::m_width = 40;
const int	CEnemyD::m_height = 40;
const float CEnemyD::m_radius = 20.0f;
const int	CEnemyD::m_max_life = 1;
const float	CEnemyD::m_attack_time = 50.0f;

CEnemyD::CEnemyD(void)
	: IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYD)
	, m_AttackTimer(0.0f)
	, m_Attacked(false)
{
}

void CEnemyD::Initialize(const vivid::Vector2& position)
{
	IEnemy::Initialize(position);
	m_AttackTimer = m_attack_time;
	m_Attacked = false;
}

void CEnemyD::Update(void)
{
	IEnemy::Update();
}

void CEnemyD::Draw(void)
{
	vivid::DrawTexture("data\\enemy_b.png", m_Position);
}

void CEnemyD::Finalize(void)
{
	IEnemy::Finalize();
}

bool CEnemyD::OnGround(IStage* stage)
{
	if (!stage) return false;

	return false;
}

void CEnemyD::Attack(ICharacter* character)
{
	if (!character) return;

	if (++m_AttackTimer > m_attack_time)
	{
		m_Attacked = true;
	}

	float dist_to_top = m_Position.y;
	float dist_to_bottom = (float)vivid::WINDOW_HEIGHT - m_Position.y;

	float distance = fabs(character->GetPosition().x - m_Position.x);
	const float attack_range = 500.0f;

	if (distance <= attack_range && m_Attacked)
	{
		CBulletManager& bullet_manager = CBulletManager::GetInstance();

		if (dist_to_top >= dist_to_bottom)
		{
			bullet_manager.Create(BULLET_ID::NORMAL_BULLET, GetCenterPosition(),
				DEG_TO_RAD(270.0f), 4.0f);
		}
		else
		{
			bullet_manager.Create(BULLET_ID::NORMAL_BULLET, GetCenterPosition(),
				DEG_TO_RAD(90.0f), 4.0f);
		}
		m_AttackTimer -= m_attack_time;

		m_Attacked = false;
	}
}
