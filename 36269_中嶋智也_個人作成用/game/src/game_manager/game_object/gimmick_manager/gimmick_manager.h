#pragma once

#include "vivid.h"
#include "gimmick/gimmick_id.h"
#include <list>

class IGimmick;

class CGimmickManager
{
public:
	// インスタンスの取得
	static CGimmickManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 作成
	void Create(GIMMICK_ID id, const vivid::Vector2& position);

private:
	// コンストラクタ
	CGimmickManager(void);

	// コピーコンストラクタ
	CGimmickManager(const CGimmickManager& rhs) = delete;

	// デストラクタ
	~CGimmickManager(void) = default;

	// 代入演算子
	CGimmickManager operator=(const CGimmickManager& rhs) = delete;

	using GIMMICK_LIST = std::list<IGimmick*>;		// ギミックリスト型
	GIMMICK_LIST	m_GimmickList;					// ギミックリスト
};