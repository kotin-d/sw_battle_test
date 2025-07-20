#pragma once

#include "AttackAction.h"


namespace sw::logic
{
	class AttackClose final : public AttackAction
	{
	public:
		explicit AttackClose(Unit& unit, uint32_t strength);
		~AttackClose() override = default;
	};
}