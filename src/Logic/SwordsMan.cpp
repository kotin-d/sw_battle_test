#include "SwordsMan.h"

#include "Map.h"
#include "Strategy/PathLinear.h"

namespace sw::logic
{
	SwordsMan::SwordsMan(const uint32_t id, const uint32_t hp, const uint32_t strength)
		: Unit(id)
	{
		_healther = std::make_unique<HealtherRegular>(hp);
		_path = std::make_unique<PathLinear>();
		_reacher = std::make_unique<ReacherFull>();
		_finder = std::make_unique<FinderClose>();
		_damager = std::make_unique<DamagerClose>(strength);
	}

	bool SwordsMan::attack(Map& map)
	{
		return oneAttack(map, _finder.get(), _damager.get());
	}

}