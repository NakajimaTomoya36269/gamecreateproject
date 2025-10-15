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

private:
	// ����
	void Alive(void) override;

	// ���S
	void Dead(void) override;

	static const int m_width;
	static const int m_height;
	static const int m_max_life;
	static const float m_radius;
	static const vivid::Vector2 m_start_position;

};