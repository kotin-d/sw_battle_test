#pragma once

#include "Logic/Game.h"

#include <cstdint>
#include <iosfwd>
#include <iostream>

namespace sw::io
{
	struct CreateMap
	{
		constexpr static const char* Name = "CREATE_MAP";

		uint32_t width{};
		uint32_t height{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}

		void execute() const
		{
			sw::logic::Game::instance().createMap(width, height);
		}
	};
}
