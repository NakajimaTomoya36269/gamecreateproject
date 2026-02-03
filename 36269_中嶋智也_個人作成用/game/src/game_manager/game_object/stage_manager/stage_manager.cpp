#include "stage_manager.h"
#include "../character_manager/character_manager.h"
#include "../enemy_manager/enemy_manager.h"
#include "../switch_manager/switch_manager.h"
#include "../bullet_manager/bullet_manager.h"
#include "stage/short_floor/short_floor.h"
#include "stage/long_floor/long_floor.h"
#include "stage/repulsion_floor/repulsion_floor.h"
#include "stage/move_floor/move_floor.h"
#include "stage/fall_floor/fall_floor.h"
#include "stage/reverse_move_floor/reverse_move_floor.h"
#include "../../../utility/csv_loader/csv_loader.h"

///------------------------------------------------------------
/// ステージマネージャのシングルトン取得
///------------------------------------------------------------
CStageManager& CStageManager::GetInstance(void)
{
	static CStageManager instance;
	return instance;
}

///------------------------------------------------------------
/// 初期化処理
/// ステージリストとステージ生成テーブルを初期化し、
/// CSVからステージ情報を読み込む
///------------------------------------------------------------
void CStageManager::Initialize(void)
{
	m_StageList.clear();
	m_StageTable.clear();

	DeployStage();
}

///------------------------------------------------------------
/// 更新処理
/// ステージ生成テーブルの更新 → ステージの更新
///------------------------------------------------------------
void CStageManager::Update(void)
{
	UpdateStageTable();
	UpdateStage();
}

///------------------------------------------------------------
/// 描画処理
/// 登録されている全ステージを描画
///------------------------------------------------------------
void CStageManager::Draw(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		(*it)->Draw();
		++it;
	}
}

///------------------------------------------------------------
/// 終了処理
/// ステージの終了処理とメモリ解放
///------------------------------------------------------------
void CStageManager::Finalize(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		(*it)->Finalize();
		delete (*it);
		++it;
	}
	m_StageList.clear();
}

///------------------------------------------------------------
/// ステージ生成
/// ステージIDに応じて対応する床オブジェクトを生成
///------------------------------------------------------------
void CStageManager::Create(STAGE_ID id, const vivid::Vector2& position)
{
	IStage* stage = nullptr;

	switch (id)
	{
	case STAGE_ID::SHORT_FLOOR: stage = new CShortFloor(); break;
	case STAGE_ID::LONG_FLOOR: stage = new CLongFloor(); break;
	case STAGE_ID::REPULSION_FLOOR:	stage = new CRepulsionFloor(); break;
	case STAGE_ID::MOVE_FLOOR: stage = new CMoveFloor(); break;
	case STAGE_ID::FALL_FLOOR: stage = new CFallFloor(); break;
	case STAGE_ID::REVERSE_MOVE_FLOOR: stage = new CReveseMoveFloor(); break;
	}

	// 無効なIDの場合は生成しない
	if (!stage)	return;

	stage->Initialize(position);
	m_StageList.push_back(stage);
}

///------------------------------------------------------------
/// 敵が地面に接地しているかの判定
///------------------------------------------------------------
void CStageManager::EnemyOnGround(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if (CEnemyManager::GetInstance().OnGround((*it)))
		{
			return;
		}
		++it;
	}
}

///------------------------------------------------------------
/// キャラクターとステージの当たり判定
///------------------------------------------------------------
bool CStageManager::CheckHitCharacter(ICharacter* character, float&& position_x)
{
	if (!character) return false;

	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		if ((*it)->CheckHitCharacter(character, position_x))
		{
			return true;
		}
		++it;
	}
	return false;
}

///------------------------------------------------------------
/// 全スイッチのON/OFF切り替え
///------------------------------------------------------------
void CStageManager::ToggleAllSwitch(void)
{
	m_AllSwitchOn = !m_AllSwitchOn;
}

///------------------------------------------------------------
/// 全スイッチがONかどうか取得
///------------------------------------------------------------
bool CStageManager::IsAllSwitchOn(void) const
{
	return m_AllSwitchOn;
}

///------------------------------------------------------------
/// スイッチに連動した床の移動方向変更
///------------------------------------------------------------
void CStageManager::MoveChange(ISwitch* sw)
{
	if (!sw) return;

	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		(*it)->MoveChange(sw);
		++it;
	}
}

///------------------------------------------------------------
/// コンストラクタ
///------------------------------------------------------------
CStageManager::CStageManager(void)
	: m_AllSwitchOn(false)
{
}

///------------------------------------------------------------
/// CSVからステージ配置データを読み込む
///------------------------------------------------------------
void CStageManager::DeployStage(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\stage_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		STAGE_TABLE_DATA t;
		t.id = (STAGE_ID)csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)STAGE_TABLE_DATA_PARAM::Y);
		m_StageTable.push_back(t);
	}

	csv_loader.Unload();
}

///------------------------------------------------------------
/// ステージ生成テーブル更新
/// 1フレームに1つずつステージを生成する
///------------------------------------------------------------
void CStageManager::UpdateStageTable(void)
{
	if (m_StageTable.empty()) return;

	STAGE_TABLE_LIST::iterator it = m_StageTable.begin();
	STAGE_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);

	m_StageTable.erase(it);
}

///------------------------------------------------------------
/// ステージ更新と各マネージャとの当たり判定処理
///------------------------------------------------------------
void CStageManager::UpdateStage(void)
{
	STAGE_LIST::iterator it = m_StageList.begin();
	STAGE_LIST::iterator end = m_StageList.end();

	while (it != end)
	{
		IStage* stage = (IStage*)(*it);
		stage->Update();

		CCharacterManager& character_manager = CCharacterManager::GetInstance();

		character_manager.CheckHitRightWall(stage);
		character_manager.CheckHitLeftWall(stage);
		character_manager.CheckHitCeiling(stage);
		character_manager.ChangeGravity(stage);
		character_manager.Jump(stage);
		character_manager.OnGround(stage);
		character_manager.FallStage(stage);

		CEnemyManager::GetInstance().OnGround(stage);
		CBulletManager::GetInstance().CheckHitStage(stage);

		++it;
	}
}
