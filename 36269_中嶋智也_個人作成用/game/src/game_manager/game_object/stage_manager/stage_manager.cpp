#include "stage_manager.h"
#include "../character_manager/character_manager.h"
#include "../enemy_manager/enemy_manager.h"
#include "../switch_manager/switch_manager.h"
#include "../bullet_manager/bullet_manager.h"
#include "stage/short_floor/short_floor.h"
#include "stage/long_floor/long_floor.h"
#include "stage/repulsion_floor/repulsion_floor.h"
#include "stage/move_floor/move_floor.h"
#include "stage/fall_floor/fall_floor.h"
#include "stage/reverse_move_floor/reverse_move_floor.h"
#include "../../../utility/csv_loader/csv_loader.h"

CStageManager& CStageManager::GetInstance(void)
{
	static CStageManager instance;

	return instance;
}

void CStageManager::Initialize(void)
{
	m_StageList.clear();
	m_StageTable.clear();

	DeployStage();
}

void CStageManager::Update(void)
{
	UpdateStageTable();

	UpdateStage();
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
	case STAGE_ID::SHORT_FLOOR: stage = new CShortFloor(); break;
	case STAGE_ID::LONG_FLOOR: stage = new CLongFloor(); break;
	case STAGE_ID::REPULSION_FLOOR:	stage = new CRepulsionFloor(); break;
	case STAGE_ID::MOVE_FLOOR: stage = new CMoveFloor(); break;
	case STAGE_ID::FALL_FLOOR: stage = new CFallFloor(); break;
	case STAGE_ID::REVERSE_MOVE_FLOOR: stage = new CReveseMoveFloor(); break;
	}

	if (!stage)	return;

	stage->Initialize(position);

	m_StageList.push_back(stage);
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

void CStageManager::ToggleAllSwitch(void)
{
	m_AllSwitchOn = !m_AllSwitchOn;
}

bool CStageManager::IsAllSwitchOn(void) const
{
	return m_AllSwitchOn;
}

void CStageManager::MoveChange(ISwitch* sw)
{
	if (!sw) return;

	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		(*it)->MoveChange(sw);
		++it;
	}
}

CStageManager::CStageManager(void)
	: m_AllSwitchOn(false)
{
}

void CStageManager::DeployStage(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\stage_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		STAGE_TABLE_DATA t;
		t.id = (STAGE_ID)csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::Y);
		m_StageTable.push_back(t);
	}

	csv_loader.Unload();
}

void CStageManager::UpdateStageTable(void)
{
	if (m_StageTable.empty())return;

	STAGE_TABLE_LIST::iterator it = m_StageTable.begin();
	STAGE_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);

	m_StageTable.erase(it);
}

void CStageManager::UpdateStage(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		IStage* stage = (IStage*)(*it);
		stage->Update();
		CCharacterManager& character_manager = CCharacterManager::GetInstance();

		character_manager.CheckHitRightWall(stage);
		character_manager.CheckHitLeftWall(stage);
		character_manager.CheckHitCeiling(stage);
		character_manager.Jump(stage);
		character_manager.ChangeGravity(stage);
		character_manager.OnGround(stage);
		character_manager.FallStage(stage);
		CEnemyManager::GetInstance().OnGround(stage);
		CBulletManager::GetInstance().CheckHitStage(stage);

		++it;
	}
}
