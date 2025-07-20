#include "Game.h"
#include <fstream>


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
		_model.clear();
	}

	void Game::createMap(const uint32_t width, const uint32_t height)
	{
		clear();
		_map.create(width, height);
	}

	void Game::spawn(const std::shared_ptr<Unit>& unit, const Position& position)
	{
		if (_model.exist(unit))
			throw std::runtime_error("Unit already exist, id = " + std::to_string(unit->id()));

		unit->setDelegate(&_logUnitDelegate);
		_model.push(unit);
		_map.spawn(unit, position);
	}

	void Game::march(const uint32_t id, const Position& position)
	{
		if (_model.exist(id))
		{
			auto unit = _model.findUnit(id);
			unit->setEndPoint(position);
		}
		else
		{
			throw std::runtime_error("Unit not exist, id = " + std::to_string(id));
		}
	}

	void Game::killUnit(const uint32_t id)
	{
		if (_model.exist(id))
		{
			_map.kill(_model.findUnit(id));
			_model.erase(id);
		}
		else
		{
			throw std::runtime_error("Unit not exist, id = " + std::to_string(id));
		}
	}

	bool Game::isGameOver() const
	{
		if (_model.size() <= 1)
			return true;
		return _model.isEveryFinish();
	}

	void Game::makeTurn()
	{
		++_turn;
		_model.forEach([this](const std::shared_ptr<Unit>& unit){unit->makeTurn(this->_map);});
	}

}