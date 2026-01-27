#include "enemy_c.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../character_manager/character/character.h"

const int   CEnemyC::m_width = 40;
const int   CEnemyC::m_height = 40;
const float CEnemyC::m_radius = 20.0f;
const int   CEnemyC::m_max_life = 1;
const float CEnemyC::m_attack_time = 180.0f;

CEnemyC::CEnemyC(void)
    : IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYC)
    , m_AttackTimer(0.0f)
    , m_Attacked(false)
{
}

void CEnemyC::Initialize(const vivid::Vector2& position)
{
    IEnemy::Initialize(position);
    m_AttackTimer = m_attack_time;
    m_Attacked = false;
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
    if (!character) return;

    if (++m_AttackTimer > m_attack_time)
    {
        m_Attacked = true;
    }

    float distance = fabs(character->GetPosition().x - m_Position.x);
    const float attack_range = 400.0f;

    if (m_Attacked && distance <= attack_range)
    {
        CBulletManager& bullet_manager = CBulletManager::GetInstance();

        vivid::Vector2 v = character->GetCenterPosition() - GetCenterPosition();
        float dir = atan2(v.y, v.x);

        bullet_manager.Create(BULLET_ID::NORMAL_BULLET, GetCenterPosition(),
                                dir, 3.0f);
        m_AttackTimer -= m_attack_time;

        m_Attacked = false;
    }
}
