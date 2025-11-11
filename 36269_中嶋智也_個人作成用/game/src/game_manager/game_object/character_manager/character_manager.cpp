#include "character_manager.h"
#include "character/player/player.h"

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

		CStageManager::GetInstance().CheckHitCharacter(character, character->GetPositionX());

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

bool CCharacterManager::OnGround(CStage* stage)
{
	if (m_CharacterList.empty())return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			return true;
		++it;
	}
	return false;
}

void CCharacterManager::CheckHitCeiling(CStage* stage)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitCeiling(stage))
			return;
		++it;
	}
}

void CCharacterManager::CheckHitRightWall(CStage* stage)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitRightWall(stage))
			return;
		++it;
	}
}

void CCharacterManager::CheckHitLeftWall(CStage* stage)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitLeftWall(stage))
			return;
		++it;
	}
}

void CCharacterManager::Jump(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Jump();
		++it;
	}
}

void CCharacterManager::ChangeGravity(void)
{
	if (m_CharacterList.empty())return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->ChangeGravity();
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
