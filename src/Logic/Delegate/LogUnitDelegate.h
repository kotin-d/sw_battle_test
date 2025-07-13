#pragma once

#include "IO/System/EventLog.hpp"
#include "Logic/Unit.h"

#include <cstdint>

namespace sw::logic
{
	class LogUnitDelegate final : public sw::logic::Unit::Delegate
	{
	public:
		LogUnitDelegate(const uint64_t& tick, sw::EventLog& eventLog);

		void onMarchStart(uint32_t id, const Position& start, const Position& end) override;
		void onMarchEnd(uint32_t id, const Position& end) override;
		void onAttack(uint32_t id, uint32_t target, uint32_t damage, uint32_t healther) override;

	private:
		const uint64_t& _tick;
		sw::EventLog& _eventLog;
	};
}
