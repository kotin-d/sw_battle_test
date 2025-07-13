#pragma once

#include <cstdint>


struct Position
{
	Position() : x(0), y(0) {}
	Position(const uint32_t x, const uint32_t y) : x(x), y(y) {}

	bool operator==(const Position& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	uint32_t x;
	uint32_t y;
};
