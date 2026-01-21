#include "item_manager.h"
#include "item/item.h"
#include "item/jump_up_item/jump_up_item.h"
#include "item/invincible_item/invincible_item.h"
#include "../character_manager/character_manager.h"
#include "../../../utility/csv_loader/csv_loader.h"

CItemManager& CItemManager::GetInstance(void)
{
	static CItemManager instance;

	return instance;
}

void CItemManager::Initialize(void)
{
	m_ItemList.clear();
	m_ItemTable.clear();

	DeployItem();
}

void CItemManager::Update(void)
{
	UpdateItemTable();

	UpdateItem();
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
	case ITEM_ID::INVINCIBLE_ITEM: item = new CInvincibleItem(); break;
	}

	if (!item) return;

	item->Initialize(position);
	m_ItemList.push_back(item);
}

CItemManager::CItemManager(void)
{
}

void CItemManager::DeployItem(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\item_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		ITEM_TABLE_DATA t;
		t.id = (ITEM_ID)csv_loader.GetInteger(i, (int)ITEM_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)ITEM_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)ITEM_TABLE_DATA_PARAM::Y);

		m_ItemTable.push_back(t);
	}

	csv_loader.Unload();
}

void CItemManager::UpdateItemTable(void)
{
	if (m_ItemTable.empty()) return;

	ITEM_TABLE_LIST::iterator it = m_ItemTable.begin();
	ITEM_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);

	m_ItemTable.erase(it);
}

void CItemManager::UpdateItem(void)
{
	ITEM_LIST::iterator it = m_ItemList.begin();
	ITEM_LIST::iterator end = m_ItemList.end();

	while (it != end)
	{
		IItem* item = (IItem*)(*it);

		item->Update();
		CCharacterManager::GetInstance().CheckHitItem(item);
		CCharacterManager::GetInstance().JumpUp(item);
		CCharacterManager::GetInstance().Invincible(item);

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
