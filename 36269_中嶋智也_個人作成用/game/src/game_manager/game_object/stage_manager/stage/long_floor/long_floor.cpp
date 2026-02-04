#include "long_floor.h"

//====================================================
// クラス共通定数定義
//====================================================
const int CLongFloor::m_width = 1500;
const int CLongFloor::m_height = 64;

const std::string CLongFloor::m_floor_texture_path = "data\\long_floor.png";

//====================================================
// コンストラクタ
//====================================================
// ・IStage にサイズと STAGE_ID を渡して初期化
// ・ロング床は特別な挙動を持たないため、ここでは
//   追加のメンバ初期化は行わない
CLongFloor::CLongFloor(void)
	: IStage(m_width, m_height, STAGE_ID::LONG_FLOOR)
{
}

//====================================================
// 初期化
//====================================================
// @param position : ステージ上での配置位置
//
// ・基底クラス IStage::Initialize を呼び、
//   開始位置・現在位置・当たり判定を初期化
// ・ロング床は静的オブジェクトのため、
//   追加の状態初期化は行わない
void CLongFloor::Initialize(const vivid::Vector2& position)
{
	IStage::Initialize(position);

	// 明示的に代入しているが、
	// IStage 側で既に設定されている場合は
	// 将来的に削除・統合してもよい
	m_Position = position;
}

//====================================================
// 描画
//====================================================
// ・ロング床専用テクスチャを現在位置に描画
void CLongFloor::Draw(void)
{
	vivid::DrawTexture(m_floor_texture_path, m_Position, 0xff000066);
}
