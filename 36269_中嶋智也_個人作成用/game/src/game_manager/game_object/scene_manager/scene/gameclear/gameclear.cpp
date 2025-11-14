#include "gameclear.h"
#include "../../scene_manager.h"

const int CGameClear::m_font_size = 40;
const int CGameClear::m_gameclear_font_size = 200;
const int CGameClear::m_enter_font_size = 60;

CGameClear::CGameClear(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_GameClearPosition(vivid::Vector2(300.0f, 440.0f))
	, m_EnterPosition(vivid::Vector2(608.0f, 800.0f))
{
}

void CGameClear::Initialize(void)
{
	vivid::CreateFont(m_gameclear_font_size, 8);
	vivid::CreateFont(m_enter_font_size, 6);
}

void CGameClear::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);
	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}

#ifdef _DEBUG
	if (keyboard::Button(keyboard::KEY_ID::UP))
	{
		m_EnterPosition.y -= 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::DOWN))
	{
		m_EnterPosition.y += 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::RIGHT))
	{
		m_EnterPosition.x += 1.0f;
	}
	if (keyboard::Button(keyboard::KEY_ID::LEFT))
	{
		m_EnterPosition.x -= 1.0f;
	}
#endif 

}

void CGameClear::Draw(void)
{
	vivid::DrawText(m_gameclear_font_size, "GameClear", m_GameClearPosition, 0xff0000aa);

	vivid::DrawText(m_enter_font_size, "Push Enter to Title", m_EnterPosition);

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GameClearScene", m_Position);

	vivid::DrawText(40, std::to_string(m_EnterPosition.x), vivid::Vector2(0.0f, 40.0f));
	vivid::DrawText(40, std::to_string(m_EnterPosition.y), vivid::Vector2(0.0f, 80.0f));
#endif
}

void CGameClear::Finalize(void)
{
}
