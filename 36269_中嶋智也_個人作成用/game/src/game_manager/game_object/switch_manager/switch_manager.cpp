#include "../character_manager/character_manager.h"
#include "../stage_manager/stage_manager.h"
#include "switch_manager.h"
#include "switch/floor_switch/floor_switch.h"

CSwitchManager& CSwitchManager::GetInstance(void)
{
	static CSwitchManager instance;

	return instance;
}

void CSwitchManager::Initialize(void)
{
	m_SwitchList.clear();
}

void CSwitchManager::Update(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		ISwitch* sw = (ISwitch*)(*it);

		sw->Update();
		CCharacterManager::GetInstance().CheckHitSwitch(sw);
		CStageManager::GetInstance().MoveChange(sw);

		it++;
	}
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
