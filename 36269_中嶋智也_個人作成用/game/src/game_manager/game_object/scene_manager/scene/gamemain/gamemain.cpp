#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../../enemy_manager/enemy_manager.h"
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
	CEnemyManager& enemy_manager = CEnemyManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
	stage_manager.Initialize();
	for (int i = 0; i < 5; i++)
	{
		stage_manager.Create(vivid::Vector2(i * 300.0f, 1016.0f));
		stage_manager.Create(vivid::Vector2(i * 300.0f, 0.0f));
	}
	stage_manager.Create(vivid::Vector2(0.0f, 600.0f));
	//stage_manager.Create(vivid::Vector2(0.0f, 952.0f));

	enemy_manager.Initialize();
	enemy_manager.Create(ENEMY_ID::ENEMYA, vivid::Vector2(0.0f, 976.0f));
	enemy_manager.Create(ENEMY_ID::ENEMYA, vivid::Vector2(400.0f, 976.0f));
	enemy_manager.Create(ENEMY_ID::ENEMYA, vivid::Vector2(600.0f, 976.0f));

	m_goal.Initialize(vivid::Vector2(0.0f, 472.0f));
}

void CGamemain::Update(void)
{
	CStageManager::GetInstance().Update();
	CCharacterManager::GetInstance().Update();
	CEnemyManager::GetInstance().Update();
	if (CStageManager::GetInstance().OnGround())
	{
		CCharacterManager::GetInstance().ChangeGravity();
	}

	if (CCharacterManager::GetInstance().CheckHitGoal(m_goal))
	{
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMECLEAR);
	}
	m_goal.Update();

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
	CStageManager::GetInstance().Draw();
	m_goal.Draw();
	CEnemyManager::GetInstance().Draw();
	CCharacterManager::GetInstance().Draw();

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GamemainScene", m_Position);
#endif 

}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
	CEnemyManager::GetInstance().Finalize();
	m_goal.Finalize();
}
