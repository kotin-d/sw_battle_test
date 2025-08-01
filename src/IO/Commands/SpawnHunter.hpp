#pragma once

#include "Logic/Game.h"
#include "Logic/Hunter.h"

#include <cstdint>
#include <iosfwd>
#include <memory>

namespace sw::io
{
	struct SpawnHunter
	{
		constexpr static const char* Name = "SPAWN_HUNTER";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t hp{};
		uint32_t agility{};
		uint32_t strength{};
		uint32_t range{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("agility", agility);
			visitor.visit("strength", strength);
			visitor.visit("range", range);
		}

		void execute() const
		{
			std::shared_ptr<sw::logic::Unit> unit = std::make_shared<sw::logic::Hunter>(unitId, hp, strength, agility, range);
			sw::logic::Game::instance().spawn(unit, {x, y});
		}
	};
}
