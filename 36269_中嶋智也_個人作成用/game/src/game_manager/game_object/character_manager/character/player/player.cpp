#include "player.h"
#include "../../../scene_manager/scene_manager.h"

//------------------------------------------------------------
// 定数定義
//------------------------------------------------------------
const int   CPlayer::m_width = 139;     // プレイヤーの横幅
const int   CPlayer::m_height = 90;     // プレイヤーの高さ
const int   CPlayer::m_max_life = 1;     // 最大ライフ
const float CPlayer::m_radius = 64.0f;   // 円判定用半径

// プレイヤーの初期位置（画面中央・少し上）
const vivid::Vector2 CPlayer::m_start_position =
vivid::Vector2((vivid::WINDOW_WIDTH - m_width) / 2.0f, 240.0f);

// プレイヤーの絵のファイルパス
const std::string CPlayer::m_player_texture_path = "data\\player_1.png";

// 無敵状態のプレイヤーの絵のファイルパス
const std::string CPlayer::m_invincible_player_texture_path = "data\\invincible_player_1.png";

// ジャンプ力上昇中の絵のファイルパス
const std::string CPlayer::m_jump_gauge_texture_path = "data\\jump_up_gauge.png";

// 重力が逆の状態の絵のファイルパス
const std::string CPlayer::m_revese_player_texture_path = "data\\player_2.png";

// 重力が逆の状態のジャンプ力上昇中の絵のファイルパス
const std::string CPlayer::m_revese_jump_gauge_texture_path = "data\\jump_up_gauge_2.png";

// 重力が逆の状態で無敵状態の絵のファイルパス
const std::string CPlayer::m_revese_invincible_player_texture_path = "data\\invincible_player_2.png";

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
CPlayer::CPlayer(void)
	: ICharacter(
		m_width,
		m_height,
		m_radius,
		m_max_life,
		CHARACTER_ID::PLAYER)
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
	// ジャンプゲージ描画用のオフセット値（プレイヤーの座標基準）
	const float jump_gauge_offset_x = 26.5f; // X方向のゲージ表示位置補正
	const float jump_gauge_offset_y = 80.0f; // Y方向のゲージ表示位置補正（上方向）

	if (!m_GravityChange)
	{
		// ジャンプ上昇中の場合、ジャンプゲージをプレイヤー上に表示
		if (m_JumpUp)
		{
			// プレイヤー位置からオフセットしてジャンプゲージを描画
			vivid::DrawTexture(
				m_jump_gauge_texture_path,
				vivid::Vector2(
					m_Position.x - jump_gauge_offset_x, // X座標調整
					m_Position.y - jump_gauge_offset_y  // Y座標調整
				)
			);
		}
		if (m_InvincibleFlag)
		{
			vivid::DrawTexture(m_invincible_player_texture_path, m_Position);
		}
		else
		{
			// プレイヤー本体の描画
			// m_Position: プレイヤーの座標
			vivid::DrawTexture(m_player_texture_path, m_Position);
		}
	}
	else
	{
		if (m_JumpUp)
		{
			vivid::DrawTexture(
				m_revese_jump_gauge_texture_path,
				vivid::Vector2(
					m_Position.x - jump_gauge_offset_x, // X座標調整
					m_Position.y + 50.0f  // Y座標調整
				)
			);
		}
		if (m_InvincibleFlag)
		{
			vivid::DrawTexture(m_revese_invincible_player_texture_path, m_Position);
		}
		else
		{
			vivid::DrawTexture(m_revese_player_texture_path, m_Position);
		}
	}

#ifdef _DEBUG
	// デバッグ用：プレイヤーのY座標を画面に表示
	// 画面左上（0,40）に表示
	vivid::DrawText(
		40, // フォントサイズ
		std::to_string(m_Position.y), // 表示文字列（Y座標）
		vivid::Vector2(0.0f, 40.0f) // 描画位置
	);
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
	if (!m_GravityChange && m_Position.y > (float)vivid::WINDOW_HEIGHT + m_Height)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
	// 画面外チェック（重力反転）
	else if (m_GravityChange && m_Position.y + m_Height < 0.0f)
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
