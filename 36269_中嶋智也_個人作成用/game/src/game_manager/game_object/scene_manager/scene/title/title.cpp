#include "title.h"
#include "../../scene_manager.h"
#include "../../../../../utility/utility.h"

//==================================================
// 定数定義
//==================================================

// デバッグ表示用フォントサイズ
const int CTitle::m_font_size = 40;

// ENTER 表示用フォントサイズ
const int CTitle::m_enter_font_size = 60;

//==================================================
// コンストラクタ
//==================================================
// ・初期値のみ設定
// ・リソース生成は Initialize() に委譲
CTitle::CTitle(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))		// デバッグ表示用位置
	, m_EnterPosition(vivid::Vector2(604.0f, 790.0f))	// ENTER 表示位置
	, m_Color(0xffffffff)				// テキストカラー（ARGB）
	, m_Angle(0.0f)					// アニメーション用角度
{
}

//==================================================
// 初期化
//==================================================
// ・フォント生成
// ・演出用パラメータのリセット
void CTitle::Initialize(void)
{
	vivid::CreateFont(m_enter_font_size, 3);

	m_Color = 0xff99ccff;
	m_Angle = 0.0f;
}

//==================================================
// 更新処理
//==================================================
// ・ENTER 表示の点滅アニメーション
// ・シーン遷移入力の受付
void CTitle::Update(void)
{
	// サイン波によるアルファ値アニメーション
	m_Angle += 2.0f;

	int alpha = static_cast<int>(sin(DEG_TO_RAD(m_Angle)) * 127) + 128;

	// ARGB カラーを生成（アルファのみ変化）
	m_Color = (static_cast<unsigned int>(alpha) & 0xff) << 24 | 0x0099ccff;

	// ENTER キー入力によるシーン遷移
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);

	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
	}
}

//==================================================
// 描画処理
//==================================================
// ・背景 → タイトル → ENTER 表示の順で描画
void CTitle::Draw(void)
{
	// 背景描画
	vivid::DrawTexture("data\\background.png", vivid::Vector2(0.0f, 0.0f));

	// タイトルロゴ描画
	vivid::DrawTexture("data\\title.png", vivid::Vector2(220.0f, 0.0f));

	// ENTER 表示（アルファアニメーション付き）
	vivid::DrawText(m_enter_font_size, "Push Enter to Start", m_EnterPosition, m_Color);
}

//==================================================
// 解放処理
//==================================================
// ・現状、明示的な解放処理なし
void CTitle::Finalize(void)
{
}
