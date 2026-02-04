#include "enemy_b.h"
#include "../../../stage_manager/stage_manager.h"

/*
====================================
  EnemyB 固有定数
====================================
*/
const int	CEnemyB::m_width = 40;		// 敵の横幅
const int	CEnemyB::m_height = 40;		// 敵の高さ
const float CEnemyB::m_radius = 20.0f;	// 当たり判定用半径
const int	CEnemyB::m_max_life = 1;	// 最大ライフ
// 敵の絵のファイルパス
const std::string CEnemyB::m_enemy_texture_path = "data\\enemy_b.png";

/*
====================================
  コンストラクタ
  ・IEnemy に EnemyB 固有のパラメータを渡す
====================================
*/
CEnemyB::CEnemyB(void)
	: IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYB)
{
}

/*
====================================
  デストラクタ
  ・特別な解放処理は無し
====================================
*/
CEnemyB::~CEnemyB(void)
{
}

/*
====================================
  初期化
  ・位置設定
  ・ライフの初期化
====================================
*/
void CEnemyB::Initialize(const vivid::Vector2& position)
{
	IEnemy::Initialize(position);

	// ライフを最大値にリセット
	m_Life = m_MaxLife = m_max_life;
}

/*
====================================
  更新処理
  ・基本処理は IEnemy に委譲
====================================
*/
void CEnemyB::Update(void)
{
	IEnemy::Update();
}

/*
====================================
  描画処理
  ・EnemyB 専用画像を描画
====================================
*/
void CEnemyB::Draw(void)
{
	vivid::DrawTexture(m_enemy_texture_path, m_Position);
}

/*
====================================
  解放処理
  ・現在は特に処理なし
====================================
*/
void CEnemyB::Finalize(void)
{
}

/*
====================================
  地面（足場）判定
  ・EnemyB は「天井側に張り付く」挙動
====================================
*/
bool CEnemyB::OnGround(IStage* stage)
{
	// AABB 判定（ステージと重なっているか）
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		// 下方向（天井側）に移動している場合
		if (m_Velocity.y > 0.0f &&
			m_Position.y < stage->GetPosition().y + (float)stage->GetHeight())
		{
			// 現在接触しているステージを保存
			m_CurrentStage = stage;

			// ステージの下側に位置を固定（天井張り付き）
			m_Position.y = stage->GetPosition().y + (float)stage->GetHeight();

			// 垂直速度をリセット
			m_Velocity.y = 0.0f;

			return true;
		}
	}
	else
	{
		// ステージから離れている場合は重力を加算
		if (m_Velocity.y < m_max_gravity)
			m_Velocity.y += m_Gravity;
	}

	return false;
}

/*
====================================
  生存中の処理
  ・上方向へ移動（逆重力的挙動）
  ・画面外に出たら死亡
====================================
*/
void CEnemyB::Alive(void)
{
	IEnemy::Alive();

	// 上方向へ移動
	m_Position.y -= m_Velocity.y;

	// 画面外判定
	if (m_Position.y < 0.0f ||
		m_Position.y + m_Height >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = ENEMY_STATE::DEAD;
	}
}

/*
====================================
  死亡処理
  ・非アクティブ化
====================================
*/
void CEnemyB::Dead(void)
{
	m_Active = false;
	IEnemy::Dead();
}
