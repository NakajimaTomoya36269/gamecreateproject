#pragma once

#include "vivid.h"
#include <list>
#include "enemy/enemy.h"
#include "enemy/enemy_id.h"
#include "../stage_manager/stage_manager.h"

class CEnemyManager
{
public:
	// インスタンスの取得
	static CEnemyManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 敵の作成
	void Create(ENEMY_ID id, const vivid::Vector2& position);

	// 地面の上にいる判定
	bool OnGround(IStage* stage);

	// 移動範囲
	void MoveArea(IStage* stage);

private:
	// コンストラクタ
	CEnemyManager(void);

	// コピーコンストラクタ
	CEnemyManager(const CEnemyManager& rhs) = delete;

	// デストラクタ
	~CEnemyManager(void) = default;

	// 代入演算子
	CEnemyManager operator=(const CEnemyManager& rhs) = delete;

	// 敵リスト型
	using ENEMY_LIST = std::list<IEnemy*>;

	ENEMY_LIST m_EnemyList;			// 敵リスト
};