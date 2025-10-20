#include "scene_manager.h"
#include "scene/gamemain/gamemain.h"

CSceneManager& CSceneManager::GetInstance(void)
{
	static CSceneManager instance;

	return instance;
}

void CSceneManager::Initialize(void)
{
	ChangeScene(SCENE_ID::GAMEMAIN);
}

void CSceneManager::Update(void)
{
	// シーンの切り替わり確認
	if (m_CurrentSceneID != m_NextSceneID)
		Change(); // 切り替え関数

	// シーンの更新
	m_Scene->Update();
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
}

void CSceneManager::Change(void)
{
	if (m_Scene != nullptr)
	{
		// 現在動いているシーンを終わらせる
		m_Scene->Finalize();

		delete m_Scene;

		m_Scene = nullptr;
	}

	switch (m_NextSceneID)
	{
	case SCENE_ID::TITLE:
		break;
	case SCENE_ID::GAMEMAIN:
		m_Scene = new CGamemain();
		break;
	case SCENE_ID::GAMEOVER:
		break;
	case SCENE_ID::GAMECLEAR:
		break;
	}

	// ヌルチェックを行う、問題なければ初期化を呼ぶ
	if (m_Scene)
	{
		m_Scene->Initialize();
	}

	// シーンIDを合わせる
	m_CurrentSceneID = m_NextSceneID;
}

CSceneManager::CSceneManager(void)
	: m_CurrentSceneID(SCENE_ID::DAMMY)
	, m_NextSceneID(SCENE_ID::DAMMY)
	, m_Scene(nullptr)
{
}
