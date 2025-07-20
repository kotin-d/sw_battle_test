#pragma once

#include "Action.h"
#include <memory>
#include "Finder.h"
#include "Damager.h"


namespace sw::logic
{
	// Промежуточный класс, нужен только для удобства
	class AttackAction : public Action
	{
	public:
		explicit AttackAction(Unit& parent) : Action(parent) {}
		~AttackAction() override = default;

		void setFinderStrategy(IFinder* finder) {_finder.reset(finder);}
		void setDamagerStrategy(IDamager* damager) {_damager.reset(damager);}

		bool execute(Map& map) override;

	private:
		std::unique_ptr<IFinder> _finder = nullptr;
		std::unique_ptr<IDamager> _damager = nullptr;
	};
}