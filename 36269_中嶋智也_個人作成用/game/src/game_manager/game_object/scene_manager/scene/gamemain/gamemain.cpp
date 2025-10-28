#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../scene_manager.h"

const int CGamemain::m_font_size = 40;

CGamemain::CGamemain(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CGamemain::Initialize(void)
{
	CCharacterManager& character_manager = CCharacterManager::GetInstance();
	CStageManager& stage_manager = CStageManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
	stage_manager.Initialize();
	for (int i = 0; i < 5; i++)
	{
		CStageManager::GetInstance().Create(vivid::Vector2(i * 300.0f, 1016.0f));
		CStageManager::GetInstance().Create(vivid::Vector2(i * 300.0f, 0.0f));
	}
	CStageManager::GetInstance().Create(vivid::Vector2(0.0f, 600.0f));
}

void CGamemain::Update(void)
{
	CStageManager::GetInstance().Update();
	CCharacterManager::GetInstance().Update();
	if (CStageManager::GetInstance().GetIsGround())
	{
		CCharacterManager::GetInstance().ChangeGravity();
		//CCharacterManager::GetInstance().Jump();
	}

	namespace keyboard = vivid::keyboard;
	bool change_gameover_scene_key = keyboard::Trigger(keyboard::KEY_ID::Z);
	bool change_gameclear_scene_key = keyboard::Trigger(keyboard::KEY_ID::X);

#ifdef _DEBUG
	if (change_gameover_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
	}
	if (change_gameclear_scene_key)
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	}
#endif
}

void CGamemain::Draw(void)
{
	CStageManager::GetInstance().Draw();
	CCharacterManager::GetInstance().Draw();

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GamemainScene", m_Position);
#endif 

}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
}
