#include "player.h"
#include "../../../box_collider/box_collider.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../../scene_manager/scene_manager.h"

const int CPlayer::m_width = 100;
const int CPlayer::m_height = 220;
const int CPlayer::m_max_life = 1;
const float CPlayer::m_radius = 64.0f;
const vivid::Vector2 CPlayer::m_start_position = vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, 240.0f);
const float CPlayer::m_jump_power = 40.0f;

CPlayer::CPlayer(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::PLAYER, CHARACTER_ID::PLAYER)
	, m_Jump(vivid::Vector2(0.0f, 0.0f))
	, m_Rotaition(0.0f)
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
	ICharacter::Update();
}

void CPlayer::Draw(void)
{
	vivid::DrawTexture("data\\player.png", m_Position, 0xffffffff, 
						m_Rect, m_Anchor, vivid::Vector2(1.0f, 1.0f), m_Rotaition);
#ifdef _DEBUG
	vivid::DrawText(40, std::to_string(m_Position.y), vivid::Vector2(0.0f, 40.0f));
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
		if (m_Position.y + m_height > stage->GetPosition().y && !m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y - (float)m_height;

			m_Velocity.y = 0.0f;

			return true;
		}
		else if (m_Position.y < stage->GetPosition().y + stage->GetHeight() && m_GravityChange)
		{
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			m_Velocity.y = 0.0f;

			return true;
		}
	}
	else
	{
		m_Velocity.y += m_Gravity;
	}

	return false;
}

void CPlayer::Alive(void)
{
	if (m_GravityChange)
	{
		m_Position.y -= m_Velocity.y;
		m_Rotaition = cos(270.0f * 3.14f / 180.0f);
	}
	if (!m_GravityChange)
	{
		m_Position.y += m_Velocity.y;
		m_Rotaition = cos(90.0f * 3.14f / 180.0f);
	}
	if (m_Position.y < 0.0f || m_Position.y >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
}

void CPlayer::Dead(void)
{
	CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
}

void CPlayer::Jump(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool jump_key = keyboard::Trigger(keyboard::KEY_ID::UP);
	bool jump_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B);

	bool jump = jump_key || jump_button;

	if (jump)
	{
		m_Velocity.y -= m_Jump.y;
	}

	if (!m_GravityChange)
		m_Position.y += m_Velocity.y * vivid::GetDeltaTime();
	else
		m_Position.y -= m_Velocity.y * vivid::GetDeltaTime();
}

void CPlayer::ChangeGravity(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	bool gravity_change_key = keyboard::Trigger(keyboard::KEY_ID::SPACE);
	bool gravity_change_button = controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A);

	bool gravity_change = gravity_change_key || gravity_change_button;

	if (gravity_change)
	{
		m_GravityChange = !m_GravityChange;
	}
}
