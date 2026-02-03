#include "scene_manager.h"
#include "scene/gamemain/gamemain.h"
#include "scene/title/title.h"
#include "scene/gameover/gameover.h"
#include "scene/gameclear/gameclear.h"

//==============================
// 定数定義（フェード演出関連）
//==============================

// フェードの変化速度（1フレームあたりのアルファ変化量）
const int                CSceneManager::m_fade_speed = 10;

// フェード描画位置（全画面を覆うため左上固定）
const vivid::Vector2     CSceneManager::m_fade_position = vivid::Vector2(0.0f, 0.0f);

// フェード用カラー（ARGB: αのみ動的に変更）
const unsigned int       CSceneManager::m_fade_color = 0xff000000;

// アルファ値の最大・最小（クランプ用）
const int                CSceneManager::m_max_fade_alpha = 255;
const int                CSceneManager::m_min_fade_alpha = 0;

//==============================
// シングルトン取得
//==============================
CSceneManager& CSceneManager::GetInstance(void)
{
	// 静的ローカル変数による遅延初期化シングルトン
	static CSceneManager instance;
	return instance;
}

//==============================
// 初期化
//==============================
void CSceneManager::Initialize(void)
{
	// 初期シーンをタイトルに設定（即切り替え）
	ChangeScene(SCENE_ID::TITLE);

	// 起動時はシーン生成フェーズから開始
	m_SceneState = SCENE_STATE::SCENE_CHANGE;

	// 明示的なシーン変更要求フラグをリセット
	m_ChangeScene = false;
}

//==============================
// 更新処理（ステートマシン）
//==============================
void CSceneManager::Update(void)
{
	// シーン管理は状態遷移で制御
	switch (m_SceneState)
	{
	case SCENE_STATE::FADEIN:        UpdateFadeIn();   break;
	case SCENE_STATE::SCENE_UPDATE: SceneUpdate();    break;
	case SCENE_STATE::FADE_OUT:     UpdateFadeOut();  break;
	case SCENE_STATE::SCENE_CHANGE: SceneChange();    break;
	}
}

//==============================
// 描画
//==============================
void CSceneManager::Draw(void)
{
	// 現在のシーン描画
	// フェードは外部（もしくは後段）で重ねる想定
	if (m_Scene) m_Scene->Draw();
}

//==============================
// 終了処理
//==============================
void CSceneManager::Finalize(void)
{
	// 管理中シーンの明示的解放
	if (m_Scene)
	{
		m_Scene->Finalize();
		delete m_Scene;
		m_Scene = nullptr;
	}
}

//==============================
// シーン変更要求
//==============================
void CSceneManager::ChangeScene(SCENE_ID next_scene)
{
	// 次に遷移するシーンIDを保持
	m_NextSceneID = next_scene;

	// 現在のシーンIDと同一でも
	// 強制的に切り替えを発生させたい場合があるためフラグ管理
	m_ChangeScene = true;
}

//==============================
// フェード描画
//==============================
void CSceneManager::DrawSceneEffect(void)
{
	// アルファ値を上位8bitに合成
	unsigned int color = (m_FadeAlpha << 24) | (m_fade_color & 0x00ffffff);

	// 白テクスチャを全画面描画することで疑似フェード
	vivid::DrawTexture("data\\white.png", m_fade_position, color);
}

//==============================
// シーン生成（Factory的役割）
//==============================
void CSceneManager::Change(SCENE_ID id)
{
	// シーンIDに応じた具象クラス生成
	switch (id)
	{
	case SCENE_ID::TITLE:
		m_Scene = new CTitle();
		break;
	case SCENE_ID::GAMEMAIN:
		m_Scene = new CGamemain();
		break;
	case SCENE_ID::GAMEOVER:
		m_Scene = new CGameOver();
		break;
	case SCENE_ID::GAMECLEAR:
		m_Scene = new CGameClear();
		break;
	}
}

//==============================
// コンストラクタ
//==============================
CSceneManager::CSceneManager(void)
	: m_CurrentSceneID(SCENE_ID::DAMMY)   // 未初期化状態を示すダミーID
	, m_NextSceneID(SCENE_ID::DAMMY)
	, m_Scene(nullptr)
	, m_ChangeScene(false)
	, m_FadeAlpha(m_max_fade_alpha)       // 起動時は完全フェード状態
{
}

//==============================
// フェードイン処理
//==============================
void CSceneManager::UpdateFadeIn(void)
{
	// アルファ値を減少させて表示状態へ
	m_FadeAlpha -= m_fade_speed;

	if (m_FadeAlpha < m_min_fade_alpha)
	{
		m_FadeAlpha = m_min_fade_alpha;

		// 完全表示後、通常更新フェーズへ
		m_SceneState = SCENE_STATE::SCENE_UPDATE;
	}
}

//==============================
// シーン通常更新
//==============================
void CSceneManager::SceneUpdate(void)
{
	// 現在のシーンロジック更新
	if (m_Scene) m_Scene->Update();

	// シーンID不一致 or 明示的変更要求があれば遷移開始
	if (m_CurrentSceneID != m_NextSceneID || m_ChangeScene)
	{
		m_ChangeScene = false;

		// 表示状態からフェードアウトへ
		m_SceneState = SCENE_STATE::FADE_OUT;
	}
}

//==============================
// フェードアウト処理
//==============================
void CSceneManager::UpdateFadeOut(void)
{
	// アルファ値を増加させて完全非表示へ
	m_FadeAlpha += m_fade_speed;

	if (m_FadeAlpha > m_max_fade_alpha)
	{
		m_FadeAlpha = m_max_fade_alpha;

		// 非表示になったら安全にシーン切り替え
		m_SceneState = SCENE_STATE::SCENE_CHANGE;
	}
}

//==============================
// シーン切り替え本体
//==============================
void CSceneManager::SceneChange(void)
{
	// 切り替え中は常に完全フェード状態
	m_FadeAlpha = m_max_fade_alpha;

	// 旧シーンの解放
	if (m_Scene)
	{
		m_Scene->Finalize();
		delete m_Scene;
		m_Scene = nullptr;
	}

	// 新シーン生成
	Change(m_NextSceneID);

	// ライフサイクル初期化
	m_Scene->Initialize();

	// 初回Updateをここで1度呼ぶことで
	// 描画前に状態を安定させる設計
	m_Scene->Update();

	// 現在シーンID更新
	m_CurrentSceneID = m_NextSceneID;

	// フェードインへ遷移
	m_SceneState = SCENE_STATE::FADEIN;
}
