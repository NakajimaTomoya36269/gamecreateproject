#include "game_manager.h"
#include "game_object/game_object.h"

//============================================================
// シングルトン取得
//============================================================
CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;
	return instance;
}

//============================================================
// 初期化処理
// ・ゲーム全体の初期化
// ・SceneManager を初期化
//============================================================
void CGameManager::Initialize(void)
{
	CSceneManager::GetInstance().Initialize();
}

//============================================================
// 更新処理
// ・ゲーム全体の更新
// ・SceneManager を更新
//============================================================
void CGameManager::Update(void)
{
	CSceneManager::GetInstance().Update();
}

//============================================================
// 描画処理
// ・ゲーム全体の描画
// ・SceneManager の描画とシーンエフェクト描画
//============================================================
void CGameManager::Draw(void)
{
	CSceneManager::GetInstance().Draw();
	CSceneManager::GetInstance().DrawSceneEffect();
}

//============================================================
// 終了処理
// ・ゲーム全体の終了処理
// ・SceneManager を解放
//============================================================
void CGameManager::Finalize(void)
{
	CSceneManager::GetInstance().Finalize();
}
