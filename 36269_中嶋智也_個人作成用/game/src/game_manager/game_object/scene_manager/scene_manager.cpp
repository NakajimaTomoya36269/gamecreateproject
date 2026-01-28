#include "scene_manager.h"
#include "scene/gamemain/gamemain.h"
#include "scene/title/title.h"
#include "scene/gameover/gameover.h"
#include "scene/gameclear/gameclear.h"

const int				CSceneManager::m_fade_speed = 10;
const vivid::Vector2	CSceneManager::m_fade_position = vivid::Vector2(0.0f, 0.0f);
const unsigned int		CSceneManager::m_fade_color = 0xff000000;
const int				CSceneManager::m_max_fade_alpha = 255;
const int				CSceneManager::m_min_fade_alpha = 0;

CSceneManager& CSceneManager::GetInstance(void)
{
	static CSceneManager instance;

	return instance;
}

void CSceneManager::Initialize(void)
{
	ChangeScene(SCENE_ID::TITLE);

	m_SceneState = SCENE_STATE::SCENE_CHANGE;

	m_ChangeScene = false;
}

void CSceneManager::Update(void)
{
	switch (m_SceneState)
	{
	case SCENE_STATE::FADEIN: UpdateFadeIn(); break;
	case SCENE_STATE::SCENE_UPDATE: SceneUpdate(); break;
	case SCENE_STATE::FADE_OUT: UpdateFadeOut(); break;
	case SCENE_STATE::SCENE_CHANGE: SceneChange(); break;
	}
}

void CSceneManager::Draw(void)
{
	// シーンの描画
	m_Scene->Draw();
}

void CSceneManager::Finalize(void)
{
	// シーンの解放
	m_Scene->Finalize();

	// シーンオブジェクトの削除
	delete m_Scene;

	m_Scene = nullptr;
}

void CSceneManager::ChangeScene(SCENE_ID next_scene)
{
	m_NextSceneID = next_scene;

	m_ChangeScene = true;
}

void CSceneManager::DrawSceneEffect(void)
{
	// アルファ値とフェードカラーの合成
	unsigned int color = (m_FadeAlpha << 24) | (m_fade_color & 0x00ffffff);

	// シーンエフェクトを描画
	vivid::DrawTexture("data\\white.png", m_fade_position, color);
}

void CSceneManager::Change(SCENE_ID id)
{
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

CSceneManager::CSceneManager(void)
	: m_CurrentSceneID(SCENE_ID::DAMMY)
	, m_NextSceneID(SCENE_ID::DAMMY)
	, m_Scene(nullptr)
	, m_ChangeScene(false)
	, m_FadeAlpha(m_max_fade_alpha)
{
}

void CSceneManager::UpdateFadeIn(void)
{
	m_FadeAlpha -= m_fade_speed;

	if (m_FadeAlpha < m_min_fade_alpha)
	{
		m_FadeAlpha = m_min_fade_alpha;

		// シーン更新
		m_SceneState = SCENE_STATE::SCENE_UPDATE;
	}
}

void CSceneManager::SceneUpdate(void)
{
	// シーンの更新
	if (m_Scene) m_Scene->Update();

	// シーン変更が発生
	if (m_CurrentSceneID != m_NextSceneID || m_ChangeScene)
	{
		m_ChangeScene = false;

		// フェードアウト
		m_SceneState = SCENE_STATE::FADE_OUT;
	}
}

void CSceneManager::UpdateFadeOut(void)
{
	m_FadeAlpha += m_fade_speed;

	if (m_FadeAlpha > m_max_fade_alpha)
	{
		m_FadeAlpha = m_max_fade_alpha;

		// シーン変更
		m_SceneState = SCENE_STATE::SCENE_CHANGE;
	}
}

void CSceneManager::SceneChange(void)
{
	m_FadeAlpha = m_max_fade_alpha;

	if (m_Scene)
	{
		m_Scene->Finalize();

		delete m_Scene;

		m_Scene = nullptr;
	}

	Change(m_NextSceneID); // 切り替え関数

	// 初期化
	m_Scene->Initialize();

	// 更新
	m_Scene->Update();

	m_CurrentSceneID = m_NextSceneID;

	// フェードイン
	m_SceneState = SCENE_STATE::FADEIN;
}
