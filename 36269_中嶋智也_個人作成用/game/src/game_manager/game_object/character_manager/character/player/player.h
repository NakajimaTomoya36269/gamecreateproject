#pragma once

#include "vivid.h"
#include "../character.h"

class CPlayer : public ICharacter
{
public:
	// �R���X�g���N�^
	CPlayer(void);

	// �f�X�g���N�^
	~CPlayer(void);

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

	void Jump(void) override;

	static const int m_width;						// ��
	static const int m_height;						// ����
	static const int m_max_life;					// �ő僉�C�t
	static const float m_radius;					// ���a
	static const vivid::Vector2 m_start_position;	// �����ʒu
	static const float m_jump_power;				// �W�����v��

	vivid::Vector2	m_Jump;							// �W�����v

};