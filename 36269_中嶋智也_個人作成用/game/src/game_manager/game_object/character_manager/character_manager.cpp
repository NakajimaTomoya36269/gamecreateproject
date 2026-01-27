#include "character_manager.h"
#include "character/player/player.h"
#include "../enemy_manager/enemy_manager.h"

CCharacterManager& CCharacterManager::GetInstance(void)
{
	static CCharacterManager instance;

	return instance;
}

void CCharacterManager::Initialize(void)
{
	m_CharacterList.clear();
}

void CCharacterManager::Update(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		ICharacter* character = (ICharacter*)(*it);

		character->Update();
		CEnemyManager::GetInstance().Attack(character);

		if (!character->GetActive())
		{
			character->Finalize();

			delete character;

			it = m_CharacterList.erase(it);
			continue;
		}
		++it;
	}
}

void CCharacterManager::Draw(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Draw();
		++it;
	}
}

void CCharacterManager::Finalize(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		++it;
	}
	m_CharacterList.clear();
}

void CCharacterManager::Create(CHARACTER_ID id, const vivid::Vector2& position)
{
	ICharacter* character = nullptr;

	switch (id)
	{
	case CHARACTER_ID::PLAYER: character = new CPlayer();	break;
	}

	if (!character) return;

	character->Initialize(position);
	m_CharacterList.push_back(character);
}

bool CCharacterManager::OnGround(IStage* stage)
{
	if (!stage)return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	bool anyGrounded = false;

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			anyGrounded = true;
		++it;
	}
	return anyGrounded;
}

bool CCharacterManager::CheckHitCeiling(IStage* stage)
{
	if (!stage)return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitCeiling(stage))
			return true;
		++it;
	}
	return false;
}
bool CCharacterManager::CheckHitRightWall(IStage* stage)
{
	if (!stage)return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitRightWall(stage))
			return true;
		++it;
	}
	return false;
}

bool CCharacterManager::CheckHitLeftWall(IStage* stage)
{
	if (!stage)return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitLeftWall(stage))
			return true;
		++it;
	}
	return false;
}

void CCharacterManager::CheckHitEnemy(IEnemy* enemy)
{
	if (!enemy)return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitEnemy(enemy))
			return;
		++it;
	}
}

void CCharacterManager::Jump(IStage* stage)
{
	if (!stage)return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Jump(stage);
		++it;
	}
}

void CCharacterManager::ChangeGravity(IStage* stage)
{
	if (!stage)return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->ChangeGravity(stage);
		++it;
	}
}

bool CCharacterManager::CheckHitGoal(CGoal& goal)
{
	if (m_CharacterList.empty())return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitGoal(goal))
			return true;
		++it;
	}
	return false;
}

void CCharacterManager::CheckHitItem(IItem* item)
{
	if (!item) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitItem(item))
			return;
		++it;
	}
}

void CCharacterManager::CheckHitBullet(IBullet* bullet)
{
	if (!bullet) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitBullet(bullet))
			return;
		it++;
	}
}

void CCharacterManager::JumpUp(IItem* item)
{
	if (!item) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->JumpUp(item);

		++it;
	}
}

void CCharacterManager::Invincible(IItem* item)
{
	if (!item) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Invincible(item);

		++it;
	}
}

void CCharacterManager::CheckHitSwitch(ISwitch* sw)
{
	if (!sw) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->CheckHitSwitch(sw);

		++it;
	}
}

void CCharacterManager::FallStage(IStage* stage)
{
	if (!stage) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->FallStage(stage);

		it++;
	}
}

void CCharacterManager::CheckHitCharacter(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if (CStageManager::GetInstance().CheckHitCharacter((*it), (*it)->GetPositionX()))
		{
			return;
		}
		++it;
	}
}
