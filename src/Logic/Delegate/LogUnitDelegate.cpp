#include "LogUnitDelegate.h"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitAttacked.hpp"

namespace sw::logic
{
	LogUnitDelegate::LogUnitDelegate(const uint64_t& tick, EventLog& eventLog)
		: _tick(tick)
		, _eventLog(eventLog)
	{
	}

	void LogUnitDelegate::onMarchStart(const uint32_t id, const Position& start, const Position& end)
	{
		_eventLog.log(_tick, io::MarchStarted{id, start.x, start.y, end.x, end.y});
	}

	void LogUnitDelegate::onMarchEnd(const uint32_t id, const Position& end)
	{
		_eventLog.log(_tick, io::MarchEnded{id, end.x, end.y});
	}

	void LogUnitDelegate::onAttack(const uint32_t id, const uint32_t target, const uint32_t damage, const uint32_t healther)
	{
		_eventLog.log(_tick, io::UnitAttacked{id, target, damage, healther});
	}
}