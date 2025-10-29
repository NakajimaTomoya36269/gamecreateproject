#pragma once

#include "vivid.h"
#include <list>
#include "stage/stage.h"

class CStage;

class CStageManager
{
public:
	// �C���X�^���X�̎擾
	static CStageManager& GetInstance(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// ���
	void Finalize(void);

	// �X�e�[�W�̍쐬
	void Create(const vivid::Vector2& position);

	// �n�ʂ̏�ɂ��邩�̔���̎擾
	bool GetIsGround(void);

private:
	// �R���X�g���N�^
	CStageManager(void);

	// �R�s�[�R���X�g���N�^
	CStageManager(const CStageManager& rhs) = delete;

	// �f�X�g���N�^
	~CStageManager(void) = default;

	// ������Z�q
	CStageManager operator=(const CStageManager& rhs) = delete;

	// �X�e�[�W���X�g�^
	using STAGE_LIST = std::list<CStage*>;

	// �X�e�[�W���X�g
	STAGE_LIST m_StageList;
};