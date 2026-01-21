#pragma once

#include "vivid.h"
#include <list>
#include "switch/switch_id.h"

class ISwitch;

class CSwitchManager
{
public:
	// インスタンスの取得
	static CSwitchManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 作成
	void Create(SWITCH_ID id, const vivid::Vector2& position);

private:
	// コンストラクタ
	CSwitchManager(void);

	// コピーコンストラクタ
	CSwitchManager(const CSwitchManager& rhs) = delete;

	// デストラクタ
	~CSwitchManager(void) = default;

	// 代入演算子
	CSwitchManager operator=(const CSwitchManager& rhs) = delete;

	// スイッチ配置
	void DeploySwitch(void);

	// スイッチテーブルの更新
	void UpdateSwitchTable(void);

	// スイッチの更新
	void UpdateSwitch(void);

	enum class SWITCH_TABLE_DATA_PARAM
	{
		ID,
		X,
		Y,
	};

	struct SWITCH_TABLE_DATA
	{
		SWITCH_ID id;
		int x;
		int y;
	};

	using SWITCH_TABLE_LIST = std::list<SWITCH_TABLE_DATA>;	// スイッチテーブルリスト型
	using SWITCH_LIST = std::list<ISwitch*>;				// スイッチリスト型
	SWITCH_TABLE_LIST	m_SwitchTable;						// スイッチテーブルリスト
	SWITCH_LIST			m_SwitchList;						// スイッチリスト
};