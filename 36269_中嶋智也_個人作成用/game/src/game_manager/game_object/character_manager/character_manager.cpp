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
	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		ICharacter* character = (ICharacter*)(*it);

		character->Update();
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
	case CHARACTER_ID::ENEMYA: break;
	}

	if (!character) return;

	character->Initialize(position);
	m_CharacterList.push_back(character);
}
