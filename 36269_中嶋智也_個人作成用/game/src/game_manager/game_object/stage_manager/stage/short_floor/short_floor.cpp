#include "short_floor.h"

// 短い床の横幅（当たり判定・描画サイズの基準）
const int CShortFloor::m_width = 300;

// 短い床の高さ
const int CShortFloor::m_height = 64;

const std::string CShortFloor::m_floor_texture_path = "data\\short_floor.png";

CShortFloor::CShortFloor(void)
// IStage にサイズとステージIDを渡して初期化
	: IStage(m_width, m_height, STAGE_ID::SHORT_FLOOR)
{
}

CShortFloor::~CShortFloor(void)
{
	// 特別な解放処理は不要
}

void CShortFloor::Initialize(const vivid::Vector2& position)
{
	// 基底クラスで共通初期化（位置・当たり判定など）
	IStage::Initialize(position);

	// 初期配置位置を設定
	// ※ IStage 側で設定されていても、明示的に代入しておくことで
	//    クラス単体での初期化意図を明確にする
	m_Position = position;
}

void CShortFloor::Draw(void)
{
	// 短い床の描画
	// 第3引数はカラー指定（半透明・デバッグ用途など）
	vivid::DrawTexture(m_floor_texture_path, m_Position, 0xff000066);
}
