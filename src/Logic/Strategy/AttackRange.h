#pragma once

#include "AttackAction.h"


namespace sw::logic
{
	class AttackRange final : public AttackAction
	{
	public:
		explicit AttackRange(Unit& unit, uint32_t range, uint32_t agility);
		~AttackRange() override = default;
	};
}