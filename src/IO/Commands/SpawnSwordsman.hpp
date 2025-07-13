#pragma once

#include "Logic/Game.h"
#include "Logic/SwordsMan.h"

#include <cstdint>
#include <iosfwd>
#include <memory>

namespace sw::io
{
	struct SpawnSwordsman
	{
		constexpr static const char* Name = "SPAWN_SWORDSMAN";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t hp{};
		uint32_t strength{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}

		void execute() const
		{
			std::shared_ptr<sw::logic::Unit> unit = std::make_shared<sw::logic::SwordsMan>(unitId, hp, strength);
			sw::logic::Game::instance().spawn(unit, {x, y});
		}
	};
}
