#include "gameover.h"
#include "../../scene_manager.h"

const int CGameOver::m_font_size = 40;

CGameOver::CGameOver(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CGameOver::Initialize(void)
{
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
#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GameOverScene", m_Position);
#endif 

}

void CGameOver::Finalize(void)
{
}
