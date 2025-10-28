#pragma once
#include "../scene.h"
#include "vivid.h"

class CGameOver
	: public IScene
{
public:
	// �R���X�g���N�^
	CGameOver(void);

	// �f�X�g���N�^
	~CGameOver(void) = default;

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �`��
	void Draw(void) override;

	// ���
	void Finalize(void) override;

private:
	static const int	m_font_size;		// �t�H���g�T�C�Y

	vivid::Vector2		m_Position;			// �ʒu
};