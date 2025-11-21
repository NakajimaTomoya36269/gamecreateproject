#include "enemy_manager.h"
#include "enemy/enemy_a/enemy_a.h"
#include "../character_manager/character_manager.h"

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

		CCharacterManager::GetInstance().CheckHitEnemy(enemy);

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

bool CEnemyManager::OnGround(IStage* stage)
{
	if (!stage) return false;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			return true;
		++it;
	}
	return false;
}

void CEnemyManager::MoveArea(IStage* stage)
{
	if (!stage) return;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		if (OnGround(stage))
		{
			(*it)->MoveArea(stage);
			return;
		}
		++it;
	}
}

CEnemyManager::CEnemyManager(void)
{
}
