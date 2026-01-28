#include "gamemain.h"
#include "../../../character_manager/character_manager.h"
#include "../../../stage_manager/stage_manager.h"
#include "../../../enemy_manager/enemy_manager.h"
#include "../../../item_manager/item_manager.h"
#include "../../../switch_manager/switch_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../scene_manager.h"

const int CGamemain::m_font_size = 40;

CGamemain::CGamemain(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_CurrentStateID(GAMEMAIN_STATE_ID::PLAY)
{
}

void CGamemain::Initialize(void)
{
	m_CurrentStateID = GAMEMAIN_STATE_ID::PLAY;

	CCharacterManager& character_manager = CCharacterManager::GetInstance();

	character_manager.Initialize();
	character_manager.Create(CHARACTER_ID::PLAYER, vivid::Vector2(0.0f, 0.0f));
	CStageManager::GetInstance().Initialize();

	CEnemyManager::GetInstance().Initialize();

	m_goal.Initialize(vivid::Vector2(4100.0f, 472.0f));

	CItemManager::GetInstance().Initialize();

	CSwitchManager::GetInstance().Initialize();

	m_background.Initialize();

	CBulletManager::GetInstance().Initialize();
}

void CGamemain::Update(void)
{
	ChangeState();

	switch (m_CurrentStateID)
	{
	case GAMEMAIN_STATE_ID::PLAY:
		UpdatePlay();
		break;
	case GAMEMAIN_STATE_ID::PAUSE:
		UpdatePause();
		break;
	}
}

void CGamemain::Draw(void)
{
	m_background.Draw();
	CStageManager::GetInstance().Draw();
	m_goal.Draw();
	CItemManager::GetInstance().Draw();
	CEnemyManager::GetInstance().Draw();
	CBulletManager::GetInstance().Draw();
	CCharacterManager::GetInstance().Draw();
	CSwitchManager::GetInstance().Draw();

	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PAUSE)
	{
		vivid::DrawTexture("data\\pause.png", vivid::Vector2(192.0f, 0.0f));
		vivid::DrawTexture("data\\pause_select.png", vivid::Vector2(768.0f, 750.0f));
	}

#ifdef _DEBUG
	vivid::DrawText(m_font_size, "GamemainScene", vivid::Vector2(0.0f, 0.0f));
#endif 

}

void CGamemain::Finalize(void)
{
	CCharacterManager::GetInstance().Finalize();
	CStageManager::GetInstance().Finalize();
	CEnemyManager::GetInstance().Finalize();
	CItemManager::GetInstance().Finalize();
	CSwitchManager::GetInstance().Finalize();
	CBulletManager::GetInstance().Finalize();
	m_goal.Finalize();
	m_background.Finalize();
}

void CGamemain::UpdatePlay(void)
{
	CStageManager::GetInstance().Update();
	CCharacterManager::GetInstance().Update();
	CEnemyManager::GetInstance().Update();
	CSwitchManager::GetInstance().Update();
	CBulletManager::GetInstance().Update();

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

void CGamemain::UpdatePause(void)
{
}

void CGamemain::ChangeState(void)
{
	namespace keyboard = vivid::keyboard;
	bool change_pause_state_key = keyboard::Trigger(keyboard::KEY_ID::P);
	bool change_title_scene_key = keyboard::Trigger(keyboard::KEY_ID::T);
	bool change_play_state_key = keyboard::Trigger(keyboard::KEY_ID::S);

	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PLAY && change_pause_state_key)
	{
		m_CurrentStateID = GAMEMAIN_STATE_ID::PAUSE;
	}

	if (m_CurrentStateID == GAMEMAIN_STATE_ID::PAUSE)
	{
		if (change_play_state_key)
		{
			m_CurrentStateID = GAMEMAIN_STATE_ID::PLAY;
		}
		if (change_title_scene_key)
		{
			CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		}
	}
}
