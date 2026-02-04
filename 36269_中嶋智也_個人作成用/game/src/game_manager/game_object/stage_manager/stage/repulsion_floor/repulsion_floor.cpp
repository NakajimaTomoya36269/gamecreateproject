#include "repulsion_floor.h"

// 反発床の当たり判定サイズ（論理サイズ）
const int CRepulsionFloor::m_width = 100;
const int CRepulsionFloor::m_height = 100;
// 床の絵のファイルパス
const std::string CRepulsionFloor::m_floor_texture_path = "data\\repulsion_floor.png";

CRepulsionFloor::CRepulsionFloor(void)
// IStage にサイズとステージ種別を委譲
// STAGE_ID::REPULSION_FLOOR により、外部システム（衝突判定・ギミック処理等）で
// 本クラス固有の挙動を識別可能にする
	: IStage(m_width, m_height, STAGE_ID::REPULSION_FLOOR)
{
}

void CRepulsionFloor::Initialize(const vivid::Vector2& position)
{
	// 基底クラスで共通初期化（当たり判定、内部状態リセット等）
	IStage::Initialize(position);

	// 明示的に位置を再代入
	// ※ 将来的に IStage::Initialize の実装が変更されても
	//    本クラスの初期位置保証を明確にするため
	m_Position = position;
}

void CRepulsionFloor::Draw(void)
{
	// 反発床の描画
	// ロジック（反発処理）と描画処理を分離し、
	// Update に依存しない純粋なレンダリング責務に限定
	vivid::DrawTexture(m_floor_texture_path, m_Position);
}
