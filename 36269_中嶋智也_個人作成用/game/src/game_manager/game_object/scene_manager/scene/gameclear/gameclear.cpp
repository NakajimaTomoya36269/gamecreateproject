#include "gameclear.h"
#include "../../scene_manager.h"

//==================================================
// 定数定義
//==================================================

// デバッグ表示用フォントサイズ
const int CGameClear::m_font_size = 40;

// 「GameClear」表示用フォントサイズ
const int CGameClear::m_gameclear_font_size = 200;

// Enter案内表示用フォントサイズ
const int CGameClear::m_enter_font_size = 60;

//==================================================
// コンストラクタ
//==================================================
CGameClear::CGameClear(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))          // デバッグ表示用
	, m_GameClearPosition(vivid::Vector2(300.0f, 440.0f)) // GameClear文字位置
	, m_EnterPosition(vivid::Vector2(608.0f, 800.0f))     // Enter案内位置
{
}

//==================================================
// 初期化
//==================================================
// 表示に使用するフォントを生成
void CGameClear::Initialize(void)
{
	vivid::CreateFont(m_gameclear_font_size, 8);
	vivid::CreateFont(m_enter_font_size, 6);
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

#ifdef _DEBUG
	// デバッグ用：Enter案内位置の微調整
	if (keyboard::Button(keyboard::KEY_ID::UP))
	{
		m_EnterPosition.y -= 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::DOWN))
	{
		m_EnterPosition.y += 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::RIGHT))
	{
		m_EnterPosition.x += 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::LEFT))
	{
		m_EnterPosition.x -= 1.0f;
	}
#endif
}

//==================================================
// 描画処理
//==================================================
void CGameClear::Draw(void)
{
	// 背景描画
	vivid::DrawTexture("data\\background.png", vivid::Vector2(0.0f, 0.0f));

	// ゲームクリア演出
	vivid::DrawText(m_gameclear_font_size, "GameClear", m_GameClearPosition, 0xff0000aa);

	// タイトル遷移案内
	vivid::DrawText(m_enter_font_size, "Push Enter to Title", m_EnterPosition);

#ifdef _DEBUG
	// デバッグ情報表示
	vivid::DrawText(m_font_size, "GameClearScene", m_Position);
	vivid::DrawText(40, std::to_string(m_EnterPosition.x), vivid::Vector2(0.0f, 40.0f));
	vivid::DrawText(40, std::to_string(m_EnterPosition.y), vivid::Vector2(0.0f, 80.0f));
#endif
}

//==================================================
// 解放処理
//==================================================
void CGameClear::Finalize(void)
{
	// 現状は明示的な解放処理なし
}
