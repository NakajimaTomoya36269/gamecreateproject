#include "../character_manager/character_manager.h"
#include "../stage_manager/stage_manager.h"
#include "switch_manager.h"
#include "switch/floor_switch/floor_switch.h"
#include "../../../utility/csv_loader/csv_loader.h"

CSwitchManager& CSwitchManager::GetInstance(void)
{
	static CSwitchManager instance;

	return instance;
}

void CSwitchManager::Initialize(void)
{
	m_SwitchList.clear();
	m_SwitchTable.clear();

	DeploySwitch();
}

void CSwitchManager::Update(void)
{
	UpdateSwitchTable();

	UpdateSwitch();
}

void CSwitchManager::Draw(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		(*it)->Draw();

		it++;
	}
}

void CSwitchManager::Finalize(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		it++;
	}
	m_SwitchList.clear();
}

void CSwitchManager::Create(SWITCH_ID id, const vivid::Vector2& position)
{
	ISwitch* sw = nullptr;

	switch (id)
	{
	case SWITCH_ID::FLOOR_SWITCH: sw = new CFloorSwitch(); break;
	}

	if (!sw) return;

	sw->Initialize(position);
	m_SwitchList.push_back(sw);
}

CSwitchManager::CSwitchManager(void)
{
}

void CSwitchManager::DeploySwitch(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\switch_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		SWITCH_TABLE_DATA t;
		t.id = (SWITCH_ID)csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::Y);

		m_SwitchTable.push_back(t);
	}

	csv_loader.Unload();
}

void CSwitchManager::UpdateSwitchTable(void)
{
	if (m_SwitchTable.empty()) return;

	SWITCH_TABLE_LIST::iterator it = m_SwitchTable.begin();
	SWITCH_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);

	m_SwitchTable.erase(it);
}

void CSwitchManager::UpdateSwitch(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		ISwitch* sw = (ISwitch*)(*it);

		sw->Update();
		CCharacterManager::GetInstance().CheckHitSwitch(sw);

		it++;
	}
}
