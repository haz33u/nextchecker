#include "TurretState.h"

void ATurretState::GetDamage(float Damage)
{
	// ¬ычитаем урон из значени€ здоровь€
	Health -= Damage;

	// ѕровер€ем, не опустилось ли значение здоровь€ ниже или равно нулю
	if (Health <= 0.0f)
	{
		Health = 0.0f;
		IsDead = true;
	}
}
