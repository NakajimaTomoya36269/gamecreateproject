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
	for (int i = 0; i < 5; i++)
	{
		CStageManager::GetInstance().Create(vivid::Vector2(i * 300.0f, 1016.0f));
		CStageManager::GetInstance().Create(vivid::Vector2(i * 300.0f, 0.0f));
	}
}

void CGamemain::Update(void)
{
	CStageManager::GetInstance().Update();
	CCharacterManager::GetInstance().Update();
	if (CStageManager::GetInstance().GetIsGround())
	{
		CCharacterManager::GetInstance().ChangeGravity();
		CCharacterManager::GetInstance().Jump();
	}
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
