#include "Unit.h"


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

	void Unit::setPathStrategy(IPath* strategy)
	{
		_path.reset(strategy);
	}

	void Unit::setHealtherStrategy(IHealther* strategy)
	{
		_healther.reset(strategy);
	}

	void Unit::setUnDetectorStrategy(IUnDetector* strategy)
	{
		_unDetector.reset(strategy);
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

	uint32_t Unit::id() const
	{
		return _id;
	}

	void Unit::pushAction(Action* action)
	{
		if (action != nullptr)
			_actions.emplace_back(action);
	}

	void Unit::makeTurn(Map& map)
	{
		for (auto& action : _actions)
		{
			if (action->execute(map))
				return;
		}
	}

}