#include "gimmick_manager.h"
#include "gimmick/gimmick.h"
#include "gimmick/switch/switch.h"
#include "../character_manager/character_manager.h"
#include "../stage_manager/stage_manager.h"

CGimmickManager& CGimmickManager::GetInstance(void)
{
	static CGimmickManager instance;

	return instance;
}

void CGimmickManager::Initialize(void)
{
	m_GimmickList.clear();
}

void CGimmickManager::Update(void)
{
	GIMMICK_LIST::iterator it = m_GimmickList.begin();
	GIMMICK_LIST::iterator end = m_GimmickList.end();

	while (it != end)
	{
		IGimmick* gimmick = (IGimmick*)(*it);

		gimmick->Update();
		CCharacterManager::GetInstance().CheckHitGimmick(gimmick);
		CStageManager::GetInstance().MoveChange(gimmick);

		it++;
	}
}

void CGimmickManager::Draw(void)
{
	GIMMICK_LIST::iterator it = m_GimmickList.begin();
	GIMMICK_LIST::iterator end = m_GimmickList.end();

	while (it != end)
	{
		(*it)->Draw();

		it++;
	}
}

void CGimmickManager::Finalize(void)
{
	GIMMICK_LIST::iterator it = m_GimmickList.begin();
	GIMMICK_LIST::iterator end = m_GimmickList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		it++;
	}
	m_GimmickList.clear();
}

void CGimmickManager::Create(GIMMICK_ID id, const vivid::Vector2& position)
{
	IGimmick* gimmick = nullptr;

	switch (id)
	{
	case GIMMICK_ID::SWITCH: gimmick = new CSwitch(); break;
	}

	if (!gimmick) return;

	gimmick->Initialize(position);
	m_GimmickList.push_back(gimmick);
}

CGimmickManager::CGimmickManager(void)
{
}
