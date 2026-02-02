#include "enemy_manager.h"
#include "enemy/enemy_a/enemy_a.h"
#include "enemy/enemy_b/enemy_b.h"
#include "enemy/enemy_c/enemy_c.h"
#include "enemy/enemy_d/enemy_d.h"
#include "../character_manager/character_manager.h"
#include "../../../utility/csv_loader/csv_loader.h"

/*
==================================================
 敵マネージャ（シングルトン）
 ・敵の生成 / 更新 / 描画 / 解放を一括管理
 ・CSVから敵出現テーブルを読み込み、順次生成
==================================================
*/
CEnemyManager& CEnemyManager::GetInstance(void)
{
	static CEnemyManager instance;
	return instance;
}

/*
--------------------------------------------------
 初期化
 ・敵リスト、敵テーブルをクリア
 ・CSVから敵配置データを読み込む
--------------------------------------------------
*/
void CEnemyManager::Initialize(void)
{
	m_EnemyList.clear();		// 現在存在する敵を全削除
	m_EnemyTable.clear();	// 出現待ちテーブルを初期化

	DeployEnemy();			// CSVから敵出現データを読み込む
}

/*
--------------------------------------------------
 更新処理
 ・敵出現テーブルの更新（敵を生成）
 ・既存敵の更新
--------------------------------------------------
*/
void CEnemyManager::Update(void)
{
	UpdateEnemyTable();	// 敵の出現管理
	UpdateEnemy();		// 敵の挙動更新
}

/*
--------------------------------------------------
 描画処理
--------------------------------------------------
*/
void CEnemyManager::Draw(void)
{
	if (m_EnemyList.empty()) return;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		(*it)->Draw();	// 各敵の描画
		++it;
	}
}

/*
--------------------------------------------------
 解放処理
 ・敵をすべて削除
--------------------------------------------------
*/
void CEnemyManager::Finalize(void)
{
	if (m_EnemyList.empty()) return;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		(*it)->Finalize();	// 敵個別の後始末
		delete (*it);		// メモリ解放
		++it;
	}
	m_EnemyList.clear();
}

/*
--------------------------------------------------
 敵の生成
 ・ENEMY_ID に応じた敵クラスを生成
--------------------------------------------------
*/
void CEnemyManager::Create(ENEMY_ID id, const vivid::Vector2& position)
{
	IEnemy* enemy = nullptr;

	switch (id)
	{
	case ENEMY_ID::ENEMYA: enemy = new CEnemyA(); break;
	case ENEMY_ID::ENEMYB: enemy = new CEnemyB(); break;
	case ENEMY_ID::ENEMYC: enemy = new CEnemyC(); break;
	case ENEMY_ID::ENEMYD: enemy = new CEnemyD(); break;
	}

	if (!enemy) return;

	enemy->Initialize(position);	// 初期化
	m_EnemyList.push_back(enemy);	// 管理リストに追加
}

/*
--------------------------------------------------
 床判定（全敵）
 ・1体でも床に接地していれば true
--------------------------------------------------
*/
bool CEnemyManager::OnGround(IStage* stage)
{
	if (!stage) return false;
	if (m_EnemyList.empty()) return false;

	bool any_grounded = false;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		if ((*it)->OnGround(stage))
			any_grounded = true;
		++it;
	}
	return any_grounded;
}

/*
--------------------------------------------------
 攻撃処理
 ・全敵に対して攻撃判定を行う
--------------------------------------------------
*/
void CEnemyManager::Attack(ICharacter* character)
{
	if (!character) return;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		(*it)->Attack(character);	// 各敵固有の攻撃処理
		it++;
	}
}

/*
--------------------------------------------------
 コンストラクタ
--------------------------------------------------
*/
CEnemyManager::CEnemyManager(void)
{
}

/*
--------------------------------------------------
 敵配置データ読み込み
 ・CSVから敵IDと出現位置を取得
--------------------------------------------------
*/
void CEnemyManager::DeployEnemy(void)
{
	CCSVLoader csv_loader;
	csv_loader.Load("data\\enemy_table.csv");

	for (int i = 0; i < csv_loader.GetRows(); i++)
	{
		ENEMY_TABLE_DATA t;
		t.id = (ENEMY_ID)csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::ID);
		t.x = csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::X);
		t.y = csv_loader.GetInteger(i, (int)ENEMY_TABLE_DATA_PARAM::Y);

		m_EnemyTable.push_back(t);	// 出現待ちリストに追加
	}

	csv_loader.Unload();	// CSV解放
}

/*
--------------------------------------------------
 敵出現テーブル更新
 ・先頭のデータから1体ずつ敵を生成
--------------------------------------------------
*/
void CEnemyManager::UpdateEnemyTable(void)
{
	if (m_EnemyTable.empty()) return;

	ENEMY_TABLE_LIST::iterator it = m_EnemyTable.begin();
	ENEMY_TABLE_DATA t = *it;

	vivid::Vector2 position((float)t.x, (float)t.y);
	Create(t.id, position);		// 敵生成
	m_EnemyTable.erase(it);		// 生成済みデータを削除
}

/*
--------------------------------------------------
 敵更新処理
 ・キャラクターとの当たり判定
 ・敵の更新
 ・非アクティブ敵の削除
--------------------------------------------------
*/
void CEnemyManager::UpdateEnemy(void)
{
	if (m_EnemyList.empty()) return;

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	ENEMY_LIST::iterator end = m_EnemyList.end();

	while (it != end)
	{
		IEnemy* enemy = (IEnemy*)(*it);

		// プレイヤーとの当たり判定
		CCharacterManager::GetInstance().CheckHitEnemy(enemy);

		enemy->Update();	// 敵の更新

		// 非アクティブなら削除
		if (!enemy->GetActive())
		{
			enemy->Finalize();
			delete enemy;
			it = m_EnemyList.erase(it);
			continue;
		}
		++it;
	}
}
