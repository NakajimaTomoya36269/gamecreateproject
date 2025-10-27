#pragma once

#include "vivid.h"
#include <list>
#include "character/character.h"
#include "character/character_id.h"
#include "../stage_manager/stage_manager.h"

class CCharacterManager
{
public:
	// �C���X�^���X�̎擾
	static CCharacterManager& GetInstance(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// ���
	void Finalize(void);

	// �L�����N�^�[�쐬
	void Create(CHARACTER_ID id, const vivid::Vector2& position);

	// �n�ʂ̏�ɂ��邩�̔���
	bool OnGround(CStage* stage);
	
	// �W�����v
	void Jump(void);

	// �d�͕ύX
	void ChangeGravity(void);

private:
	// �R���X�g���N�^
	CCharacterManager(void) = default;

	// �R�s�[�R���X�g���N�^
	CCharacterManager(const CCharacterManager& rhs) = delete;

	// �f�X�g���N�^
	~CCharacterManager(void) = default;
	
	// ������Z�q
	CCharacterManager operator=(const CCharacterManager& rhs) = delete;

	// �L�����N�^�[���X�g�^
	using CHARACTER_LIST = std::list<ICharacter*>;

	CHARACTER_LIST m_CharacterList;		// �L�����N�^�[���X�g
};