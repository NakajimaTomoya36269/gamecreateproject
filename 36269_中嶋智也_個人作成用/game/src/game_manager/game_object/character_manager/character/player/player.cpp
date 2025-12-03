#include "player.h"
#include "../../../scene_manager/scene_manager.h"

const int CPlayer::m_width = 100;
const int CPlayer::m_height = 220;
const int CPlayer::m_max_life = 1;
const float CPlayer::m_radius = 64.0f;
const vivid::Vector2 CPlayer::m_start_position = vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, 240.0f);

CPlayer::CPlayer(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::PLAYER, CHARACTER_ID::PLAYER)
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
	const vivid::Vector2 scale = vivid::Vector2(1.0f, 1.0f);

	vivid::DrawTexture("data\\player.png", m_Position, 0xffffffff);
#ifdef _DEBUG
	vivid::DrawText(40, std::to_string(m_Position.y), vivid::Vector2(0.0f, 40.0f));
#endif 
}

void CPlayer::Finalize(void)
{
}

void CPlayer::Alive(void)
{
	if (m_GravityChange)
	{
		m_Position.y -= m_Velocity.y;
	}
	if (!m_GravityChange)
	{
		m_Position.y += m_Velocity.y;
	}
	if (m_Position.y < 0.0f || m_Position.y + m_Height >(float)vivid::WINDOW_HEIGHT || m_Life <= 0)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
}

void CPlayer::Dead(void)
{
	m_Active = false;
	CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
}
