#pragma once

#include "vivid.h"

class CBoxCollider
{
public:
	// �C���X�^���X�̎擾
	static CBoxCollider& GetInstance(void);

	bool CheckBoxCollision(const vivid::Vector2& box_position1, const int box_width1, const int box_height1,
							const vivid::Vector2& box_position2, const int box_width2, const int box_height2);

private:
	// �R���X�g���N�^
	CBoxCollider(void) = default;

	// �R�s�[�R���X�g���N�^
	CBoxCollider(const CBoxCollider& rhs) = delete;

	// �f�X�g���N�^
	~CBoxCollider(void) = default;

	// ������Z�q
	CBoxCollider operator=(const CBoxCollider& rhs) = delete;
};