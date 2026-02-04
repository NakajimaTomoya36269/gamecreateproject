#include "fall_floor.h"

//====================================================
// 定数定義
//====================================================

// 床の当たり判定サイズ
const int	CFallFloor::m_width = 400;
const int	CFallFloor::m_height = 64;

// 落下速度（Y方向）
const float CFallFloor::m_fall_speed = 60.0f;

// 落下後、元の位置に戻るまでの待機時間（フレーム想定）
const float CFallFloor::m_return_time = 300.0f;

// 床の絵のファイルパス
const std::string CFallFloor::m_floor_texture_path = "data\\fall_floor.png";

//====================================================
// コンストラクタ
//====================================================
CFallFloor::CFallFloor(void)
// IStage にサイズとステージIDを委譲
	: IStage(m_width, m_height, STAGE_ID::FALL_FLOOR)

	// 落下用速度ベクトル
	, m_FallVelocity(vivid::Vector2(0.0f, 0.0f))

	// 復帰用タイマー
	, m_ReturnTimer(0.0f)

	// 描画色（デバッグ・拡張用）
	, m_Color(0xffffffff)
{
}

//====================================================
// 初期化
//====================================================
void CFallFloor::Initialize(const vivid::Vector2& position)
{
	// 基底クラス側で位置・当たり判定などを初期化
	IStage::Initialize(position);

	// 落下速度リセット
	m_FallVelocity = vivid::Vector2(0.0f, 0.0f);

	// 復帰タイマー初期化
	m_ReturnTimer = 0.0f;

	// 色初期化
	m_Color = 0xffffffff;
}

//====================================================
// 更新
//====================================================
void CFallFloor::Update(void)
{
	// 基底ステージ更新（共通処理）
	IStage::Update();

	//================================================
	// 落下状態制御
	//================================================
	// ※ 現在は常に true のため「常時落下床」
	//    将来的に「プレイヤーが乗ったら true」などに拡張可能
	m_IsFalled = true;

	if (m_IsFalled)
	{
		// 落下中：Y方向に一定速度を与える
		m_FallVelocity.y = m_fall_speed;
	}
	else
	{
		// 落下していない場合は停止
		m_FallVelocity.y = 0.0f;
	}

	//================================================
	// 画面外到達チェック
	//================================================
	if (m_Position.y > (float)vivid::WINDOW_HEIGHT)
	{
		// 落下完了扱い
		m_IsFalled = false;

		// 復帰タイマー加算
		if (++m_ReturnTimer > m_return_time)
		{
			// 一定時間後、初期位置へ復帰
			m_Position.y = m_StartPosition.y;

			// タイマーリセット（剰余的に管理）
			m_ReturnTimer -= m_return_time;
		}
	}

	//================================================
	// 位置更新（デルタタイム対応）
	//================================================
	m_Position += m_FallVelocity * vivid::GetDeltaTime();
}

//====================================================
// 描画
//====================================================
void CFallFloor::Draw(void)
{
	// 画面内に存在する場合のみ描画
	if (m_Position.y < (float)vivid::WINDOW_HEIGHT && m_Position.y > 0.0f)
	{
		vivid::DrawTexture(m_floor_texture_path, m_Position);
	}
}

//====================================================
// 解放
//====================================================
void CFallFloor::Finalize(void)
{
	// 基底クラスの後始末
	IStage::Finalize();
}
