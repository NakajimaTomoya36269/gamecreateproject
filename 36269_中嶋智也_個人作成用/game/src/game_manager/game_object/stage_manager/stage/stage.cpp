#include "stage.h"

const int CStage::m_width = 300;
const int CStage::m_height = 64;
const float CStage::m_scroll_speed = 1.0f;

CStage::CStage(void)
	: m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
{
}

void CStage::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

void CStage::Update(void)
{
}

void CStage::Draw(void)
{
	vivid::DrawTexture("data\\floor.png", m_Position);
}

void CStage::Finalize(void)
{
}

int CStage::GetWidth(void)
{
	return m_width;
}

int CStage::GetHeight(void)
{
	return m_height;
}

vivid::Vector2 CStage::GetPosition(void)
{
	return m_Position;
}
