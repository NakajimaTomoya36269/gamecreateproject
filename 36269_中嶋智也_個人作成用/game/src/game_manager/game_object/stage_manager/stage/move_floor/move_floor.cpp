#include "move_floor.h"
#include "../../../switch_manager/switch/switch.h"

//====================================================
// クラス共通定数
//====================================================
// ・可動床のサイズは通常床より短めに設定
// ・移動速度はキャラクターの歩行速度と
//   体感的にズレない値を採用
const int   CMoveFloor::m_width = 300;
const int   CMoveFloor::m_height = 64;
const float CMoveFloor::m_move_speed = 60.0f;

//====================================================
// コンストラクタ
//====================================================
// ・IStage に床サイズと STAGE_ID を委譲
// ・開始位置・移動速度・状態フラグは初期値で初期化
// ・スイッチが ON になるまで床は静止状態
CMoveFloor::CMoveFloor(void)
	: IStage(m_width, m_height, STAGE_ID::MOVE_FLOOR)
	, m_StartPosition(vivid::Vector2(0.0f, 0.0f))
	, m_MoveVelocity(vivid::Vector2(0.0f, 0.0f))
	, m_ChangeMove(false)
	, m_ActiveFlag(false)
{
}

//====================================================
// 初期化
//====================================================
// @param position : 初期配置位置
//
// ・基底クラスで位置・当たり判定を初期化
// ・開始位置を保存し、移動範囲の基準点とする
// ・スイッチ未接続状態を想定し、非アクティブで開始
void CMoveFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);

	m_StartPosition = m_Position;              // 移動開始基準位置
	m_MoveVelocity = vivid::Vector2(0.0f, 0.0f);
	m_ChangeMove = false;
	m_ActiveFlag = false;
}

//====================================================
// 更新
//====================================================
// ・ステージスクロールの影響を受ける（m_Velocity）
// ・スイッチ ON 時のみ床自体が左右に移動
// ・移動範囲は「開始位置 ～ 開始位置 + 幅」
// ・端に到達すると移動方向を反転
void CMoveFloor::Update(void)
{
	namespace keyboard = vivid::keyboard;

	//------------------------------
	// スクロール処理（カメラ連動）
	//------------------------------
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	//------------------------------
	// 可動床本体の移動制御
	//------------------------------
	if (m_ActiveFlag)
	{
		// 移動範囲の端に到達したか判定
		if (m_Position.x > m_StartPosition.x + (float)m_Width)
		{
			m_ChangeMove = true;   // 左方向へ
		}
		if (m_Position.x < m_StartPosition.x)
		{
			m_ChangeMove = false;  // 右方向へ
		}

		// 移動方向に応じて速度を設定
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
		// 非アクティブ時は床は停止
		m_MoveVelocity.x = 0.0f;
	}

	//------------------------------
	// 座標更新
	//------------------------------
	// スクロールによる位置補正
	m_Position += m_Velocity * vivid::GetDeltaTime();
	m_StartPosition += m_Velocity * vivid::GetDeltaTime();

	// 慣性減衰
	m_Velocity.x *= m_friction;

	// 床固有の移動
	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();
	m_MoveVelocity.x *= m_friction;
}

//====================================================
// 描画
//====================================================
// ・可動床専用テクスチャを現在位置に描画
void CMoveFloor::Draw(void)
{
	vivid::DrawTexture("data\\move_floor.png", m_Position);
}

//====================================================
// 解放
//====================================================
void CMoveFloor::Finalize(void)
{
	IStage::Finalize();
}

//====================================================
// スイッチ連動処理
//====================================================
// @param sw : 接続されているスイッチ
//
// ・スイッチの ON/OFF に応じて
//   可動床の稼働状態を切り替える
// ・移動方向や位置リセットは行わず、
//   現在の状態を維持したまま停止/再開
void CMoveFloor::MoveChange(ISwitch* sw)
{
	if (!sw) return;

	m_ActiveFlag = sw->GetOnFlag();
}
