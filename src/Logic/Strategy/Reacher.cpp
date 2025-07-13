#include "Reacher.h"
#include "Finder.h"
#include <typeinfo>

namespace sw::logic
{
	bool ReacherFull::check(const IFinder* finder, const Position& attacker, const Position& target) const
	{
		return true;
	}

	bool ReacherOnlyClose::check(const IFinder* finder, const Position& position, const Position& target) const
	{
		// без RTTI будет двойной перевызов. Так что RTTI тут к месту.
		return typeid(*finder) == typeid(FinderClose);
	}

	bool ReacherOnlyRange::check(const IFinder* finder, const Position& attacker, const Position& target) const
	{
		return typeid(*finder) == typeid(FinderRange);
	}
}