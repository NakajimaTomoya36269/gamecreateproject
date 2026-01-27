#include "enemy_c.h"

const int   CEnemyC::m_width = 40;
const int   CEnemyC::m_height = 40;
const float CEnemyC::m_radius = 20.0f;
const int   CEnemyC::m_max_life = 1;

CEnemyC::CEnemyC(void)
    :IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYC)
{
}

void CEnemyC::Initialize(const vivid::Vector2& position)
{
    IEnemy::Initialize(position);
}

void CEnemyC::Update(void)
{
    IEnemy::Update();
}

void CEnemyC::Draw(void)
{
    vivid::DrawTexture("data\\enemy_b.png", m_Position);
}

void CEnemyC::Finalize(void)
{
}

bool CEnemyC::OnGround(IStage* stage)
{
    if (!stage) return false;

    return false;
}

void CEnemyC::Attack(ICharacter* character)
{
}
