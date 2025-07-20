#pragma once

#include "Unit.h"


namespace sw::logic
{
	class SwordsMan final : public Unit
	{
	public:
		constexpr static const char* Name = "Swordsman";

		SwordsMan(uint32_t id, uint32_t hp, uint32_t strength);
		~SwordsMan() override = default;

		[[nodiscard]] const char* name() const override { return Name; }
	};
}
