#include "player.h"

const int CPlayer::m_width = 128;
const int CPlayer::m_height = 256;
const int CPlayer::m_max_life = 1;
const float CPlayer::m_radius = 64.0f;
const vivid::Vector2 CPlayer::m_start_position = vivid::Vector2(0.0f, 0.0f);

CPlayer::CPlayer(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::PLAYER, CHARACTER_ID::PLAYER)
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
}

void CPlayer::Update(void)
{
	ICharacter::Update();
}

void CPlayer::Draw(void)
{
	vivid::DrawTexture("data\\player.png", m_Position);
}

void CPlayer::Finalize(void)
{
}

void CPlayer::Alive(void)
{

}

void CPlayer::Dead(void)
{
}
