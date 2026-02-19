#pragma once

class IEnemy;

struct CheckHitEnemyEvent
{
	IEnemy* enemy;
};

struct EnemyAttackEvent
{
	IEnemy* enemy;
};