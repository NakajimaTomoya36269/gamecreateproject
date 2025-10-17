#pragma once

class IScene
{
public:
	// �R���X�g���N�^
	IScene(void);

	// �f�X�g���N�^
	virtual ~IScene(void);

	// ������
	virtual void Initialize(void);

	// �X�V
	virtual void Update(void);

	// �`��
	virtual void Draw(void);

	// ���
	virtual void Finalize(void);
};