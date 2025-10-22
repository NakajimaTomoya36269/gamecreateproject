#pragma once
#include "vivid.h"

class CStage
{
public:
	// �R���X�g���N�^
	CStage(void);

	// �f�X�g���N�^
	~CStage(void) = default;

	// ������
	void Initialize(const vivid::Vector2& position);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// ���
	void Finalize(void);

	// ���̎擾
	int GetWidth(void);

	// �����̎擾
	int GetHeight(void);

	// �ʒu�̎擾
	vivid::Vector2 GetPosition(void);

private:
	static const int	m_width;
	static const int	m_height;
	static const float	m_scroll_speed;
	static const float	m_friction;

	vivid::Vector2		m_Position;
	vivid::Vector2		m_Velocity;
};