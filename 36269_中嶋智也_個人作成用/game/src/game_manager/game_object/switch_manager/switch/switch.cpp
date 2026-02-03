#include "switch.h"
#include "../../stage_manager/stage_manager.h"

//============================================================
// スイッチ共通のスクロール速度
//（ステージスクロールに追従するため）
//============================================================
const float ISwitch::m_scroll_speed = 60.0f;

//============================================================
// スイッチ移動時の減衰率（慣性を抑える）
//============================================================
const float ISwitch::m_friction = 0.9f;

//============================================================
// コンストラクタ
// width, height : 当たり判定サイズ
// id            : スイッチの種類ID
//============================================================
ISwitch::ISwitch(int width, int height, SWITCH_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_SwitchID(id)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
{
}

//============================================================
// 初期化処理
// スイッチの配置位置と速度を初期化
//============================================================
void ISwitch::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

//============================================================
// 更新処理
// ステージスクロールに合わせてスイッチを移動
//============================================================
void ISwitch::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// ステージスクロール入力
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	// スクロール方向に応じて速度を加算
	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	// 位置更新（ΔTime対応）
	m_Position += m_Velocity * vivid::GetDeltaTime();

	// 摩擦による減衰
	m_Velocity.x *= m_friction;
}

//============================================================
// 描画処理
// 派生クラスで実装するため空実装
//============================================================
void ISwitch::Draw(void)
{
}

//============================================================
// 解放処理
// 派生クラスで必要に応じてオーバーライド
//============================================================
void ISwitch::Finalize(void)
{
}

//============================================================
// スイッチが押されたときの処理
// ・全スイッチのON/OFF切り替え
// ・床などの挙動変更を通知
//============================================================
void ISwitch::OnPress(void)
{
	CStageManager::GetInstance().ToggleAllSwitch();
	CStageManager::GetInstance().MoveChange(this);
}

//============================================================
// スイッチの幅取得
//============================================================
int ISwitch::GetWidth(void)
{
	return m_Width;
}

//============================================================
// スイッチの高さ取得
//============================================================
int ISwitch::GetHeight(void)
{
	return m_Height;
}

//============================================================
// スイッチの現在位置取得
//============================================================
vivid::Vector2 ISwitch::GetPosition(void)
{
	return m_Position;
}

//============================================================
// スイッチID取得
//============================================================
SWITCH_ID ISwitch::GetSwitchID(void)
{
	return m_SwitchID;
}

//============================================================
// スイッチがON状態かどうか取得
// StageManagerが状態を一括管理
//============================================================
bool ISwitch::GetOnFlag(void)
{
	return CStageManager::GetInstance().IsAllSwitchOn();
}
