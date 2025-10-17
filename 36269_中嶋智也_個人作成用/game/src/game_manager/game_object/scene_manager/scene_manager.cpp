#include "scene_manager.h"

CSceneManager& CSceneManager::GetInstance(void)
{
	static CSceneManager instance;

	return instance;
}

void CSceneManager::Initialize(void)
{
}

void CSceneManager::Update(void)
{
}

void CSceneManager::Draw(void)
{
}

void CSceneManager::Finalize(void)
{
}

CSceneManager::CSceneManager(void)
{
}
