#pragma once

#include "Strategy/Damager.h"
#include "Strategy/Finder.h"
#include "Unit.h"

#include <memory>

namespace sw::logic
{
	class SwordsMan final : public Unit
	{
	public:
		constexpr static const char* Name = "Swordsman";

		SwordsMan(uint32_t id, uint32_t hp, uint32_t strength);
		~SwordsMan() override = default;

		[[nodiscard]] const char* name() const override { return Name; }

		[[nodiscard]] bool attack(Map& map) override;

	private:
		std::unique_ptr<FinderClose> _finder = nullptr;
		std::unique_ptr<IDamager> _damager = nullptr;
	};
}
