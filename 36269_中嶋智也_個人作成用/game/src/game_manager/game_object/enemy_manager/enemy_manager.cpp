#include "enemy_manager.h"
#include "enemy/enemy_a/enemy_a.h"
#include "enemy/enemy_b/enemy_b.h"
#include "enemy/enemy_c/enemy_c.h"
#include "../character_manager/character_manager.h"
#include "../../../utility/csv_loader/csv_loader.h"

CEnemyManager& CEnemyManager::GetInstance(void)
{
	static CEnemyManager instance;

	return instance;
}

void CEnemyManager::Initialize(void)
{
	m_EnemyList.clear();
	m_EnemyTable.clear();
	
	DeployEnemy();
}

void CEnemyManager::Update(void)
{
	UpdateEnemyTable();

	UpdateEnemy();
}

void CEnemyManager::Draw(void)
{
	if (m_EnemyList.empty()) return;

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
	if (m_EnemyList.empty()) return;

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
	case ENEMY_ID::ENEMYB: enemy = new CEnemyB(); break;
	case ENEMY_ID::ENEMYC: enemy = new CEnemyC(); break;
	}

	if (!enemy) return;

	enemy->Initialize(position);
	m_EnemyList.push_back(enemy);
}

bool CEnemyManager::OnGround(IStage* stage)
{
	if (!stage) return false;

	bool any_grounded = false;

	if (m_EnemyList.empty()) return false;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			any_grounded = true;
		++it;
	}
	return any_grounded;
}

CEnemyManager::CEnemyManager(void)
{
}

void CEnemyManager::DeployEnemy(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\enemy_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		ENEMY_TABLE_DATA t;
		t.id = (ENEMY_ID)csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::Y);
		m_EnemyTable.push_back(t);
	}
	
	// ‰ð•ú
	csv_loader.Unload();
}

void CEnemyManager::UpdateEnemyTable(void)
{
	if (m_EnemyTable.empty()) return;

	ENEMY_TABLE_LIST::iterator it = m_EnemyTable.begin();
	ENEMY_TABLE_DATA t = *it;

	vivid::Vector2 position((float)(t.x), (float)(t.y));
	Create(t.id, position);
	m_EnemyTable.erase(it);
}

void CEnemyManager::UpdateEnemy(void)
{
	if (m_EnemyList.empty()) return;

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
