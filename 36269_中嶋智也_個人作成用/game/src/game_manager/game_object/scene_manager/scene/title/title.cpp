#include "title.h"
#include "../../scene_manager.h"

const int CTitle::m_font_size = 40;

CTitle::CTitle(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CTitle::Initialize(void)
{
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
#ifdef _DEBUG
	vivid::DrawText(m_font_size, "TitleScene", m_Position);
#endif
}

void CTitle::Finalize(void)
{
}
