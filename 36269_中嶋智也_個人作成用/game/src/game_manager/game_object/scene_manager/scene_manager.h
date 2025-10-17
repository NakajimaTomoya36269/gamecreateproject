#pragma once

#include "vivid.h"
#include "scene/scene.h"
#include "scene/scene_id.h"

class IScene;

class CSceneManager
{
public:
	// �C���X�^���X�̎擾
	static CSceneManager& GetInstance(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// ���
	void Finalize(void);

private:
	// �R���X�g���N�^
	CSceneManager(void);

	// �R�s�[�R���X�g���N�^
	CSceneManager(const CSceneManager& rhs) = delete;

	// �f�X�g���N�^
	~CSceneManager(void) = default;

	// ������Z�q
	CSceneManager operator=(const CSceneManager& rhs) = delete;
};