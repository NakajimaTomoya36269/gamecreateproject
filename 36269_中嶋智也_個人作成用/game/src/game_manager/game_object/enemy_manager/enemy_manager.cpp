#include "enemy_manager.h"
#include "enemy/enemy_a/enemy_a.h"

CEnemyManager& CEnemyManager::GetInstance(void)
{
	static CEnemyManager instance;

	return instance;
}

void CEnemyManager::Initialize(void)
{
	m_EnemyList.clear();
}

void CEnemyManager::Update(void)
{
	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		IEnemy* enemy = (IEnemy*)(*it);

		enemy->Update();

		if (!enemy->GetActive())
		{
			enemy->Finalize();

			delete enemy;

			it = m_EnemyList.erase(it);
			continue;
		}
		++it;
	}
}

void CEnemyManager::Draw(void)
{
	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		(*it)->Draw();

		++it;
	}
}

void CEnemyManager::Finalize(void)
{
	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		++it;
	}
	m_EnemyList.clear();
}

void CEnemyManager::Create(ENEMY_ID id, const vivid::Vector2& position)
{
	IEnemy* enemy = nullptr;

	switch (id)
	{
	case ENEMY_ID::ENEMYA: enemy = new CEnemyA(); break;
	case ENEMY_ID::ENEMYB:	break;
	}

	if (!enemy) return;

	enemy->Initialize(position);
	m_EnemyList.push_back(enemy);
}

void CEnemyManager::OnGround(CStage* stage)
{
	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			return;
		++it;
	}
}

CEnemyManager::CEnemyManager(void)
{
}
