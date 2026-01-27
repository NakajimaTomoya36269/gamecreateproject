#include "bullet_manager.h"
#include "bullet/bullet.h"
#include "bullet/normal_bullet/normal_bullet.h"
#include "../stage_manager/stage_manager.h"
#include "../character_manager/character_manager.h"

CBulletManager& CBulletManager::GetInstance(void)
{
	static CBulletManager instance;

	return instance;
}

void CBulletManager::Initialize(void)
{
	m_BulletList.clear();
}

void CBulletManager::Update(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		IBullet* bullet = (IBullet*)(*it);

		bullet->Update();
		CCharacterManager::GetInstance().CheckHitBullet(bullet);

		if (!bullet->GetActiveFlag())
		{
			bullet->Finalize();

			delete bullet;

			it = m_BulletList.erase(it);
			continue;
		}
		it++;
	}
}

void CBulletManager::Draw(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		(*it)->Draw();

		it++;
	}
}

void CBulletManager::Finalize(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		it++;
	}

	m_BulletList.clear();
}

void CBulletManager::Create(BULLET_ID id, const vivid::Vector2& position, float direction, float speed)
{
	IBullet* bullet = nullptr;

	switch (id)
	{
	case BULLET_ID::NORMAL_BULLET: bullet = new CNormalBullet(); break;
	}

	if (!bullet) return;

	bullet->Initialize(position, direction, speed);

	m_BulletList.push_back(bullet);
}

void CBulletManager::CheckHitStage(IStage* stage)
{
	if (!stage) return;

	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		if ((*it)->CheckHitStage(stage))
			return;

		it++;
	}
}

CBulletManager::CBulletManager(void)
{
}
