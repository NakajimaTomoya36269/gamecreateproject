#pragma once

#include "vivid.h"
#include <list>
#include "stage/stage.h"

class CStage;

class CStageManager
{
public:
	// インスタンスの取得
	static CStageManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// ステージの作成
	void Create(const vivid::Vector2& position);

	// 地面の上にいるかの判定の取得
	bool GetIsGround(void);

private:
	// コンストラクタ
	CStageManager(void);

	// コピーコンストラクタ
	CStageManager(const CStageManager& rhs) = delete;

	// デストラクタ
	~CStageManager(void) = default;

	// 代入演算子
	CStageManager operator=(const CStageManager& rhs) = delete;

	// ステージリスト型
	using STAGE_LIST = std::list<CStage*>;

	// ステージリスト
	STAGE_LIST m_StageList;
};