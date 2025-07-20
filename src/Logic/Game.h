#pragma once

#include "IO/System/EventLog.hpp"
#include "Logic/Delegate/LogUnitDelegate.h"
#include "Logic/Delegate/LogMapDelegate.h"
#include "Logic/Map.h"
#include "Logic/Unit.h"
#include "Logic/Model.h"
#include <memory>


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
		void spawn(const std::shared_ptr<Unit>& unit, const Position& position);
		void march(uint32_t id, const Position& position);
		void killUnit(uint32_t id);

		[[nodiscard]] bool isGameOver() const;
		void makeTurn();

	private:
		uint64_t _turn = 1;
		EventLog _eventLog;
		LogMapDelegate _logMapDelegate;
		LogUnitDelegate _logUnitDelegate;

		Model _model;
		Map _map;
	};
}
