#include "player.h"
#include "../../../box_collider/box_collider.h"
#include "../../../stage_manager/stage_manager.h"

const int CPlayer::m_width = 100;
const int CPlayer::m_height = 220;
const int CPlayer::m_max_life = 1;
const float CPlayer::m_radius = 64.0f;
const vivid::Vector2 CPlayer::m_start_position = vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, 0.0f);
const float CPlayer::m_jump_power = 30.0f;

CPlayer::CPlayer(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::PLAYER, CHARACTER_ID::PLAYER)
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

	bool jump_key = keyboard::Trigger(keyboard::KEY_ID::UP);
	bool jump_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B);

	bool jump = jump_key || jump_button;

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
#ifdef _DEBUG
	vivid::DrawText(40, std::to_string(m_Position.y), vivid::Vector2(0.0f, 0.0f));
#endif 
}

void CPlayer::Finalize(void)
{
}

bool CPlayer::OnGround(CStage* stage)
{
	if (!stage)return false;

	if (CBoxCollider::GetInstance().CheckBoxCollision(m_Position, m_width, m_height,
		stage->GetPosition(), stage->GetWidth(), stage->GetHeight()))
	{
		if (m_Position.y + m_height >= stage->GetPosition().y)
		{
			m_Position.y = stage->GetPosition().y - (float)m_height;

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
