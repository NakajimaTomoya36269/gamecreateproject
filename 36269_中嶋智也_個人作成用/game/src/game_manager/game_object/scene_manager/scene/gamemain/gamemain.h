#pragma once

#include "../scene.h"

class CGamemain : public IScene
{
public:
	// �R���X�g���N�^
	CGamemain(void);

	// �f�X�g���N�^
	~CGamemain(void) = default;

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �`��
	void Draw(void) override;

	// ���
	void Finalize(void) override;
};