#include "title.h"
#include "../../scene_manager.h"

const int CTitle::m_font_size = 40;
const int CTitle::m_title_font_size = 100;

CTitle::CTitle(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_TitlePosition(vivid::Vector2((vivid::WINDOW_WIDTH - m_title_font_size * 7.0f) / 2.0f,
										(vivid::WINDOW_HEIGHT - m_title_font_size * 2.0f) / 2.0f))
{
}

void CTitle::Initialize(void)
{
	vivid::CreateFont(m_title_font_size, 5);
}

void CTitle::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);

	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEMAIN);
	}
}

void CTitle::Draw(void)
{

	vivid::DrawText(m_title_font_size, "Reverse\nGravity", m_TitlePosition);

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "TitleScene", m_Position);
#endif
}

void CTitle::Finalize(void)
{
}
