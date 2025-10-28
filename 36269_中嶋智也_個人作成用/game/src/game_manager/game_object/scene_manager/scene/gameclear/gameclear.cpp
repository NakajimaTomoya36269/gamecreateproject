#include "gameclear.h"
#include "../../scene_manager.h"

const int CGameClear::m_font_size = 40;

CGameClear::CGameClear(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CGameClear::Initialize(void)
{
}

void CGameClear::Update(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_scene_key = keyboard::Trigger(keyboard::KEY_ID::NUMPADENTER);
	if (change_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}
}

void CGameClear::Draw(void)
{
#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GameClearScene", m_Position);
#endif
}

void CGameClear::Finalize(void)
{
}
