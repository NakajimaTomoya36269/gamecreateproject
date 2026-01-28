#include "game_manager.h"
#include "game_object/game_object.h"

CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;

	return instance;
}

void CGameManager::Initialize(void)
{
	CSceneManager::GetInstance().Initialize();
}

void CGameManager::Update(void)
{
	CSceneManager::GetInstance().Update();
}

void CGameManager::Draw(void)
{
	CSceneManager::GetInstance().Draw();

	CSceneManager::GetInstance().DrawSceneEffect();
}

void CGameManager::Finalize(void)
{
	CSceneManager::GetInstance().Finalize();
}
