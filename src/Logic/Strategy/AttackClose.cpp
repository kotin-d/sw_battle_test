#include "AttackClose.h"
#include "Finder.h"
#include "Damager.h"


namespace sw::logic
{
	AttackClose::AttackClose(Unit& unit, const uint32_t strength)
		: AttackAction(unit)
	{
		setFinderStrategy(new FinderClose());
		setDamagerStrategy(new DamagerClose(strength));
	}
}