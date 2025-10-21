#include "box_collider.h"

CBoxCollider& CBoxCollider::GetInstance(void)
{
	static CBoxCollider instance;

	return instance;
}

bool CBoxCollider::CheckBoxCollision(const vivid::Vector2& box_position1, const int box_width1,
										const int box_height1, 
										const vivid::Vector2& box_position2, const int box_width2, 
										const int box_height2)
{
	return ( box_position1.x + (float)box_width1 > box_position2.x &&
			 box_position1.x < box_position2.x + (float)box_width2 &&
			 box_position1.y + (float)box_height1 > box_position2.y &&
			 box_position1.y < box_position2.y + (float)box_height2 );
}
