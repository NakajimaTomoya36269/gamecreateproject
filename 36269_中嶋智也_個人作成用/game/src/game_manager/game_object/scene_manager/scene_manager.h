#pragma once

#include "vivid.h"
#include "scene/scene.h"
#include "scene/scene_id.h"

class IScene;

class CSceneManager
{
public:
	// インスタンスの取得
	static CSceneManager& GetInstance(void);

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
	CSceneManager(void);

	// コピーコンストラクタ
	CSceneManager(const CSceneManager& rhs) = delete;

	// デストラクタ
	~CSceneManager(void) = default;

	// 代入演算子
	CSceneManager operator=(const CSceneManager& rhs) = delete;
};