#include "item_manager.h"
#include "item/item.h"
#include "item/jump_up_item/jump_up_item.h"
#include "../character_manager/character_manager.h"

CItemManager& CItemManager::GetInstance(void)
{
	static CItemManager instance;

	return instance;
}

void CItemManager::Initilaize(void)
{
	m_ItemList.clear();
}

void CItemManager::Update(void)
{
	ITEM_LIST::iterator it = m_ItemList.begin();
	ITEM_LIST::iterator end = m_ItemList.end();

	while (it != end)
	{
		IItem* item = (IItem*)(*it);

		item->Update();
		CCharacterManager::GetInstance().CheckHitItem(item);
		CCharacterManager::GetInstance().JumpUp(item);

		if (!item->GetActive())
		{
			item->Finalize();

			delete item;

			it = m_ItemList.erase(it);

			continue;
		}
		it++;
	}
}

void CItemManager::Draw(void)
{
	ITEM_LIST::iterator it = m_ItemList.begin();
	ITEM_LIST::iterator end = m_ItemList.end();

	while (it != end)
	{
		(*it)->Draw();

		it++;
	}
}

void CItemManager::Finalize(void)
{
	ITEM_LIST::iterator it = m_ItemList.begin();
	ITEM_LIST::iterator end = m_ItemList.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete (*it);

		it++;
	}
	m_ItemList.clear();
}

void CItemManager::Create(ITEM_ID id, const vivid::Vector2& position)
{
	IItem* item = nullptr;

	switch (id)
	{
	case ITEM_ID::JUMP_UP_ITEM: item = new CJumpUpItem(); break;
	}

	if (!item) return;

	item->Initialize(position);
	m_ItemList.push_back(item);
}

CItemManager::CItemManager(void)
{
}
