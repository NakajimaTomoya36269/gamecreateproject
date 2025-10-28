#pragma once

#include "vivid.h"
#include "character_id.h"

class CStage;

enum class CHARACTER_STATE
{
	ALIVE,
	DEAD,
};

class ICharacter
{
public:
	// �R���X�g���N�^
	ICharacter(int width, int height, float radius, int life, 
				CHARACTER_CATEGORY category, CHARACTER_ID character_id);

	// �f�X�g���N�^
	virtual ~ICharacter(void);

	// ������
	virtual void Initialize(const vivid::Vector2& position);

	// �X�V
	virtual void Update(void);

	// �`��
	virtual void Draw(void);

	// ���
	virtual void Finalize(void);

	// �n�ʂ̏�ɂ��锻��
	virtual bool OnGround(CStage* stage);

	// �W�����v
	virtual void Jump(void);

	// �d�͕ύX
	virtual void ChangeGravity(void);

	// �V��ɂ������Ă��邩�̔���
	virtual void CheckHitCeiling(CStage* stage);

	// �L�����N�^�[ID�̎擾
	CHARACTER_ID GetCharacterID(void);

	// �J�e�S���[�̎擾
	CHARACTER_CATEGORY GetCategory(void);

	// �ʒu�̎擾
	vivid::Vector2 GetPosition(void);
	
	// �ʒu�̐ݒ�
	void SetPosition(const vivid::Vector2 position);

	// ���̎擾
	int GetWidth(void);

	// �����̎擾
	int GetHeight(void);

	// �A�N�e�B�u�t���O�̎擾
	bool GetActive(void);

	// �A�N�e�B�u�t���O�̐ݒ�
	void SetActive(bool active);

	// ���C�t�̎擾
	int GetMaxLife(void);

	// ���C�t�̐ݒ�
	int GetLife(void);

	// �d�͂̎擾
	float GetGravity(void);

	// �d�͂̐ݒ�
	void SetGravity(float gravity);

	// �d�͕ύX�t���O�̎擾
	bool GetGravityChange(void);

	// �d�͕ύX�t���O�̐ݒ�
	void SetGravityChange(bool gravity);

protected:
	// ����
	virtual void Alive(void);

	// ���S
	virtual void Dead(void);

	vivid::Vector2		m_Position;		// �ʒu
	vivid::Vector2		m_Velocity;		// ����
	vivid::Rect			m_Rect;			// �\���͈�
	vivid::Vector2		m_Anchor;		// ���S
	int  				m_Width;		// ��
	int				    m_Height;		// ����
	int					m_Life;			// ���C�t
	int					m_MaxLife;		// �ő僉�C�t
	float				m_Radius;		// ���a
	float				m_Gravity;		// �d��
	bool				m_Active;		// �A�N�e�B�u�t���O
	bool				m_IsGround;		// �n�ʂ̏�ɂ��锻��
	bool				m_GravityChange;// �d�͕ύX�t���O
	CHARACTER_CATEGORY  m_Category;		// �J�e�S���[
	CHARACTER_ID		m_CharacterID;	// �L�����N�^�[ID
	CHARACTER_STATE		m_State;		// ���

	static const float  m_move_speed;	// ��������
	static const float  m_gravity_speed;// �d�͂̋���
};