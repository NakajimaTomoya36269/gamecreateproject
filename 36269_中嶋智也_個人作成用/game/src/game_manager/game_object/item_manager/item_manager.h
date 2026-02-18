#pragma once

#include "vivid.h"
#include <list>
#include <memory>
#include <unordered_map>
#include <functional>
#include "item/item_id.h"

class IItem;

//==================================================
// アイテム管理クラス
//==================================================
// アイテムの生成・更新・破棄を一元管理するシングルトン。
// 配置情報は外部データ（CSV）から読み込み、テーブル駆動で生成する。
class CItemManager
{
public:
	//==================================================
	// シングルトン
	//==================================================

	// インスタンス取得
	static CItemManager& GetInstance(void);

	//==================================================
	// ライフサイクル
	//==================================================

	// 管理データ初期化・配置テーブル読み込み
	void Initialize(void);

	// 出現・更新処理
	void Update(void);

	// 管理中アイテム描画
	void Draw(void);

	// 管理中アイテム解放
	void Finalize(void);

	//==================================================
	// アイテム生成
	//==================================================

	// 指定 ID のアイテムを指定座標に生成
	void Create(ITEM_ID id, const vivid::Vector2& position);

private:
	//==================================================
	// コンストラクタ制御
	//==================================================

	CItemManager(void);

	// コピー禁止
	CItemManager(const CItemManager& rhs) = delete;

	// 明示的な解放処理は持たない
	~CItemManager(void) = default;

	// 代入禁止
	CItemManager operator=(const CItemManager& rhs) = delete;

	//==================================================
	// 内部処理
	//==================================================

	// 配置データ（CSV）読み込み
	void DeployItem(void);

	// 出現テーブル更新
	void UpdateItemTable(void);

	// 管理中アイテム更新
	void UpdateItem(void);

	//==================================================
	// アイテム配置テーブル定義
	//==================================================

	// CSV カラム定義
	enum class ITEM_TABLE_DATA_PARAM
	{
		ID,
		X,
		Y,
	};

	// アイテム配置データ
	struct ITEM_TABLE_DATA
	{
		ITEM_ID id;
		int     x;
		int     y;
	};

	//----------------------------------
	// Factory用
	//----------------------------------

	using CreateFunc = std::function < std::unique_ptr<IItem>()>;

	std::unordered_map<ITEM_ID, CreateFunc> m_CreateMap;

	// アイテム登録
	void RegisterItems(void);

	using ITEM_TABLE_LIST = std::list<ITEM_TABLE_DATA>; // 配置テーブル型
	using ITEM_LIST = std::list<std::unique_ptr<IItem>>; // 管理アイテム型

	//==================================================
	// 管理データ
	//==================================================

	ITEM_TABLE_LIST m_ItemTable; // 出現待ちアイテムテーブル
	ITEM_LIST       m_ItemList;  // 現在管理中のアイテム
};
