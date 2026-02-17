#include "character_manager.h"
#include "character/player/player.h"
#include "../enemy_manager/enemy_manager.h"
#include "../stage_manager/stage_manager.h"
#include "../item_manager/item_manager.h"
#include "../switch_manager/switch_manager.h"
#include "../bullet_manager/bullet_manager.h"

/*
================================
  シングルトン取得
================================
*/
CCharacterManager& CCharacterManager::GetInstance(void)
{
	static CCharacterManager instance;	// 唯一のインスタンス

	return instance;
}

/*
================================
  初期化
  キャラクターリストを空にする
================================
*/
void CCharacterManager::Initialize(void)
{
	m_CharacterList.clear();
}

/*
================================
  更新処理
  ・各キャラクターの更新
  ・敵の攻撃判定
  ・非アクティブになったキャラの削除
================================
*/
void CCharacterManager::Update(void)
{
	if (m_CharacterList.empty()) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		ICharacter* character = (ICharacter*)(*it);

		// キャラクター自身の更新
		character->Update();

		// 敵からの攻撃判定
		CEnemyManager::GetInstance().Attack(character);

		// 非アクティブなら削除
		if (!character->GetActive())
		{
			character->Finalize();
			delete character;

			it = m_CharacterList.erase(it);
			continue;
		}
		++it;
	}
}

/*
================================
  描画処理
  全キャラクターを描画
================================
*/
void CCharacterManager::Draw(void)
{
	if (m_CharacterList.empty()) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->Draw();
	}
}

/*
================================
  終了処理
  全キャラクターを解放
================================
*/
void CCharacterManager::Finalize(void)
{
	if (m_CharacterList.empty()) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->Finalize();
		delete (*it);
	}
	m_CharacterList.clear();
}

/*
================================
  キャラクター生成
  IDに応じて生成するキャラを切り替える
================================
*/
void CCharacterManager::Create(CHARACTER_ID id, const vivid::Vector2& position)
{
	ICharacter* character = nullptr;

	switch (id)
	{
	case CHARACTER_ID::PLAYER:
		character = new CPlayer();
		break;
	}

	if (!character) return;

	character->Initialize(position);
	m_CharacterList.push_back(character);
}

/*
================================
  地面に接地しているか判定
  1人でも接地していれば true
================================
*/
bool CCharacterManager::OnGround(IStage* stage)
{
	if (!stage) return false;

	bool anyGrounded = false;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->OnGround(stage))
			anyGrounded = true;
	}
	return anyGrounded;
}

/*
================================
  天井との当たり判定
================================
*/
bool CCharacterManager::CheckHitCeiling(IStage* stage)
{
	if (!stage) return false;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitCeiling(stage))
			return true;
	}
	return false;
}

/*
================================
  右壁との当たり判定
================================
*/
bool CCharacterManager::CheckHitRightWall(IStage* stage)
{
	if (!stage) return false;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitRightWall(stage))
			return true;
	}
	return false;
}

/*
================================
  左壁との当たり判定
================================
*/
bool CCharacterManager::CheckHitLeftWall(IStage* stage)
{
	if (!stage) return false;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitLeftWall(stage))
			return true;
	}
	return false;
}

/*
================================
  敵との当たり判定
================================
*/
void CCharacterManager::CheckHitEnemy(IEnemy* enemy)
{
	if (!enemy) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitEnemy(enemy))
			return;
	}
}

/*
================================
  ジャンプ処理
================================
*/
void CCharacterManager::Jump(IStage* stage)
{
	if (!stage) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->Jump(stage);
	}
}

/*
================================
  重力反転処理
================================
*/
void CCharacterManager::ChangeGravity(IStage* stage)
{
	if (!stage) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->ChangeGravity(stage);
	}
}

/*
================================
  ゴール判定
================================
*/
bool CCharacterManager::CheckHitGoal(CGoal& goal)
{
	if (m_CharacterList.empty()) return false;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitGoal(goal))
			return true;
	}
	return false;
}

/*
================================
  アイテム取得判定
================================
*/
void CCharacterManager::CheckHitItem(IItem* item)
{
	if (!item) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitItem(item))
			return;
	}
}

/*
================================
  弾との当たり判定
================================
*/
void CCharacterManager::CheckHitBullet(IBullet* bullet)
{
	if (!bullet) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if ((*it)->CheckHitBullet(bullet))
			return;
	}
}

/*
================================
  ジャンプ力アップ処理
================================
*/
void CCharacterManager::JumpUp(IItem* item)
{
	if (!item) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->JumpUp(item);
	}
}

/*
================================
  無敵化処理
================================
*/
void CCharacterManager::Invincible(IItem* item)
{
	if (!item) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->Invincible(item);
	}
}

/*
================================
  スイッチとの当たり判定
================================
*/
void CCharacterManager::CheckHitSwitch(ISwitch* sw)
{
	if (!sw) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->CheckHitSwitch(sw);
	}
}

/*
================================
  落下床処理
================================
*/
void CCharacterManager::FallStage(IStage* stage)
{
	if (!stage) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		(*it)->FallStage(stage);
	}
}

/*
================================
  キャラクター同士の当たり判定
================================
*/
void CCharacterManager::CheckHitCharacter(void)
{
	if (m_CharacterList.empty()) return;

	for (auto it = m_CharacterList.begin(); it != m_CharacterList.end(); ++it)
	{
		if (CStageManager::GetInstance().CheckHitCharacter(
			(*it), (*it)->GetPositionX()))
		{
			return;
		}
	}
}
