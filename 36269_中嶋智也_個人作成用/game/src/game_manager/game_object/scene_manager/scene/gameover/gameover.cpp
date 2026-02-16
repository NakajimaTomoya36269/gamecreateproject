#include "gameover.h"
#include "../../scene_manager.h"

const int CGameOver::m_font_size = 40;
const int CGameOver::m_enter_font_size = 60;

CGameOver::CGameOver(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_EnterPosition(vivid::Vector2(608.0f, 800.0f))
{
}

void CGameOver::Initialize(void)
{
	vivid::CreateFont(m_enter_font_size, 6);
}

void CGameOver::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);
	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}
}

void CGameOver::Draw(void)
{
	vivid::DrawTexture("data\\background.png", vivid::Vector2(0.0f, 0.0f));

	vivid::DrawTexture("data\\gameover.png", vivid::Vector2(543.0f, 250.0f));

	vivid::DrawText(m_enter_font_size, "Push Enter to Title", m_EnterPosition);
	
}

void CGameOver::Finalize(void)
{
}
