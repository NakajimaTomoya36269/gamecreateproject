#include "game_manager.h"
#include "game_object/game_object.h"

CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;

	return instance;
}

void CGameManager::Initialize(void)
{
}

void CGameManager::Update(void)
{
}

void CGameManager::Draw(void)
{
}

void CGameManager::Finalize(void)
{
}
