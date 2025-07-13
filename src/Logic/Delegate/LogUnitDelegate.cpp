#include "LogUnitDelegate.h"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitAttacked.hpp"

namespace sw::logic
{
	LogUnitDelegate::LogUnitDelegate(const uint64_t& tick, sw::EventLog& eventLog)
		: _tick(tick)
		, _eventLog(eventLog)
	{
	}

	void LogUnitDelegate::onMarchStart(const uint32_t id, const Position& start, const Position& end)
	{
		_eventLog.log(_tick, io::MarchStarted{id, start.x, start.y, end.x, end.y});
	}

	void LogUnitDelegate::onMarchEnd(uint32_t id, const Position& end)
	{
		_eventLog.log(_tick, io::MarchEnded{id, end.x, end.y});
	}

	void LogUnitDelegate::onAttack(uint32_t id, uint32_t target, uint32_t damage, uint32_t healther)
	{
		_eventLog.log(_tick, io::UnitAttacked{id, target, damage, healther});
	}
}