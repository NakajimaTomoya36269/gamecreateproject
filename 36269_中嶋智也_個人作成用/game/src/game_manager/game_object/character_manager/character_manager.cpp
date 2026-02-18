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
	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		ICharacter* character = it->get();

		// キャラクター自身の更新
		character->Update();

		// 敵からの攻撃判定
		CEnemyManager::GetInstance().Attack(character);

		// 非アクティブなら削除
		if (!character->GetActive())
		{
			character->Finalize();

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
	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Draw();

		++it;
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
	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Finalize();

		++it;
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
	std::unordered_map<CHARACTER_ID, CreateFunc>::iterator it = m_CreateMap.find(id);
	
	if (it == m_CreateMap.end())
		return;

	std::unique_ptr<ICharacter> character = it->second();

	if (!character) return;

	character->Initialize(position);
	m_CharacterList.push_back(std::move(character));
}

/*
================================
  地面に接地しているか判定
================================
*/
void CCharacterManager::OnGround(IStage* stage)
{
	if (!stage) return;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->OnGround(stage);

		++it;
	}
}

/*
================================
  天井との当たり判定
================================
*/
bool CCharacterManager::CheckHitCeiling(IStage* stage)
{
	if (!stage) return false;

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitCeiling(stage))
			return true;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitRightWall(stage))
			return true;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitLeftWall(stage))
			return true;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitEnemy(enemy))
			return;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Jump(stage);

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->ChangeGravity(stage);

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitGoal(goal))
			return true;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitItem(item))
			return;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		if ((*it)->CheckHitBullet(bullet))
			return;

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->JumpUp(item);

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->Invincible(item);

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->CheckHitSwitch(sw);

		++it;
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

	CHARACTER_LIST::iterator it = m_CharacterList.begin();
	CHARACTER_LIST::iterator end = m_CharacterList.end();

	while (it != end)
	{
		(*it)->FallStage(stage);

		++it;
	}
}

CCharacterManager::CCharacterManager(void)
{
	RegisterCharacters();
}

void CCharacterManager::RegisterCharacters(void)
{
	m_CreateMap[CHARACTER_ID::PLAYER] =
		[]() {return std::make_unique<CPlayer>(); };
}
