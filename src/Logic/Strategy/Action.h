#pragma once

namespace sw::logic
{
	class Map;
	class Unit;

	class Action
	{
	public:
		Action(Unit& parent) : _parent(parent) {}
		virtual ~Action() = default;
		virtual bool execute(Map& map) = 0;

	protected:
		[[nodiscard]] Unit& parent() {return _parent;}
		[[nodiscard]] const Unit& parent() const {return _parent;}

	private:
		Unit& _parent;
	};
}