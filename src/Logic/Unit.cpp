#include "Unit.h"

#include "Delegate/LogUnitDelegate.h"
#include "Game.h"
#include "Map.h"
#include "Strategy/Finder.h"

namespace sw::logic
{
	Unit::Unit(const uint32_t id)
		: _id(id)
	{
	}

	void Unit::setDelegate(Delegate* delegate)
	{
		_delegate = delegate;
	}

	void Unit::setStartPoint(const Position& start)
	{
		_path->setStartPoint(start);
	}

	void Unit::setEndPoint(const Position& end)
	{
		_path->setEndPoint(end);
		if (_delegate)
			_delegate->onMarchStart(_id, _path->startPoint(), _path->endPoint());
	}

	bool Unit::finishPath() const
	{
		return _path->finish();
	}

	uint32_t Unit::id() const
	{
		return _id;
	}

	void Unit::move(Map& map)
	{
		if (_path->isGenerated() && !_path->finish()) {
			const auto old = _path->currentPosition();
			const auto now = _path->nextPosition();
			map.moveUnit(old, now);

			if (_path->finish() && _delegate)
				_delegate->onMarchEnd(_id, _path->currentPosition());
		}
	}

	bool Unit::checkReacher(const IFinder* finder, const Position& position) const
	{
		if (_reacher != nullptr)
			return _reacher->check(finder, position, _path->currentPosition());
		return true;
	}

	void Unit::takeDamage(const IDamager* damager)
	{
		_healther->takeAttack(damager);
	}

	bool Unit::oneAttack(Map& map, IFinder* finder, IDamager* damager)
	{
		auto enemy = finder->select(map, _path->currentPosition());
		if (enemy == nullptr)
			return false;

		enemy->takeDamage(damager);
		if (_delegate)
		 	_delegate->onAttack(_id, enemy->id(), damager->power(), enemy->health());

		if (enemy->isDied())
			 Game::instance().killUnit(enemy);

		return true;
	}

}