#pragma once

#include "vivid.h"
#include <list>
#include "character/character.h"
#include "character/character_id.h"
#include "../stage_manager/stage_manager.h"

class CCharacterManager
{
public:
	// インスタンスの取得
	static CCharacterManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// キャラクター作成
	void Create(CHARACTER_ID id, const vivid::Vector2& position);

	// 地面の上にいるかの判定
	bool OnGround(CStage* stage);
	
	// ジャンプ
	void Jump(void);

	// 重力変更
	void ChangeGravity(void);

private:
	// コンストラクタ
	CCharacterManager(void) = default;

	// コピーコンストラクタ
	CCharacterManager(const CCharacterManager& rhs) = delete;

	// デストラクタ
	~CCharacterManager(void) = default;
	
	// 代入演算子
	CCharacterManager operator=(const CCharacterManager& rhs) = delete;

	// キャラクターリスト型
	using CHARACTER_LIST = std::list<ICharacter*>;

	CHARACTER_LIST m_CharacterList;		// キャラクターリスト
};