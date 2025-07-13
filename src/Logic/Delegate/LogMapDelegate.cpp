#include "LogMapDelegate.h"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/Events/UnitDied.hpp"

namespace sw::logic
{
	LogMapDelegate::LogMapDelegate(const uint64_t& tick, sw::EventLog& eventLog)
		: _tick(tick)
		, _eventLog(eventLog)
	{
	}

	void LogMapDelegate::onCreated(const uint32_t width, const uint32_t height)
	{
		_eventLog.log(_tick, io::MapCreated{width, height});
	}

	void LogMapDelegate::onUnitSpawned(Unit* unit, const Position& position)
	{
		_eventLog.log(_tick, io::UnitSpawned{unit->id(), unit->name(), position.x, position.y});
	}

	void LogMapDelegate::onUnitMoved(Unit* unit, const Position& old, const Position& now)
	{
		_eventLog.log(_tick, io::UnitMoved{unit->id(), now.x, now.y});
	}

	void LogMapDelegate::onUnitDied(Unit* unit)
	{
		_eventLog.log(_tick, io::UnitDied{unit->id()});
	}

}