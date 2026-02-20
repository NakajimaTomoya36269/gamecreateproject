#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../../enemy_manager/enemy_manager.h"
#include "../../../item_manager/item_manager.h"
#include "../../../switch_manager/switch_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../scene_manager.h"

//-----------------------------------------------------------------------------
// デバッグ用フォントサイズ
// ・シーン識別表示のみで使用
//-----------------------------------------------------------------------------
const int	CGamemain::m_font_size = 40;
const float	CGamemain::m_scene_change_time = 9000.0f;

//-----------------------------------------------------------------------------
// コンストラクタ
// ・ゲーム中の状態管理（PLAY / PAUSE）の初期化のみを行う
// ・実際のリソース生成は Initialize() に委譲
//-----------------------------------------------------------------------------
CGamemain::CGamemain(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_CurrentStateID(GAMEMAIN_STATE_ID::PLAY)
	, m_SceneChangeTimer(0.0f)
{
}

//-----------------------------------------------------------------------------
// 初期化
// ・ゲーム開始時およびリセット時に呼ばれる
// ・各 Manager のライフサイクルを一元管理する役割を持つ
//-----------------------------------------------------------------------------
void CGamemain::Initialize(void)
{
	// ゲーム開始時は必ず PLAY 状態
	m_CurrentStateID = GAMEMAIN_STATE_ID::PLAY;

	m_SceneChangeTimer = 0.0f;

	// キャラクタ管理
	// ・参照を取得して初期化と生成を明示的に分離
	CCharacterManager& character_manager = CCharacterManager::GetInstance();
	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));

	// ステージ管理
	CStageManager::GetInstance().Initialize();

	// 敵管理
	CEnemyManager::GetInstance().Initialize();

	// ゴールは Gamemain が直接所有（シーン固有オブジェクト）
	m_goal.Initialize(vivid::Vector2(9000.0f, 472.0f));

	// アイテム管理
	CItemManager::GetInstance().Initialize();

	// スイッチ管理
	CSwitchManager::GetInstance().Initialize();

	// 背景
	m_background.Initialize();

	// 弾管理
	CBulletManager::GetInstance().Initialize();
}

//-----------------------------------------------------------------------------
// 更新
// ・状態遷移 → 状態別更新 の順を保証
//-----------------------------------------------------------------------------
void CGamemain::Update(void)
{
	// 入力による状態遷移判定
	ChangeState();

	// 現在の状態に応じた処理を実行
	switch (m_CurrentStateID)
	{
	case GAMEMAIN_STATE_ID::PLAY:
		UpdatePlay();
		break;

	case GAMEMAIN_STATE_ID::PAUSE:
		UpdatePause();
		break;
	}
}

//-----------------------------------------------------------------------------
// 描画
// ・描画順がゲームの視覚的レイヤー構造を表す
//-----------------------------------------------------------------------------
void CGamemain::Draw(void)
{
	// 背景 → ステージ → オブジェクト → キャラクタ → UI の順
	m_background.Draw();
	CStageManager::GetInstance().Draw();
	m_goal.Draw();
	CItemManager::GetInstance().Draw();
	CEnemyManager::GetInstance().Draw();
	CBulletManager::GetInstance().Draw();
	CCharacterManager::GetInstance().Draw();
	CSwitchManager::GetInstance().Draw();

	// ポーズ中のみ UI をオーバーレイ表示
	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PAUSE)
	{
		vivid::DrawTexture("data\\pause.png", vivid::Vector2(192.0f, 0.0f));
		vivid::DrawTexture("data\\pause_select.png", vivid::Vector2(768.0f, 750.0f));
	}

#ifdef _DEBUG
	// シーン識別用デバッグ表示
	vivid::DrawText(m_font_size, "GamemainScene", vivid::Vector2(0.0f, 0.0f));
	vivid::DrawText(40, std::to_string(m_SceneChangeTimer), vivid::Vector2(0.0f, 80.0f));
#endif 
}

//-----------------------------------------------------------------------------
// 解放
// ・Initialize() と対になるライフサイクル終端処理
// ・Manager の解放順は依存関係を考慮
//-----------------------------------------------------------------------------
void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
	CEnemyManager::GetInstance().Finalize();
	CItemManager::GetInstance().Finalize();
	CSwitchManager::GetInstance().Finalize();
	CBulletManager::GetInstance().Finalize();

	// シーン所有オブジェクト
	m_goal.Finalize();
	m_background.Finalize();
}

//-----------------------------------------------------------------------------
// PLAY 状態更新
// ・ゲーム進行の中核
//-----------------------------------------------------------------------------
void CGamemain::UpdatePlay(void)
{
	if (++m_SceneChangeTimer > m_scene_change_time)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
	}

	// 各 Manager の更新
	CStageManager::GetInstance().Update();
	CCharacterManager::GetInstance().Update();
	CEnemyManager::GetInstance().Update();
	CSwitchManager::GetInstance().Update();
	CBulletManager::GetInstance().Update();

	// ゴール判定
	if (CCharacterManager::GetInstance().CheckHitGoal(m_goal))
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	}

	m_goal.Update();
	CItemManager::GetInstance().Update();
	m_background.Update();

	namespace keyboard = vivid::keyboard;

	// デバッグ・検証用入力
	bool reset_key = keyboard::Trigger(keyboard::KEY_ID::R);

	// ゲーム全体の再初期化（簡易リセット）
	if (reset_key)
	{
		Finalize();
		Initialize();
	}

#ifdef _DEBUG
	bool change_gameover_scene_key = keyboard::Trigger(keyboard::KEY_ID::Z);
	bool change_gameclear_scene_key = keyboard::Trigger(keyboard::KEY_ID::X);

	// 強制シーン遷移（テスト用）
	if (change_gameover_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
	}
	if (change_gameclear_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	}
#endif
}

//-----------------------------------------------------------------------------
// PAUSE 状態更新
// ・現状は入力待ちのみ
// ・将来的にメニュー操作を追加可能
//-----------------------------------------------------------------------------
void CGamemain::UpdatePause(void)
{
}

//-----------------------------------------------------------------------------
// 状態遷移管理
// ・PLAY / PAUSE の切替とシーン遷移を集約
//-----------------------------------------------------------------------------
void CGamemain::ChangeState(void)
{
	namespace keyboard = vivid::keyboard;

	bool change_pause_state_key = keyboard::Trigger(keyboard::KEY_ID::P);
	bool change_title_scene_key = keyboard::Trigger(keyboard::KEY_ID::T);
	bool change_play_state_key = keyboard::Trigger(keyboard::KEY_ID::S);

	// PLAY → PAUSE
	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PLAY && change_pause_state_key)
	{
		m_CurrentStateID = GAMEMAIN_STATE_ID::PAUSE;
	}

	// PAUSE 中の入力処理
	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PAUSE)
	{
		// PAUSE → PLAY
		if (change_play_state_key)
		{
			m_CurrentStateID = GAMEMAIN_STATE_ID::PLAY;
		}

		// タイトルへ戻る
		if (change_title_scene_key)
		{
			CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		}
	}
}
