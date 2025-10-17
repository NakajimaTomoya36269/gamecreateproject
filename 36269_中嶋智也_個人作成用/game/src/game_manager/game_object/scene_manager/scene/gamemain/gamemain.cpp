#include "gamemain.h"
#include "../../../character_manager/character_manager.h"

CGamemain::CGamemain(void)
{
}

void CGamemain::Initialize(void)
{
	CCharacterManager& character_manager = CCharacterManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
}

void CGamemain::Update(void)
{
	CCharacterManager::GetInstance().Update();
}

void CGamemain::Draw(void)
{
	CCharacterManager::GetInstance().Draw();
}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
}
