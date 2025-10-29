#pragma once

#include "../character.h"
#include "vivid.h"

class CEnemyA
	: public ICharacter
{
public:
	// �R���X�g���N�^
	CEnemyA(void);

	// �f�X�g���N�^
	~CEnemyA(void) = default;

	// ������
	void Initialize(const vivid::Vector2& position) override;

	// �X�V
	void Update(void) override;

	// �`��
	void Draw(void) override;

	// ���
	void Finalize(void) override;

	// �n�ʂ̏�ɂ��锻��
	bool OnGround(CStage* stage)override;

private:
	// ����
	void Alive(void) override;

	// ���S
	void Dead(void) override;

	static const int		m_width;		// ��
	static const int		m_height;		// ����
	static const float		m_radius;		// ���a
	static const int		m_max_life;		// �ő僉�C�t
	static const float		m_move_speed;	// �ړ��̑���
	static const float		m_friction;		// ���C��

	vivid::Vector2			m_Position;		// �ʒu
};
