#pragma once

#include <vector>
#include <memory>
#include "Cell.h"


namespace sw::logic
{
	class Map
	{
	public:
		class Delegate
		{
		public:
			virtual ~Delegate() = default;
			virtual void onCreated([[maybe_unused]] uint32_t width, [[maybe_unused]] uint32_t height) {};
			virtual void onUnitSpawned([[maybe_unused]] const std::shared_ptr<Unit>& unit, [[maybe_unused]] const Position& position) {};
			virtual void onUnitMoved([[maybe_unused]] const std::shared_ptr<Unit>& unit, [[maybe_unused]] const Position& old, [[maybe_unused]] const Position& now) {};
			virtual void onUnitDied([[maybe_unused]] const std::shared_ptr<Unit>& unit) {};
		};

	public:
		Map() = default;
		void setDelegate(Delegate* delegate);

		[[nodiscard]] uint32_t height() const;
		[[nodiscard]] uint32_t width() const;

		// тут принимаем именно int.
		[[nodiscard]] bool isExistCell(int x, int y) const;
		[[nodiscard]] bool isExistUnit(const Position& position) const;

		[[nodiscard]] bool isEmpty() const;
		void clear();

		void create(uint32_t width, uint32_t height);
		void spawn(const std::shared_ptr<Unit>& unit, const Position& position);
		void kill(const std::shared_ptr<Unit>& unit);

		// есть строгое указание, что в одной клетке может находиться только один юнит.
		// но будут летающие юниты, поэтому передавать id все же придется.
		void moveUnit(const Position& old, const Position& now);

		[[nodiscard]] Unit* getUnit(const Position& position) const;

	private:
		[[nodiscard]] size_t index(const Position& position) const;

		Cell& cell(const Position& position);
		[[nodiscard]] const Cell& cell(const Position& position) const;

		size_t _height = 0;
		size_t _width = 0;

		std::vector<Cell> _cells;

		Delegate* _delegate = nullptr;

		const uint32_t MAX_WIDTH = 128;
		const uint32_t MAX_HEIGHT = 128;
	};
}

