#pragma once

#include "vivid.h"

class CGameManager
{
public:
	// インスタンスの取得
	static CGameManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

private:
	// コンストラクタ
	CGameManager(void) = default;
	
	// コピーコンストラクタ
	CGameManager(const CGameManager& rhs) = delete;

	// デストラクタ
	~CGameManager(void) = default;

	// 代入演算子
	CGameManager operator=(const CGameManager& rhs) = delete;
};