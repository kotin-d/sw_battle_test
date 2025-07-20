#pragma once

#include "IO/System/EventLog.hpp"
#include "Logic/Map.h"
#include "Logic/Unit.h"
#include <memory>
#include <cstdint>

namespace sw::logic
{
	class LogMapDelegate final : public Map::Delegate
	{
	public:
		LogMapDelegate(const uint64_t& tick, EventLog& eventLog);

		void onCreated(uint32_t width, uint32_t height) override;
		void onUnitSpawned(const std::shared_ptr<Unit>& unit, const Position& position) override;
		void onUnitMoved(const std::shared_ptr<Unit>& unit, const Position& old, const Position& now) override;
		void onUnitDied(const std::shared_ptr<Unit>& unit) override;

	private:
		const uint64_t& _tick;
		EventLog& _eventLog;
	};

}

