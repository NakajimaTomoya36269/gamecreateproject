#pragma once

#include "../scene.h"

class CTitle
	: public IScene
{
public:
	// �R���X�g���N�^
	CTitle(void);

	// �f�X�g���N�^
	~CTitle(void) = default;

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �`��
	void Draw(void) override;

	// ���
	void Finalize(void) override;
};