#include "item_manager.h"
#include "item/item.h"
#include "item/jump_up_item/jump_up_item.h"
#include "item/invincible_item/invincible_item.h"
#include "../character_manager/character_manager.h"
#include "../../../utility/csv_loader/csv_loader.h"

//==================================================
// シングルトン取得
//==================================================
CItemManager& CItemManager::GetInstance(void)
{
	static CItemManager instance;
	return instance;
}

//==================================================
// 初期化
//==================================================
// ・管理中アイテムをクリア
// ・CSV から配置情報を読み込み
void CItemManager::Initialize(void)
{
	m_ItemList.clear();
	m_ItemTable.clear();

	DeployItem();
}

//==================================================
// 更新
//==================================================
void CItemManager::Update(void)
{
	UpdateItemTable(); // 出現テーブル更新
	UpdateItem();      // 既存アイテム更新
}

//==================================================
// 描画
//==================================================
void CItemManager::Draw(void)
{
	for (ITEM_LIST::iterator it = m_ItemList.begin();
		it != m_ItemList.end();
		++it)
	{
		(*it)->Draw();
	}
}

//==================================================
// 解放
//==================================================
void CItemManager::Finalize(void)
{
	for (ITEM_LIST::iterator it = m_ItemList.begin();
		it != m_ItemList.end();
		++it)
	{
		(*it)->Finalize();
	}
	m_ItemList.clear();
}

//==================================================
// アイテム生成
//==================================================
// ITEM_ID に応じて派生クラスを生成
void CItemManager::Create(ITEM_ID id, const vivid::Vector2& position)
{
	std::unordered_map<ITEM_ID, CreateFunc>::iterator it = m_CreateMap.find(id);

	if (it == m_CreateMap.end())
		return;

	std::unique_ptr<IItem> item = it->second();

	if (!item) return;

	item->Initialize(position);
	m_ItemList.push_back(std::move(item));
}

//==================================================
// コンストラクタ
//==================================================
CItemManager::CItemManager(void)
{
	RegisterItems();
}

//==================================================
// 配置データ読み込み
//==================================================
// CSV からアイテム配置テーブルを構築
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

//==================================================
// 出現テーブル更新
//==================================================
// テーブル先頭のアイテムを順次生成
void CItemManager::UpdateItemTable(void)
{
	if (m_ItemTable.empty()) return;

	ITEM_TABLE_LIST::iterator it = m_ItemTable.begin();
	const ITEM_TABLE_DATA& t = *it;

	Create(t.id, vivid::Vector2((float)t.x, (float)t.y));
	m_ItemTable.erase(it);
}

//==================================================
// アイテム更新
//==================================================
void CItemManager::UpdateItem(void)
{
	ITEM_LIST::iterator it = m_ItemList.begin();

	while (it != m_ItemList.end())
	{
		IItem* item = it->get();

		// 基本挙動更新
		item->Update();

		// キャラクターとの相互作用
		CCharacterManager::GetInstance().CheckHitItem(item);
		CCharacterManager::GetInstance().JumpUp(item);
		CCharacterManager::GetInstance().Invincible(item);

		// 非アクティブ化されたアイテムを破棄
		if (!item->GetActive())
		{
			item->Finalize();
			it = m_ItemList.erase(it);
			continue;
		}

		++it;
	}
}

void CItemManager::RegisterItems(void)
{
	m_CreateMap[ITEM_ID::INVINCIBLE_ITEM] =
		[]() {return std::make_unique<CInvincibleItem>(); };

	m_CreateMap[ITEM_ID::JUMP_UP_ITEM] =
		[]() {return std::make_unique<CJumpUpItem>(); };
}
