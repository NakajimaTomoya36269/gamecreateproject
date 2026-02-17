#include "gameover.h"
#include "../../scene_manager.h"

// 「Push Enter」表示用フォントサイズ
const int   CGameOver::m_enter_font_size = 60;

// 自動でタイトルに戻るまでの時間（フレーム数）
const float CGameOver::m_scene_change_time = 360.0f;


// コンストラクタ
CGameOver::CGameOver(void)
// テキスト描画位置（未使用なら削除してもOK）
    : m_Position(vivid::Vector2(0.0f, 0.0f))
    // 「Push Enter to Title」の表示位置
    , m_EnterPosition(vivid::Vector2(608.0f, 800.0f))
    // シーン切り替え用タイマー初期化
    , m_SceneChangeTimer(0.0f)
{
}


// 初期化処理
void CGameOver::Initialize(void)
{
    // Enter表示用フォントを生成
    vivid::CreateFont(m_enter_font_size, 6);

    // タイマーをリセット
    m_SceneChangeTimer = 0.0f;
}


// 毎フレーム更新処理
void CGameOver::Update(void)
{
    namespace keyboard = vivid::keyboard;

    // テンキーのEnterキーが押された瞬間を取得
    bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);

    // Enterキーが押されたらタイトル画面へ遷移
    if (change_scene_key)
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }

    // タイマーを1フレーム進める
    // 一定時間（m_scene_change_time）を超えたら自動でタイトルへ
    if (++m_SceneChangeTimer > m_scene_change_time)
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
}


// 描画処理
void CGameOver::Draw(void)
{
    // 背景画像描画
    vivid::DrawTexture("data\\background.png", vivid::Vector2(0.0f, 0.0f));

    // GameOver画像描画
    vivid::DrawTexture("data\\gameover.png", vivid::Vector2(543.0f, 250.0f));

    // 「Push Enter to Title」テキスト描画
    vivid::DrawText(m_enter_font_size, "Push Enter to Title", m_EnterPosition, 0xff99ccff);
}


// 終了処理
void CGameOver::Finalize(void)
{
    // 今回は特に後処理なし
}
