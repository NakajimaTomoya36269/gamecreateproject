#include "reverse_move_floor.h"
#include "../../../switch_manager/switch/switch.h"

// 床の当たり判定サイズ
const int   CReverseMoveFloor::m_width = 300;
const int   CReverseMoveFloor::m_height = 64;

// 床の自動移動速度
const float CReverseMoveFloor::m_move_speed = 60.0f;

const std::string CReverseMoveFloor::m_floor_texture_path = "data\\move_floor.png";

CReverseMoveFloor::CReverseMoveFloor(void)
	: IStage(m_width, m_height, STAGE_ID::REVERSE_MOVE_FLOOR)
	, m_StartPosition(vivid::Vector2(0.0f, 0.0f))	// 初期位置
	, m_MoveVelocity(vivid::Vector2(0.0f, 0.0f))	// 自動移動用速度
	, m_ChangeMove(false)							// 移動方向反転フラグ
	, m_ActiveFlag(false)							// スイッチ状態（true時は停止）
{
}

void CReverseMoveFloor::Initialize(const vivid::Vector2& position)
{
	// 親クラスの初期化（座標・判定サイズなど）
	IStage::Initialize(position);

	// 初期位置を保存（移動範囲の基準点）
	m_StartPosition = m_Position;

	// 移動速度リセット
	m_MoveVelocity = vivid::Vector2(0.0f, 0.0f);

	// 状態フラグ初期化
	m_ChangeMove = false;
	m_ActiveFlag = false;
}

void CReverseMoveFloor::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// カメラスクロール用の入力取得
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	// 画面スクロールによる床の追従移動
	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	// ▼ 逆制御の移動床ロジック ▼
	// スイッチが「OFF」のときだけ自動移動する
	if (!m_ActiveFlag)
	{
		// 移動範囲の端に到達したら移動方向を切り替える
		if (m_Position.x > m_StartPosition.x + (float)m_Width)
		{
			m_ChangeMove = true;
		}
		if (m_Position.x < m_StartPosition.x)
		{
			m_ChangeMove = false;
		}

		// フラグに応じて移動方向を決定
		if (m_ChangeMove)
		{
			m_MoveVelocity.x = -m_move_speed;
		}
		else
		{
			m_MoveVelocity.x = m_move_speed;
		}
	}
	else
	{
		// スイッチON中は床を完全停止
		m_MoveVelocity.x = 0.0f;
	}

	// スクロールによる位置補正
	m_Position += m_Velocity * vivid::GetDeltaTime();
	m_StartPosition += m_Velocity * vivid::GetDeltaTime();

	// 慣性減衰（スクロール速度）
	m_Velocity.x *= m_friction;

	// 自動移動の反映
	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();
	m_MoveVelocity.x *= m_friction;
}

void CReverseMoveFloor::Draw(void)
{
	// 移動床の描画
	vivid::DrawTexture(m_floor_texture_path, m_Position);
}

void CReverseMoveFloor::Finalize(void)
{
	// 親クラスの終了処理
	IStage::Finalize();
}

void CReverseMoveFloor::MoveChange(ISwitch* sw)
{
	// nullptr安全対策
	if (!sw) return;

	// スイッチ状態を取得
	// true  : 停止
	// false : 自動移動
	m_ActiveFlag = sw->GetOnFlag();
}
