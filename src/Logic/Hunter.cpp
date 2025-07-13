#include "Hunter.h"
#include "Map.h"
#include "Strategy/PathLinear.h"

namespace sw::logic
{
	Hunter::Hunter(const uint32_t id, const uint32_t hp, const uint32_t strength, const uint32_t agility, const uint32_t range)
		: Unit(id)
	{
		_healther = std::make_unique<HealtherRegular>(hp);
		_path = std::make_unique<PathLinear>();
		_reacher = std::make_unique<ReacherFull>();

		_finderClose = std::make_unique<FinderClose>();
		_damagerClose = std::make_unique<DamagerClose>(strength);

		_finderRange = std::make_unique<FinderRange>(range);
		_damagerRange = std::make_unique<DamagerClose>(agility);
	}

	bool Hunter::attack(Map& map)
	{
		if (oneAttack(map, _finderClose.get(), _damagerClose.get()))
			return true;
		return oneAttack(map, _finderRange.get(), _damagerRange.get());
	}

}