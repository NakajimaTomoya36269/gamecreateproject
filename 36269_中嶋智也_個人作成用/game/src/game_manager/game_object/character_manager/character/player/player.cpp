#include "player.h"
#include "../../../box_collider/box_collider.h"
#include "../../../stage_manager/stage_manager.h"

const int CPlayer::m_width = 128;
const int CPlayer::m_height = 256;
const int CPlayer::m_max_life = 1;
const float CPlayer::m_radius = 64.0f;
const vivid::Vector2 CPlayer::m_start_position = vivid::Vector2(0.0f, 0.0f);
const float CPlayer::m_jump_power = 10.0f;

CPlayer::CPlayer(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::PLAYER, CHARACTER_ID::PLAYER)
	, m_JumpKey(vivid::keyboard::KEY_ID::UP)
	, m_JumpButton(vivid::controller::BUTTON_ID::B)
	, m_Jump(vivid::Vector2(0.0f, 0.0f))
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Initialize(const vivid::Vector2& position)
{
	(void)position;
	ICharacter::Initialize(m_start_position);

	m_Life = m_MaxLife = m_max_life;

	m_Jump = vivid::Vector2(0.0f, m_jump_power);
}

void CPlayer::Update(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool jump = keyboard::Trigger(m_JumpKey) || 
		controller::Trigger(controller::DEVICE_ID::PLAYER1, m_JumpButton);

	if (jump && m_IsGround)
	{
		m_Velocity.y -= m_Jump.y;
	}

	m_Position.y += m_Velocity.y;

	ICharacter::Update();
}

void CPlayer::Draw(void)
{
	vivid::DrawTexture("data\\player.png", m_Position);
	vivid::DrawText(40, std::to_string(m_Position.y), vivid::Vector2(0.0f, 0.0f));
}

void CPlayer::Finalize(void)
{
}

bool CPlayer::OnGround(CStage* stage)
{
	//const float height = (float)(stage->GetPosition().y - (float)stage->GetHeight());

	if (!stage)return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_width, m_height,
		stage->GetPosition(), stage->GetWidth(), stage->GetHeight()))
	{
		if (m_Position.y >= stage->GetPosition().y)
		{
			m_Position.y = (float)(m_Position.y - m_height - stage->GetHeight());

			m_Velocity.y = 0.0f;

			m_IsGround = true;
		}
	}
	else
	{
		m_IsGround = false;

		m_Velocity.y += m_Gravity;
	}

	return m_IsGround;
}

void CPlayer::Alive(void)
{

}

void CPlayer::Dead(void)
{
}
