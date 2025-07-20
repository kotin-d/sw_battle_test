#pragma once

#include "Helpers/Position.h"
#include "Logic/Unit.h"
#include <memory>
#include <vector>


namespace sw::logic
{
	class Map;

	class IFinder
	{
	public:
		explicit IFinder() = default;
		virtual ~IFinder() = default;
		[[nodiscard]] virtual Unit* select(const Map& map, const Position& position) const;
		[[nodiscard]] virtual std::vector<Unit*> selectAll(const Map& map, const Position& position) const;
		[[nodiscard]] virtual std::vector<Unit*> findAll(const Map& map, const Position& position) const = 0;
	};

	class FinderClose final : public IFinder
	{
	public:
		~FinderClose() override = default;
		explicit FinderClose() = default;
		[[nodiscard]] std::vector<Unit*> findAll(const Map& map, const Position& position) const override;
	};

	class FinderRange final : public IFinder
	{
	public:
		~FinderRange() override = default;
		explicit FinderRange(const uint32_t range) : _range(range) {}
		[[nodiscard]] std::vector<Unit*> findAll(const Map& map, const Position& position) const override;

	private:
		uint32_t _range;
	};

}



