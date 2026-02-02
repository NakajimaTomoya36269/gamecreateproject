#include "player.h"
#include "../../../scene_manager/scene_manager.h"

//------------------------------------------------------------
// 定数定義
//------------------------------------------------------------
const int   CPlayer::m_width = 100;     // プレイヤーの横幅
const int   CPlayer::m_height = 220;     // プレイヤーの高さ
const int   CPlayer::m_max_life = 1;     // 最大ライフ
const float CPlayer::m_radius = 64.0f;   // 円判定用半径

// プレイヤーの初期位置（画面中央・少し上）
const vivid::Vector2 CPlayer::m_start_position =
vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, 240.0f);

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
CPlayer::CPlayer(void)
	: ICharacter(
		m_width,
		m_height,
		m_radius,
		m_max_life,
		CHARACTER_CATEGORY::PLAYER,
		CHARACTER_ID::PLAYER)
	, m_Rotation(0.0f)
{
}

//------------------------------------------------------------
// デストラクタ
//------------------------------------------------------------
CPlayer::~CPlayer(void)
{
}

//------------------------------------------------------------
// 初期化処理
//------------------------------------------------------------
void CPlayer::Initialize(const vivid::Vector2& position)
{
	// 引数 position は使わず、固定の開始位置を使用
	(void)position;

	// 基底クラスの初期化
	ICharacter::Initialize(m_start_position);

	// ライフ初期化
	m_Life = m_MaxLife = m_max_life;

	// ジャンプ初速設定
	m_Jump = vivid::Vector2(0.0f, m_jump_power);
}

//------------------------------------------------------------
// 更新処理
//------------------------------------------------------------
void CPlayer::Update(void)
{
	// 基本的な移動・入力処理は基底クラスに任せる
	ICharacter::Update();
}

//------------------------------------------------------------
// 描画処理
//------------------------------------------------------------
void CPlayer::Draw(void)
{
	// プレイヤー描画
	vivid::DrawTexture("data\\player.png", m_Position, 0xffffffff);

#ifdef _DEBUG
	// デバッグ用：Y座標表示
	vivid::DrawText(
		40,
		std::to_string(m_Position.y),
		vivid::Vector2(0.0f, 40.0f));
#endif
}

//------------------------------------------------------------
// 解放処理
//------------------------------------------------------------
void CPlayer::Finalize(void)
{
}

//------------------------------------------------------------
// 生存状態処理
//------------------------------------------------------------
void CPlayer::Alive(void)
{
	// 基底クラスの生存処理
	ICharacter::Alive();

	// 重力反転状態による移動方向切り替え
	if (m_GravityChange)
	{
		// 重力反転中（上方向）
		m_Position.y -= m_Velocity.y;
	}
	else
	{
		// 通常重力（下方向）
		m_Position.y += m_Velocity.y;
	}

	// 画面外チェック（通常重力）
	if (!m_GravityChange && m_Position.y + m_Height > (float)vivid::WINDOW_HEIGHT)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
	// 画面外チェック（重力反転）
	else if (m_GravityChange && m_Position.y < 0.0f)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
	// ライフ切れ
	else if (m_Life <= 0)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
}

//------------------------------------------------------------
// 死亡状態処理
//------------------------------------------------------------
void CPlayer::Dead(void)
{
	// プレイヤーを無効化
	m_Active = false;

	// ゲームオーバーシーンへ遷移
	CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAMEOVER);
}
