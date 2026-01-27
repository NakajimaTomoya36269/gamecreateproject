#pragma once

#include "vivid.h"
#include "bullet/bullet_id.h"
#include <list>

class IBullet;
class IStage;

class CBulletManager
{
public:
	// インスタンスの取得
	static CBulletManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 作成
	void Create(BULLET_ID id, const vivid::Vector2& position, float direction, float speed);

	// ステージのアタリ判定
	void CheckHitStage(IStage* stage);

private:
	// コンストラクタ
	CBulletManager(void);

	// コピーコンストラクタ
	CBulletManager(const CBulletManager& rhs) = delete;

	// デストラクタ
	~CBulletManager(void) = default;

	// 代入演算子
	CBulletManager operator=(const CBulletManager& rhs) = delete;

	// バレットリスト型
	using BULLET_LIST = std::list<IBullet*>;

	BULLET_LIST			m_BulletList;		// バレットリスト
};