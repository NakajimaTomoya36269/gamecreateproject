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

	using SWITCH_LIST = std::list<ISwitch*>;		// スイッチリスト型
	SWITCH_LIST		m_SwitchList;					// スイッチリスト
};