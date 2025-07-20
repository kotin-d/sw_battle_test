#include "Map.h"
#include <stdexcept>
#include <algorithm>

namespace sw::logic
{

	void Map::setDelegate(Delegate* delegate)
	{
		_delegate = delegate;
	}

	uint32_t Map::height() const
	{
		return _height;
	}

	uint32_t Map::width() const
	{
		return _width;
	}

	bool Map::isExistCell(const int x, const int y) const
	{
		return x >= 0 && x < _width && y >= 0 && y < _height;
	}

	bool Map::isExistUnit(const Position& position) const
	{
		return !cell(position).empty();
	}

	bool Map::isEmpty() const
	{
		return _cells.empty();
	}

	void Map::clear()
	{
		_height = 0;
		_width = 0;
		_cells.clear();
	}

	void Map::create(const uint32_t width, const uint32_t height)
	{
		if (width > MAX_WIDTH || height > MAX_HEIGHT)
			throw std::runtime_error("Missing map size width = " + std::to_string(width) + " height = " + std::to_string(height));

		if (!isEmpty())
			clear();

		_height = height;
		_width = width;
		_cells.resize(height * width);

		if (_delegate)
			_delegate->onCreated(_width, _height);
	}

	void Map::spawn(const std::shared_ptr<Unit>& unit, const Position& position)
	{
		if (position.x >= width() || position.y >= height())
			throw std::runtime_error("Position out of bounds x = " + std::to_string(position.x) + " y = " + std::to_string(position.y));

		unit->setStartPoint(position);
		cell(position).push(unit);

		if (_delegate)
			_delegate->onUnitSpawned(unit, position);
	}

	void Map::kill(const std::shared_ptr<Unit>& unit)
	{
		if (_delegate)
			_delegate->onUnitDied(unit);
		cell(unit->getPath()->currentPosition()).clear();
	}

	void Map::moveUnit(const Position& old, const Position& now)
	{
		std::swap(cell(old).get(), cell(now).get());
		if (_delegate)
			_delegate->onUnitMoved(cell(now).get(), old, now);
	}

	Cell& Map::cell(const Position& position)
	{
		return _cells[index(position)];
	}

	const Cell& Map::cell(const Position& position) const
	{
		return _cells[index(position)];
	}

	Unit* Map::getUnit(const Position& position) const
	{
		return cell(position).get().get();
	}

	size_t Map::index(const Position& position) const
	{
		return position.y * _width + position.x;
	}
}