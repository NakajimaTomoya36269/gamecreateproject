#include "floor_switch.h"

//============================================================
// フロアスイッチの当たり判定サイズ
//============================================================
const int	CFloorSwitch::m_width = 100;
const int	CFloorSwitch::m_height = 40;

const std::string CFloorSwitch::m_switch_texture_path = "data\\floor_switch.png";

//============================================================
// コンストラクタ
// ・スイッチのサイズとIDを基底クラスに渡す
//============================================================
CFloorSwitch::CFloorSwitch(void)
	: ISwitch(m_width, m_height, SWITCH_ID::FLOOR_SWITCH)
{
}

//============================================================
// 描画処理
// フロアスイッチのテクスチャを描画
//============================================================
void CFloorSwitch::Draw(void)
{
	vivid::DrawTexture(m_switch_texture_path, m_Position);
}
