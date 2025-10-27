#include "stage_manager.h"
#include "../character_manager/character_manager.h"

CStageManager& CStageManager::GetInstance(void)
{
	static CStageManager instance;

	return instance;
}

void CStageManager::Initialize(void)
{
	m_StageList.clear();
}

void CStageManager::Update(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		(*it)->Update();

		++it;
	}
}

void CStageManager::Draw(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();
	
	while (it != end)
	{
		(*it)->Draw();

		++it;
	}
}

void CStageManager::Finalize(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();
	
	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		++it;
	}
	m_StageList.clear();
}

void CStageManager::Create(const vivid::Vector2& position)
{
	CStage* stage = nullptr;

	stage = new CStage();

	if (!stage)	return;

	stage->Initialize(position);

	m_StageList.push_back(stage);
}

bool CStageManager::GetIsGround(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if (CCharacterManager::GetInstance().OnGround((*it)))
		{
			return true;
		}
		++it;
	}

	return false;
}

CStageManager::CStageManager(void)
{
}
