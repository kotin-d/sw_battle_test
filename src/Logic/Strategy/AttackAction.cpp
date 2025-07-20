#include "AttackAction.h"
#include "Logic/Map.h"
#include "Logic/Unit.h"
#include "Logic/Game.h"


namespace sw::logic
{
	bool AttackAction::execute(Map& map)
	{
		if (_finder == nullptr || _damager == nullptr)
			return false;

		auto enemy = _finder->select(map, parent().getPath()->currentPosition());
		if (enemy == nullptr)
			return false;

		auto heater = enemy->getHealther();
		if (heater != nullptr)
		{
			heater->takeAttack(_damager.get());

			if (parent().getDelegate())
				parent().getDelegate()->onAttack(parent().id(), enemy->id(), _damager->power(), heater->health());

			if (heater->isDied())
				Game::instance().killUnit(enemy->id());

			return true;
		}
		return false;
	}
}