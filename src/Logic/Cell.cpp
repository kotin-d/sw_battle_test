#include "Cell.h"

#include <utility>

namespace sw::logic
{
	bool Cell::empty() const
	{
		return _unit == nullptr;
	}

	void Cell::push(Unit::Ptr unit)
	{
		_unit = std::move(unit);
	}

	Unit::Ptr& Cell::get()
	{
		return _unit;
	}

	const Unit::Ptr& Cell::get() const
	{
		return _unit;
	}

	void Cell::clear()
	{
		_unit.reset();
	}
}