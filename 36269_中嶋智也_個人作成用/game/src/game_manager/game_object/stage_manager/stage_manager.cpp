#include "stage_manager.h"
#include "../character_manager/character_manager.h"
#include "../enemy_manager/enemy_manager.h"
#include "stage/short_floor/short_floor.h"
#include "stage/long_floor/long_floor.h"

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
		IStage* stage = (IStage*)(*it);
		stage->Update();
		CCharacterManager::GetInstance().CheckHitRightWall(stage);
		CCharacterManager::GetInstance().CheckHitLeftWall(stage);
		CCharacterManager::GetInstance().CheckHitCeiling(stage);
		CCharacterManager::GetInstance().Jump(stage);
		CCharacterManager::GetInstance().ChangeGravity(stage);
		CEnemyManager::GetInstance().OnGround(stage);
		CEnemyManager::GetInstance().MoveArea(stage);

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

void CStageManager::Create(STAGE_ID id, const vivid::Vector2& position)
{
	IStage* stage = nullptr;

	switch (id)
	{
	case STAGE_ID::SHORT_FLOOR: stage = new CShortFloor();	break;
	case STAGE_ID::LONG_FLOOR:	stage = new CLongFloor();	break;
	}

	if (!stage)	return;

	stage->Initialize(position);

	m_StageList.push_back(stage);
}

void CStageManager::OnGround(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if (CCharacterManager::GetInstance().OnGround((*it)))
		{
			return;
		}
		++it;
	}

	return;
}

void CStageManager::EnemyOnGround(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if (CEnemyManager::GetInstance().OnGround((*it)))
		{
			return;
		}
		++it;
	}

	return;
}

bool CStageManager::CheckHitCharacter(ICharacter* character, float&& position_x)
{
	if (!character) return false;

	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if ((*it)->CheckHitCharacter(character, position_x))
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
