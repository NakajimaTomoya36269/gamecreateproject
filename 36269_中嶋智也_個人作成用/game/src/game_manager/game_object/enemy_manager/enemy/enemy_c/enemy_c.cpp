#include "enemy_c.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../character_manager/character/character.h"

// EnemyC の定数定義
const int   CEnemyC::m_width = 40;              // 敵の横幅
const int   CEnemyC::m_height = 40;             // 敵の高さ
const float CEnemyC::m_radius = 20.0f;          // 当たり判定用の半径
const int   CEnemyC::m_max_life = 1;            // 最大ライフ
const float CEnemyC::m_attack_time = 180.0f;    // 攻撃クールタイム（フレーム）
// 敵の絵のファイルパス
const std::string CEnemyC::m_enemy_texture_path = "data\\enemy_c.png";

/*
-----------------------------------------------------
 コンストラクタ
 ・EnemyC 固有のサイズ・半径・ライフを IEnemy に渡す
 ・攻撃関連の変数を初期化
-----------------------------------------------------
*/
CEnemyC::CEnemyC(void)
    : IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYC)
    , m_AttackTimer(0.0f)   // 攻撃タイマー初期化
    , m_Attacked(false)     // 攻撃フラグOFF
{
}

/*
------------------------------------
 初期化処理
 ・出現位置を設定（IEnemy 側）
 ・攻撃タイマーとフラグをリセット
------------------------------------
*/
void CEnemyC::Initialize(const vivid::Vector2& position)
{
    IEnemy::Initialize(position);

    // 攻撃可能になるまでの待ち時間をセット
    m_AttackTimer = m_attack_time;
    m_Attacked = false;
}

/*
------------------------------------
 更新処理
 ・Enemy 共通処理（重力、状態管理など）を実行
------------------------------------
*/
void CEnemyC::Update(void)
{
    IEnemy::Update();
}

/*
------------------------------------
 描画処理
 ・EnemyC のテクスチャを描画
------------------------------------
*/
void CEnemyC::Draw(void)
{
    vivid::DrawTexture(m_enemy_texture_path, m_Position);
}

/*
------------------------------------
 解放処理
 ・現状は特別な後処理なし
------------------------------------
*/
void CEnemyC::Finalize(void)
{
}

/*
------------------------------------
 床との当たり判定
 ・EnemyC は床判定を行わない設計
 ・将来拡張用に override だけしている
------------------------------------
*/
bool CEnemyC::OnGround(IStage* stage)
{
    if (!stage) return false;

    return false;
}

/*
------------------------------------
 攻撃処理
 ・一定時間ごとにプレイヤーへ弾を発射
 ・距離制限あり
------------------------------------
*/
void CEnemyC::Attack(ICharacter* character)
{
    if (!character) return;

    // 攻撃タイマーを進める
    // attack_time を超えたら攻撃可能状態にする
    if (++m_AttackTimer > m_attack_time)
    {
        m_Attacked = true;
    }

    // プレイヤーとの X 方向距離を計算
    float distance = fabs(character->GetPosition().x - m_Position.x);

    // 攻撃可能距離
    const float attack_range = 400.0f;

    // 攻撃可能かつ射程内なら攻撃
    if (m_Attacked && distance <= attack_range)
    {
        CBulletManager& bullet_manager = CBulletManager::GetInstance();

        // 敵からプレイヤーへのベクトルを計算
        vivid::Vector2 v = character->GetCenterPosition() - GetCenterPosition();

        // 発射角度を算出
        float dir = atan2(v.y, v.x);

        // 弾を生成
        bullet_manager.Create(
            BULLET_ID::NORMAL_BULLET,   // 弾の種類
            GetCenterPosition(),        // 発射位置
            dir,                        // 発射方向
            3.0f                        // 弾速
        );

        // 攻撃タイマーをリセット
        m_AttackTimer -= m_attack_time;

        // 攻撃フラグOFF（連射防止）
        m_Attacked = false;
    }
}
