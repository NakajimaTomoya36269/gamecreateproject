#include "bullet_manager.h"

CBulletManager& CBulletManager::GetInstance(void)
{
	static CBulletManager instance;

	return instance;
}

void CBulletManager::Initialize(void)
{
}

void CBulletManager::Update(void)
{
}

void CBulletManager::Draw(void)
{
}

void CBulletManager::Finalize(void)
{
}

void CBulletManager::Create(BULLET_ID id, const vivid::Vector2& position, float direction, float speed)
{
}

CBulletManager::CBulletManager(void)
{
}
