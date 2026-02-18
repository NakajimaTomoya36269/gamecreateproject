#include "bullet_manager.h"
#include "bullet/bullet.h"
#include "bullet/normal_bullet/normal_bullet.h"
#include "../stage_manager/stage_manager.h"
#include "../character_manager/character_manager.h"

//------------------------------------------------------------
// シングルトン取得
// ・static 変数は最初の呼び出し時に1回だけ生成される
// ・ゲーム全体で弾管理を1つにするための設計
//------------------------------------------------------------
CBulletManager& CBulletManager::GetInstance(void)
{
	static CBulletManager instance;
	return instance;
}

//------------------------------------------------------------
// 初期化
// ・弾リストを空にする
// ・ステージ開始時などに呼ばれる想定
//------------------------------------------------------------
void CBulletManager::Initialize(void)
{
	m_BulletList.clear();
}

//------------------------------------------------------------
// 更新処理
// ・全弾の Update 実行
// ・キャラとの当たり判定
// ・非アクティブ弾の削除
//------------------------------------------------------------
void CBulletManager::Update(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		// unique_ptr から生ポインタ取得
		IBullet* bullet = it->get();

		// 弾の更新処理
		bullet->Update();

		// キャラクターとの当たり判定
		CCharacterManager::GetInstance().CheckHitBullet(bullet);

		// 弾が非アクティブなら削除
		if (!bullet->GetActiveFlag())
		{
			// 終了処理
			bullet->Finalize();

			// erase は削除後の次のイテレータを返す
			it = m_BulletList.erase(it);
			continue;  // ++しない（既に次へ進んでいる）
		}

		it++;
	}
}

//------------------------------------------------------------
// 描画処理
// ・全弾の描画を行う
//------------------------------------------------------------
void CBulletManager::Draw(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		(*it)->Draw();
		it++;
	}
}

//------------------------------------------------------------
// 終了処理
// ・全弾の Finalize 実行
// ・リストを空にする
//------------------------------------------------------------
void CBulletManager::Finalize(void)
{
	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		(*it)->Finalize();
		it++;
	}

	// unique_ptr なので clear するだけで自動解放
	m_BulletList.clear();
}

//------------------------------------------------------------
// 弾生成
// id        : 弾の種類
// position  : 初期座標
// direction : 進行方向
// speed     : 速度
//------------------------------------------------------------
void CBulletManager::Create(BULLET_ID id, const vivid::Vector2& position, float direction, float speed)
{
	std::unordered_map<BULLET_ID, CreateFunc>::iterator it = m_CreateMap.find(id);
	if (it == m_CreateMap.end())
		return;

	std::unique_ptr<IBullet> bullet = it->second();  // 生成

	bullet->Initialize(position, direction, speed);

	m_BulletList.push_back(std::move(bullet));
}

//------------------------------------------------------------
// ステージとの当たり判定
// ・全弾に対してステージとの衝突をチェック
//------------------------------------------------------------
void CBulletManager::CheckHitStage(IStage* stage)
{
	if (!stage) return;

	BULLET_LIST::iterator it = m_BulletList.begin();
	BULLET_LIST::iterator end = m_BulletList.end();

	while (it != end)
	{
		if ((*it)->CheckHitStage(stage))
			return;

		it++;
	}
}

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
CBulletManager::CBulletManager(void)
{
	RegisterBullets();
}

// 弾登録
void CBulletManager::RegisterBullets(void)
{
	m_CreateMap[BULLET_ID::NORMAL_BULLET] = 
		[]() {return std::make_unique<CNormalBullet>(); };
}
