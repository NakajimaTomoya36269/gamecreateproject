#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../../enemy_manager/enemy_manager.h"
#include "../../../item_manager/item_manager.h"
#include "../../../switch_manager/switch_manager.h"
#include "../../scene_manager.h"

const int CGamemain::m_font_size = 40;

CGamemain::CGamemain(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CGamemain::Initialize(void)
{
	CCharacterManager& character_manager = CCharacterManager::GetInstance();
	CSwitchManager& switch_manager = CSwitchManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
	CStageManager::GetInstance().Initialize();

	CEnemyManager::GetInstance().Initialize();

	m_goal.Initialize(vivid::Vector2(4100.0f, 472.0f));

	CItemManager::GetInstance().Initialize();

	switch_manager.Initialize();
	switch_manager.Create(SWITCH_ID::FLOOR_SWITCH, vivid::Vector2(3400.0f, 900.0f));
	switch_manager.Create(SWITCH_ID::FLOOR_SWITCH , vivid::Vector2(3000.0f, 900.0f));

	m_background.Initialize();
}

void CGamemain::Update(void)
{
	CStageManager::GetInstance().Update();
	//CStageManager::GetInstance().OnGround();
	//CStageManager::GetInstance().EnemyOnGround();
	CCharacterManager::GetInstance().Update();
	//CCharacterManager::GetInstance().CheckHitCharacter();
	CEnemyManager::GetInstance().Update();
	CSwitchManager::GetInstance().Update();

	if (CCharacterManager::GetInstance().CheckHitGoal(m_goal))
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	}
	m_goal.Update();

	CItemManager::GetInstance().Update();

	m_background.Update();

	namespace keyboard = vivid::keyboard;
	bool change_gameover_scene_key = keyboard::Trigger(keyboard::KEY_ID::Z);
	bool change_gameclear_scene_key = keyboard::Trigger(keyboard::KEY_ID::X);
	bool reset_key = keyboard::Trigger(keyboard::KEY_ID::R);

	if (reset_key)
	{
		Finalize();
		Initialize();
	}

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
	m_background.Draw();
	CStageManager::GetInstance().Draw();
	m_goal.Draw();
	CItemManager::GetInstance().Draw();
	CEnemyManager::GetInstance().Draw();
	CCharacterManager::GetInstance().Draw();
	CSwitchManager::GetInstance().Draw();

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GamemainScene", m_Position);
#endif 

}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
	CEnemyManager::GetInstance().Finalize();
	CItemManager::GetInstance().Finalize();
	CSwitchManager::GetInstance().Finalize();
	m_goal.Finalize();
	m_background.Finalize();
}
