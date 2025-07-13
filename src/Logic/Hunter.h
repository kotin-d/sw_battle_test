#pragma once

#include "Strategy/Damager.h"
#include "Strategy/Finder.h"
#include "Unit.h"

namespace sw::logic
{
	class Hunter final : public Unit
	{
	public:
		constexpr static const char* Name = "Hunter";

		Hunter(uint32_t id, uint32_t hp, uint32_t strength, uint32_t agility, uint32_t range);
		~Hunter() override = default;

		[[nodiscard]] const char* name() const override { return Name; }

		bool attack(Map& map) override;

	protected:
		std::unique_ptr<FinderClose> _finderClose = nullptr;
		std::unique_ptr<IDamager> _damagerClose = nullptr;
		std::unique_ptr<FinderRange> _finderRange = nullptr;
		std::unique_ptr<IDamager> _damagerRange = nullptr;
	};
}
