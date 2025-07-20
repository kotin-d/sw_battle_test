#include "Finder.h"
#include "Logic/Map.h"
#include <algorithm>
#include <random>


namespace sw::logic
{
	namespace
	{
		std::vector<Unit*> findRound(const Map& map, const Position& position, const uint32_t range)
		{
			std::vector<Unit*> result;
			if (range < 1)
				return result;

			const int startX = static_cast<int>(position.x) - static_cast<int>(range);
			const int finishX = static_cast<int>(position.x) + static_cast<int>(range);

			const int startY = static_cast<int>(position.y) - static_cast<int>(range);
			const int finishY = static_cast<int>(position.y) + static_cast<int>(range);

			for (int index = startX; index != finishX + 1; ++index) {
				if (map.isExistCell(index, startY) &&
					map.isExistUnit({static_cast<uint32_t>(index), static_cast<uint32_t>(startY)})) {
					result.push_back(map.getUnit({static_cast<uint32_t>(index), static_cast<uint32_t>(startY)}));
					}
				if (map.isExistCell(index, finishY) &&
					map.isExistUnit({static_cast<uint32_t>(index), static_cast<uint32_t>(finishY)})) {
					result.push_back(map.getUnit({static_cast<uint32_t>(index), static_cast<uint32_t>(finishY)}));
					}
			}

			for (int index = startY + 1; index < finishY; ++index)
			{
				if (map.isExistCell(startX, index) &&
					map.isExistUnit({static_cast<uint32_t>(startX), static_cast<uint32_t>(index)})) {
					result.push_back(map.getUnit({static_cast<uint32_t>(startX), static_cast<uint32_t>(index)}));
					}
				if (map.isExistCell(finishX, index) &&
					map.isExistUnit({static_cast<uint32_t>(finishX), static_cast<uint32_t>(index)})) {
					result.push_back(map.getUnit({static_cast<uint32_t>(finishX), static_cast<uint32_t>(index)}));
					}
			}
			return result;
		}

		std::vector<Unit*> findRound(const Map& map, const Position& position, const uint32_t min, const uint32_t max)
		{
			std::vector<Unit*> result;
			for (uint32_t index = min; index <= max; ++index) {
				const auto round = findRound(map, position, index);
				std::copy(round.begin(), round.end(), std::back_inserter(result));
			}
			return result;
		}

		Unit* randomOne(const std::vector<Unit*>& units)
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<size_t> dist(0, units.size() - 1);
			return units[dist(mt)];
		}

		Unit* takeFirst(const std::vector<Unit*>& units)
		{
			return units.front();
		}
	}


	Unit* IFinder::select(const Map& map, const Position& position) const
	{
		auto units = selectAll(map, position);
		if (units.empty())
			return nullptr;

		return randomOne(units);
	}

	std::vector<Unit*> IFinder::selectAll(const Map& map, const Position& position) const
	{
		auto units = findAll(map, position);

		units.erase(std::remove_if(units.begin(), units.end(),
		  	[this, &position](const Unit* unit)
		  	{
		  		if (unit != nullptr && unit->getUnDetector() != nullptr)
		  			return !unit->getUnDetector()->check(this, position, unit->getPath()->currentPosition());
		  		return false;
		  	}),
		  	units.end());

		return units;
	}

	std::vector<Unit*>  FinderClose::findAll(const Map& map, const Position& position) const
	{
		return findRound(map, position, 1);
	}

	std::vector<Unit*> FinderRange::findAll(const Map& map, const Position& position) const
	{
		// +1 для range из-за странного понимания дистанции выстрела. Он не сколько клеток, а через сколько клеток
		return findRound(map, position, 2, _range + 1);
	}

}