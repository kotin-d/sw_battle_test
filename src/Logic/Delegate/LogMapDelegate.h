#pragma once

#include "IO/System/EventLog.hpp"
#include "Logic/Map.h"
#include "Logic/Unit.h"

#include <cstdint>

namespace sw::logic
{
	class LogMapDelegate final : public logic::Map::Delegate
	{
	public:
		LogMapDelegate(const uint64_t& tick, sw::EventLog& eventLog);

		void onCreated(uint32_t width, uint32_t height) override;
		void onUnitSpawned(Unit* unit, const Position& position) override;
		void onUnitMoved(Unit* unit, const Position& old, const Position& now) override;
		void onUnitDied(Unit* unit) override;

	private:
		const uint64_t& _tick;
		sw::EventLog& _eventLog;
	};

}

