#include "gameclear.h"
#include "../../scene_manager.h"

//==================================================
// 定数定義
//==================================================

// デバッグ表示用フォントサイズ
const int CGameClear::m_font_size = 40;

// Enter案内表示用フォントサイズ
const int CGameClear::m_enter_font_size = 60;

const float CGameClear::m_scene_change_time = 360.0f;

//==================================================
// コンストラクタ
//==================================================
CGameClear::CGameClear(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))          // デバッグ表示用
	, m_EnterPosition(vivid::Vector2(608.0f, 800.0f))     // Enter案内位置
	, m_SceneChangeTimer(0.0f)
{
}

//==================================================
// 初期化
//==================================================
// 表示に使用するフォントを生成
void CGameClear::Initialize(void)
{
	vivid::CreateFont(m_enter_font_size, 6);
	m_SceneChangeTimer = 0.0f;
}

//==================================================
// 更新処理
//==================================================
// ・Enter入力でタイトルシーンへ遷移
// ・デバッグ時は表示位置の微調整を許可
void CGameClear::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// Enterキーでタイトルへ戻る
	if (keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER))
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}

	if (++m_SceneChangeTimer > m_scene_change_time)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}
}

//==================================================
// 描画処理
//==================================================
void CGameClear::Draw(void)
{
	// 背景描画
	vivid::DrawTexture("data\\background.png", vivid::Vector2(0.0f, 0.0f));

	// ゲームクリア演出
	vivid::DrawTexture("data\\gameclear.png", vivid::Vector2(598.0f, 300.0f));

	// タイトル遷移案内
	vivid::DrawText(m_enter_font_size, "Push Enter to Title", m_EnterPosition, 0xff99ccff);
}

//==================================================
// 解放処理
//==================================================
void CGameClear::Finalize(void)
{
	// 現状は明示的な解放処理なし
}
