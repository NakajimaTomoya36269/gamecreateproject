#pragma once

#include "vivid.h"
#include <list>
#include "item/item_id.h"

class IItem;

class CItemManager
{
public:
	// インスタンスの取得
	static CItemManager& GetInstance(void);

	// 初期化
	void Initilaize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 作成
	void Create(ITEM_ID id, const vivid::Vector2& position);

private:
	// コンストラクタ
	CItemManager(void);

	// コピーコンストラクタ
	CItemManager(const CItemManager& rhs) = delete;

	// デストラクタ
	~CItemManager(void) = default;

	// 代入演算子
	CItemManager operator=(const CItemManager& rhs) = delete;

	using ITEM_LIST = std::list<IItem*>;	// アイテムリスト型

	ITEM_LIST		m_ItemList;				// アイテムリスト
};