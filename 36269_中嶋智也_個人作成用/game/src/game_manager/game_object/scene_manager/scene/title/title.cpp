#include "title.h"
#include "../../scene_manager.h"

const int CTitle::m_font_size = 40;
const int CTitle::m_title_font_size = 100;
const int CTitle::m_enter_font_size = 60;

CTitle::CTitle(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_TitlePosition(vivid::Vector2(710.0f, 440.0f))
	, m_EnterPosition(vivid::Vector2(604.0f, 790.0f))
{
}

void CTitle::Initialize(void)
{
	vivid::CreateFont(m_title_font_size, 5);
	vivid::CreateFont(m_enter_font_size, 3);
}

void CTitle::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);

	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
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

void CTitle::Draw(void)
{

	vivid::DrawText(m_title_font_size, "Reverse\nGravity", m_TitlePosition);

	vivid::DrawText(m_enter_font_size, "Push Enter to Start", m_EnterPosition);

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "TitleScene", m_Position);

	vivid::DrawText(40, std::to_string(m_EnterPosition.x), vivid::Vector2(0.0f, 80.0f));
	vivid::DrawText(40, std::to_string(m_EnterPosition.y), vivid::Vector2(0.0f, 120.0f));
#endif
}

void CTitle::Finalize(void)
{
}
