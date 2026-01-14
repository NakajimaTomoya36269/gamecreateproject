#pragma once

#include "vivid.h"
#include <list>
#include "stage/stage.h"
#include "stage/stage_id.h"

class IStage;
class ISwitch;

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
	void Create(STAGE_ID id, const vivid::Vector2& position);

	// 敵が地面の上にいるかの判定
	void EnemyOnGround(void);

	// キャラクターのアタリ判定
	bool CheckHitCharacter(ICharacter* character, float&& position_x);

	void MoveChange(ISwitch* sw);


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
	using STAGE_LIST = std::list<IStage*>;

	// ステージリスト
	STAGE_LIST m_StageList;
};