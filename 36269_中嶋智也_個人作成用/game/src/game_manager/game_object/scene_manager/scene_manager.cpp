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
	// �V�[���̐؂�ւ��m�F
	if (m_CurrentSceneID != m_NextSceneID)
		Change(); // �؂�ւ��֐�

	// �V�[���̍X�V
	m_Scene->Update();
}

void CSceneManager::Draw(void)
{
	// �V�[���̕`��
	m_Scene->Draw();
}

void CSceneManager::Finalize(void)
{
	// �V�[���̉��
	m_Scene->Finalize();

	// �V�[���I�u�W�F�N�g�̍폜
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
		// ���ݓ����Ă���V�[�����I��点��
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

	// �k���`�F�b�N���s���A���Ȃ���Ώ��������Ă�
	if (m_Scene)
	{
		m_Scene->Initialize();
	}

	// �V�[��ID�����킹��
	m_CurrentSceneID = m_NextSceneID;
}

CSceneManager::CSceneManager(void)
	: m_CurrentSceneID(SCENE_ID::DAMMY)
	, m_NextSceneID(SCENE_ID::DAMMY)
	, m_Scene(nullptr)
{
}
