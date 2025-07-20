#include "AttackRange.h"
#include "Finder.h"
#include "Damager.h"

namespace sw::logic
{
	AttackRange::AttackRange(Unit& unit, const uint32_t range, const uint32_t agility)
		: AttackAction(unit)
	{
		setFinderStrategy(new FinderRange(range));
		setDamagerStrategy(new DamagerRange(agility));
	}
}