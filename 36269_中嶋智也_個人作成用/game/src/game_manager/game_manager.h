#pragma once

#include "vivid.h"

class CGameManager
{
public:
	// �C���X�^���X�̎擾
	static CGameManager& GetInstance(void);

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
	CGameManager(void) = default;
	
	// �R�s�[�R���X�g���N�^
	CGameManager(const CGameManager& rhs) = delete;

	// �f�X�g���N�^
	~CGameManager(void) = default;

	// ������Z�q
	CGameManager operator=(const CGameManager& rhs) = delete;
};