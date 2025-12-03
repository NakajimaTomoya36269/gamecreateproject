#include "enemy.h"
#include "../../box_collider/box_collider.h"
#include "../../stage_manager/stage/stage.h"
#include "../../stage_manager/stage/long_floor/long_floor.h"

const float IEnemy::m_gravity_speed = 0.5f;
const float IEnemy::m_max_gravity = 30.0f;
const float IEnemy::m_scroll_speed = 60.0f;
const float IEnemy::m_move_speed = 3.0f;
const float IEnemy::m_max_speed = 100.0f;
const float IEnemy::m_friction = 0.9f;
const float IEnemy::m_jump_power = 30.0f;

IEnemy::IEnemy(int width, int height, float radius, int life, ENEMY_ID enemy_id)
	: m_Width(width)
	, m_Height(height)
	, m_Radius(radius)
	, m_Life(life)
	, m_MaxLife(life)
	, m_EnemyID(enemy_id)
	, m_State(ENEMY_STATE::ALIVE)
	, m_Active(true)
	, m_MoveChange(false)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_MoveVelocity(vivid::Vector2(0.0f, 0.0f))
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect{ 0, 0, m_Width, m_Height }
	, m_Jump(vivid::Vector2(0.0f, 0.0f))
{
}

void IEnemy::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_MoveVelocity = vivid::Vector2(0.0f, 0.0f);
	m_Jump = vivid::Vector2(0.0f, m_jump_power);
	m_Gravity = m_gravity_speed;
	m_Active = true;
	m_MoveChange = false;
	m_State = ENEMY_STATE::ALIVE;
}

void IEnemy::Update(void)
{
	switch (m_State)
	{
	case ENEMY_STATE::ALIVE: Alive(); break;
	case ENEMY_STATE::DEAD: Dead(); break;
	}
}

void IEnemy::Draw(void)
{
#ifdef _DEBUG
	vivid::DrawText(40, std::to_string(m_MoveVelocity.x), vivid::Vector2(0.0f, 80.0f));
#endif 

}

void IEnemy::Finalize(void)
{
}

bool IEnemy::OnGround(IStage* stage)
{
	if (m_Position.x + (float)m_Width > stage->GetPosition().x &&
		m_Position.x < stage->GetPosition().x + (float)stage->GetWidth() &&
		m_Position.y + (float)m_Height > stage->GetPosition().y &&
		m_Position.y < stage->GetPosition().y + stage->GetHeight())
	{
		if (m_Position.y + (float)m_Height > stage->GetPosition().y)
		{
			m_Position.y = stage->GetPosition().y - (float)m_Height;

			m_Velocity.y = 0.0f;

			if (stage->GetStageID() == STAGE_ID::REPULSION_FLOOR)
			{
				m_Velocity.y -= m_Jump.y;
			}

			return true;
		}
	}
	else
	{
		if (m_Velocity.y < m_max_gravity)
			m_Velocity.y += m_Gravity;
	}

	return false;
}

vivid::Vector2 IEnemy::GetPosition(void)
{
	return m_Position;
}

void IEnemy::SetPosition(const vivid::Vector2& position)
{
	m_Position = position;
}

int IEnemy::GetWidth(void)
{
	return m_Width;
}

int IEnemy::GetHeight(void)
{
	return m_Height;
}

bool IEnemy::GetActive(void)
{
	return m_Active;
}

void IEnemy::SetActive(bool active)
{
	m_Active = active;
}

void IEnemy::MoveArea(IStage* stage)
{
	const float move_area_margin = 200.0f;

	if (!stage) return;

	CLongFloor* long_floor = dynamic_cast<CLongFloor*>(stage);

	if (!long_floor) return;

	if (m_Position.x > long_floor->GetPosition().x + (float)long_floor->GetWidth() - move_area_margin)
	{
		m_MoveChange = true;
	}
	else if (m_Position.x < long_floor->GetPosition().x)
	{
		m_MoveChange = false;
	}
	if (m_MoveVelocity.x < m_max_speed)
	{
		if (m_MoveChange)
		{
			m_MoveVelocity.x -= m_move_speed;
		}
		else
		{
			m_MoveVelocity.x += m_move_speed;
		}
	}

	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();

	m_MoveVelocity.x *= m_friction;
}

void IEnemy::Alive(void)
{
	namespace keyboard = vivid::keyboard;

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

	m_Position.x += m_Velocity.x * vivid::GetDeltaTime();
	m_Position.y += m_Velocity.y;
	m_Velocity.x *= m_friction;
}

void IEnemy::Dead(void)
{
}
