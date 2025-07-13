#pragma once

#include "IO/System/EventLog.hpp"
#include "Logic/Delegate/LogUnitDelegate.h"
#include "Logic/Delegate/LogMapDelegate.h"
#include "Logic/Map.h"
#include "Logic/Unit.h"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <list>


namespace sw::logic
{
	class Game
	{
	private:
		Game();

	public:
		static Game& instance();

		void clear();

		void createMap(uint32_t width, uint32_t height);
		void spawn(const Unit::Ptr& unit, const Position& position);
		void killUnit(Unit* unit);

		[[nodiscard]] bool isGameOver() const;
		void makeTurn();

		[[nodiscard]] bool exist(Unit* unit) const;
		Unit* findUnit(uint32_t index) const;

	private:
		uint64_t _turn = 1;
		EventLog _eventLog;
		LogMapDelegate _logMapDelegate;
		LogUnitDelegate _logUnitDelegate;

		std::list<uint32_t> _orders;
		std::unordered_map<uint32_t, Unit::Ptr> _units;

		Map _map;
	};
}
