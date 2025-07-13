#include "Game.h"
#include <fstream>
#include <algorithm>
#include <bits/locale_facets_nonio.h>

namespace sw::logic
{
	Game::Game()
		: _logMapDelegate(_turn, _eventLog)
		, _logUnitDelegate(_turn, _eventLog)
	{
		_map.setDelegate(&_logMapDelegate);
	}

	Game& Game::instance()
	{
		static Game instance;
		return instance;
	}

	void Game::clear()
	{
		_turn = 1;
		_map.clear();
		_orders.clear();
		_units.clear();
	}

	void Game::createMap(const uint32_t width, const uint32_t height)
	{
		clear();
		_map.create(width, height);
	}

	void Game::spawn(const Unit::Ptr& unit, const Position& position)
	{
		if (exist(unit.get()))
			throw std::runtime_error("Unit already exist, id = " + std::to_string(unit->id()));

		unit->setDelegate(&_logUnitDelegate);
		_orders.push_back(unit->id());
		_units.emplace(unit->id(), unit);
		_map.spawn(unit, position);
	}

	void Game::killUnit(Unit* unit)
	{
		std::erase_if(_orders, [&unit](const int value){ return unit->id() == value; });		_units.erase(unit->id());
		_map.kill(unit);
	}

	bool Game::isGameOver() const
	{
		if (_orders.size() <= 1)
			return true;

		for (const auto& unit : _units)
		{
			if (!unit.second->finishPath())
				return false;
		}
		return true;
	}

	void Game::makeTurn()
	{
		++_turn;
		for (const auto index : _orders)
		{
			auto unit = findUnit(index);
			if (!unit->attack(_map))
				unit->move(_map);
		}
	}

	bool Game::exist(Unit* unit) const
	{
		return _units.contains(unit->id());
	}

	Unit* Game::findUnit(const uint32_t id) const
	{
		const auto iter = _units.find(id);
		if (iter == _units.end())
			return nullptr;
		return iter->second.get();
	}

}