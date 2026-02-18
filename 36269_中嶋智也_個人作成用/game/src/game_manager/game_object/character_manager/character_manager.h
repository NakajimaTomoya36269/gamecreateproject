#pragma once

#include "vivid.h"
#include <list>
#include <memory>
#include "character/character.h"
#include "character/character_id.h"

class IStage;
class IEnemy;
class IItem;
class ISwitch;
class IBullet;

/*
==================================================
  キャラクター管理クラス
  ・プレイヤーなど全キャラクターを一括管理
  ・更新 / 描画 / 当たり判定をまとめて処理
  ・シングルトンで使用する
==================================================
*/
class CCharacterManager
{
public:
	/*
	--------------------------------
	  インスタンス取得（シングルトン）
	--------------------------------
	*/
	static CCharacterManager& GetInstance(void);

	/*
	--------------------------------
	  初期化
	  キャラクターリストを空にする
	--------------------------------
	*/
	void Initialize(void);

	/*
	--------------------------------
	  更新処理
	  ・キャラクター更新
	  ・敵の攻撃処理
	  ・削除判定
	--------------------------------
	*/
	void Update(void);

	/*
	--------------------------------
	  描画処理
	  全キャラクターを描画
	--------------------------------
	*/
	void Draw(void);

	/*
	--------------------------------
	  終了処理
	  キャラクターの解放
	--------------------------------
	*/
	void Finalize(void);

	/*
	--------------------------------
	  キャラクター生成
	  IDに応じたキャラを生成
	--------------------------------
	*/
	void Create(CHARACTER_ID id, const vivid::Vector2& position);

	/*
	--------------------------------
	  地面に接地しているか判定
	  1体でも接地していれば true
	--------------------------------
	*/
	bool OnGround(IStage* stage);

	/*
	--------------------------------
	  天井との当たり判定
	--------------------------------
	*/
	bool CheckHitCeiling(IStage* stage);

	/*
	--------------------------------
	  右壁との当たり判定
	--------------------------------
	*/
	bool CheckHitRightWall(IStage* stage);

	/*
	--------------------------------
	  左壁との当たり判定
	--------------------------------
	*/
	bool CheckHitLeftWall(IStage* stage);

	/*
	--------------------------------
	  敵との当たり判定
	--------------------------------
	*/
	void CheckHitEnemy(IEnemy* enemy);

	/*
	--------------------------------
	  ジャンプ処理
	--------------------------------
	*/
	void Jump(IStage* stage);

	/*
	--------------------------------
	  重力反転処理
	--------------------------------
	*/
	void ChangeGravity(IStage* stage);

	/*
	--------------------------------
	  ゴール判定
	--------------------------------
	*/
	bool CheckHitGoal(CGoal& goal);

	/*
	--------------------------------
	  アイテム取得判定
	--------------------------------
	*/
	void CheckHitItem(IItem* item);

	/*
	--------------------------------
	  弾との当たり判定
	--------------------------------
	*/
	void CheckHitBullet(IBullet* bullet);

	/*
	--------------------------------
	  ジャンプ力アップ処理
	--------------------------------
	*/
	void JumpUp(IItem* item);

	/*
	--------------------------------
	  無敵化処理
	--------------------------------
	*/
	void Invincible(IItem* item);

	/*
	--------------------------------
	  スイッチ（ギミック）判定
	--------------------------------
	*/
	void CheckHitSwitch(ISwitch* sw);

	/*
	--------------------------------
	  落下床などのステージ処理
	--------------------------------
	*/
	void FallStage(IStage* stage);

private:
	/*
	--------------------------------
	  コンストラクタ
	  外部生成禁止（シングルトン）
	--------------------------------
	*/
	CCharacterManager(void) = default;

	// コピー禁止
	CCharacterManager(const CCharacterManager& rhs) = delete;

	// デストラクタ
	~CCharacterManager(void) = default;

	// 代入禁止
	CCharacterManager operator=(const CCharacterManager& rhs) = delete;

	/*
	--------------------------------
	  キャラクターリスト型
	--------------------------------
	*/
	using CHARACTER_LIST = std::list<std::unique_ptr<ICharacter>>;

	CHARACTER_LIST m_CharacterList;		// 管理しているキャラクター一覧
};
