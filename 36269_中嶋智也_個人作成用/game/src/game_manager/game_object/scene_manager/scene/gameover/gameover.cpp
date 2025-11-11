#include "gameover.h"
#include "../../scene_manager.h"

const int CGameOver::m_font_size = 40;
const int CGameOver::m_gameover_font_size = 200;

CGameOver::CGameOver(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_GameOverPosition(vivid::Vector2(360.0f, 440.0f))
{
}

void CGameOver::Initialize(void)
{
	vivid::CreateFont(m_gameover_font_size, 8);
}

void CGameOver::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);
	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}

#ifdef _DEBUG

	if (keyboard::Button(keyboard::KEY_ID::RIGHT))
	{
		m_GameOverPosition.x += 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::LEFT))
	{
		m_GameOverPosition.x -= 1.0f;
	}

#endif 

}

void CGameOver::Draw(void)
{
	vivid::DrawText(m_gameover_font_size, "GameOver", m_GameOverPosition, 0xffff0000);
#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GameOverScene", m_Position);

	vivid::DrawText(40, std::to_string(m_GameOverPosition.x), vivid::Vector2(0.0f, 40.0f));
#endif 

}

void CGameOver::Finalize(void)
{
}
