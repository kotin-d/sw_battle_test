#include "UnDetector.h"
#include "Finder.h"
#include <typeinfo>

namespace sw::logic
{
	bool UnDetectorFull::check(const IFinder* finder, const Position& attacker, const Position& target) const
	{
		return true;
	}

	bool UnDetectorOnlyClose::check(const IFinder* finder, const Position& position, const Position& target) const
	{
		// без RTTI будет двойной перевызов. Так что RTTI тут к месту.
		return typeid(*finder) == typeid(FinderClose);
	}

	bool UnDetectorOnlyRange::check(const IFinder* finder, const Position& attacker, const Position& target) const
	{
		return typeid(*finder) == typeid(FinderRange);
	}
}