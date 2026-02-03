#include "../character_manager/character_manager.h"
#include "../stage_manager/stage_manager.h"
#include "switch_manager.h"
#include "switch/floor_switch/floor_switch.h"
#include "../../../utility/csv_loader/csv_loader.h"

//============================================================
// シングルトン取得
//============================================================
CSwitchManager& CSwitchManager::GetInstance(void)
{
	static CSwitchManager instance;
	return instance;
}

//============================================================
// 初期化処理
// スイッチリスト、生成テーブルのクリアとCSV読み込み
//============================================================
void CSwitchManager::Initialize(void)
{
	m_SwitchList.clear();
	m_SwitchTable.clear();

	DeploySwitch();
}

//============================================================
// 更新処理
// スイッチ生成テーブル更新 → スイッチ更新
//============================================================
void CSwitchManager::Update(void)
{
	UpdateSwitchTable();
	UpdateSwitch();
}

//============================================================
// 描画処理
// 登録されている全スイッチを描画
//============================================================
void CSwitchManager::Draw(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		(*it)->Draw();
		it++;
	}
}

//============================================================
// 終了処理
// スイッチのFinalize呼び出しとメモリ解放
//============================================================
void CSwitchManager::Finalize(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		(*it)->Finalize();
		delete (*it);
		it++;
	}
	m_SwitchList.clear();
}

//============================================================
// スイッチ生成
// 指定IDに応じて派生クラスを生成
//============================================================
void CSwitchManager::Create(SWITCH_ID id, const vivid::Vector2& position)
{
	ISwitch* sw = nullptr;

	switch (id)
	{
	case SWITCH_ID::FLOOR_SWITCH: sw = new CFloorSwitch(); break;
	}

	if (!sw) return;

	sw->Initialize(position);
	m_SwitchList.push_back(sw);
}

//============================================================
// コンストラクタ
//============================================================
CSwitchManager::CSwitchManager(void)
{
}

//============================================================
// CSVからスイッチ配置データを読み込み
//============================================================
void CSwitchManager::DeploySwitch(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\switch_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		SWITCH_TABLE_DATA t;
		t.id = (SWITCH_ID)csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)SWITCH_TABLE_DATA_PARAM::Y);

		m_SwitchTable.push_back(t);
	}

	csv_loader.Unload();
}

//============================================================
// スイッチ生成テーブル更新
// 1フレームにつき1つずつスイッチを生成
//============================================================
void CSwitchManager::UpdateSwitchTable(void)
{
	if (m_SwitchTable.empty()) return;

	SWITCH_TABLE_LIST::iterator it = m_SwitchTable.begin();
	SWITCH_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);

	m_SwitchTable.erase(it);
}

//============================================================
// スイッチ更新処理
// ・スイッチのUpdate呼び出し
// ・キャラクターとの当たり判定呼び出し
//============================================================
void CSwitchManager::UpdateSwitch(void)
{
	SWITCH_LIST::iterator it = m_SwitchList.begin();
	SWITCH_LIST::iterator end = m_SwitchList.end();

	while (it != end)
	{
		ISwitch* sw = (ISwitch*)(*it);

		sw->Update();
		CCharacterManager::GetInstance().CheckHitSwitch(sw);

		it++;
	}
}
