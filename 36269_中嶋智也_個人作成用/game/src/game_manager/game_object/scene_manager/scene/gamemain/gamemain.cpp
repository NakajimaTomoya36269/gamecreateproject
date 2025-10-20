#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"

CGamemain::CGamemain(void)
{
}

void CGamemain::Initialize(void)
{
	CCharacterManager& character_manager = CCharacterManager::GetInstance();
	CStageManager& stage_manager = CStageManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
	stage_manager.Initialize();
	stage_manager.Create(vivid::Vector2(0.0f, 1016.0f));
}

void CGamemain::Update(void)
{
	CCharacterManager::GetInstance().Update();
	CStageManager::GetInstance().Update();
}

void CGamemain::Draw(void)
{
	CCharacterManager::GetInstance().Draw();
	CStageManager::GetInstance().Draw();
}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
}
