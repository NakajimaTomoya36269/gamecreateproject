#include "background.h"

//------------------------------------------------------------
// 定数定義
//------------------------------------------------------------
const int   CBackGround::m_max_background_count = 2;		// 背景の枚数
const int   CBackGround::m_width = 1920;					// 背景1枚の横幅
const int   CBackGround::m_height = 1080;					// 背景1枚の高さ
const float CBackGround::m_scroll_speed = 60.0f;			// スクロール速度
// 背景の絵のファイルパス
const std::string CBackGround::m_background_texture_path = "data\\background.png";

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
CBackGround::CBackGround(void)
	: m_Position(nullptr)   // 位置配列は未確保
	, m_Velocity(nullptr)   // 速度配列は未確保
{
}

//------------------------------------------------------------
// 初期化処理
//------------------------------------------------------------
void CBackGround::Initialize(void)
{
	// 背景位置配列の確保
	if (!m_Position)
		m_Position = new vivid::Vector2[m_max_background_count];

	// 背景速度配列の確保
	if (!m_Velocity)
		m_Velocity = new vivid::Vector2[m_max_background_count];

	// 各背景の初期設定
	for (int i = 0; i < m_max_background_count; i++)
	{
		// 背景を横に並べる（0枚目:0、1枚目:1920）
		m_Position[i] = vivid::Vector2(i * (float)m_width, 0.0f);

		// スクロール速度を設定（右方向）
		m_Velocity[i] = vivid::Vector2(m_scroll_speed, 0.0f);
	}
}

//------------------------------------------------------------
// 更新処理
//------------------------------------------------------------
void CBackGround::Update(void)
{
	namespace keyboard = vivid::keyboard;

	// キー入力取得
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	for (int i = 0; i < m_max_background_count; i++)
	{
		// 右移動（背景は左に動かす）
		if (right_move_key)
		{
			m_Position[i].x -= m_Velocity[i].x * vivid::GetDeltaTime();

			// 画面外に出たら右端へ回す（無限スクロール）
			if (m_Position[i].x <= -m_width)
			{
				m_Position[i].x += m_width * m_max_background_count;
			}
		}

		// 左移動（背景は右に動かす）
		if (left_move_key)
		{
			m_Position[i].x += m_Velocity[i].x * vivid::GetDeltaTime();

			// 画面外に出たら左端へ回す（無限スクロール）
			if (m_Position[i].x >= m_width)
			{
				m_Position[i].x -= m_width * m_max_background_count;
			}
		}
	}
}

//------------------------------------------------------------
// 描画処理
//------------------------------------------------------------
void CBackGround::Draw(void)
{
	for (int i = 0; i < m_max_background_count; i++)
	{
		// 背景画像を描画
		vivid::DrawTexture(m_background_texture_path, m_Position[i]);
	}
}

//------------------------------------------------------------
// 解放処理
//------------------------------------------------------------
void CBackGround::Finalize(void)
{
	// 位置配列の解放
	delete[] m_Position;
	m_Position = nullptr;

	// 速度配列の解放
	delete[] m_Velocity;
	m_Velocity = nullptr;
}
