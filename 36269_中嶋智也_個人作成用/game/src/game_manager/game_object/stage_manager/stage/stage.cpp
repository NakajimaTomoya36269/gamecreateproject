#include "stage.h"
#include "../../character_manager/character_manager.h"
#include "../../box_collider/box_collider.h"

// ステージ全体の横スクロール速度（プレイヤー移動に追従）
const float IStage::m_scroll_speed = 60.0f;

// 慣性減衰用の摩擦係数（値が小さいほど止まりやすい）
const float IStage::m_friction = 0.9f;

// コンストラクタ
// 各ステージ床のサイズとステージIDを受け取り、共通情報を初期化する
IStage::IStage(int width, int height, STAGE_ID id)
	: m_Width(width)								// 当たり判定の幅
	, m_Height(height)								// 当たり判定の高さ
	, m_StageID(id)								// ステージID
	, m_Position(vivid::Vector2(0.0f, 0.0f))		// 現在位置
	, m_StartPosition(vivid::Vector2(0.0f, 0.0f))	// 初期位置
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))		// 移動速度
	, m_IsFalled(false)							// 落下状態フラグ
{
}

// 初期化
// ステージ生成時に一度だけ呼ばれ、位置と状態をリセットする
void IStage::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_StartPosition = m_Position;

	m_Velocity = vivid::Vector2(0.0f, 0.0f);

	m_IsFalled = false;
}

// 更新
// 横スクロール処理のみを共通処理として実装
// 各派生クラスでは追加挙動を override で実装する
void IStage::Update(void)
{
	namespace keyboard = vivid::keyboard;

	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	// プレイヤー操作に合わせて床を逆方向へ移動させる
	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	// 速度を位置に反映
	m_Position += m_Velocity * vivid::GetDeltaTime();

	// 摩擦による減速
	m_Velocity.x *= m_friction;
}

// 描画
// 基底クラスでは何もしない
// 派生クラスで必ず override する前提
void IStage::Draw(void)
{
}

// 解放
// 共通で解放するリソースは存在しないため空実装
void IStage::Finalize(void)
{
}

// スイッチによる状態変更（デフォルトは何もしない）
// 動く床などが override して使用する
void IStage::MoveChange(ISwitch* sw)
{
	if (!sw) return;
}

// 幅の取得（当たり判定用）
int IStage::GetWidth(void)
{
	return m_Width;
}

// 高さの取得（当たり判定用）
int IStage::GetHeight(void)
{
	return m_Height;
}

// 現在位置の取得
vivid::Vector2 IStage::GetPosition(void)
{
	return m_Position;
}

// ステージIDの取得
STAGE_ID IStage::GetStageID(void)
{
	return m_StageID;
}

// 落下状態の取得
bool IStage::GetIsFalled(void)
{
	return m_IsFalled;
}

// 落下状態の設定
void IStage::SetIsFalled(bool fall_flag)
{
	m_IsFalled = fall_flag;
}

// 落下状態にする
void IStage::Falled(void)
{
	m_IsFalled = true;
}

// キャラクターとの左右衝突判定
// 衝突時はキャラクターのX座標を補正し、床の貫通を防ぐ
bool IStage::CheckHitCharacter(ICharacter* character, float& position_x)
{
	if (!character) return false;

	// 矩形同士の当たり判定
	if (CBoxCollider::GetInstance().CheckBoxCollision(
		m_Position, m_Width, m_Height,
		character->GetPosition(), character->GetWidth(), character->GetHeight()))
	{
		// 右方向に動いている床に衝突
		if (m_Velocity.x > 0.0f && position_x + (float)character->GetWidth() < m_Position.x)
		{
			position_x = m_Position.x - (float)character->GetWidth();
			m_Velocity.x = 0.0f;
			return true;
		}

		// 左方向に動いている床に衝突
		if (m_Velocity.x < 0.0f && position_x > m_Position.x + (float)m_Width)
		{
			position_x = m_Position.x + (float)m_Width;
			m_Velocity.x = 0.0f;
			return true;
		}
	}

	return false;
}
