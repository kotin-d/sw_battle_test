#pragma once

#include "Unit.h"
#include <memory>

namespace sw::logic
{
	// одна клетка на карте
	class Cell
	{
	public:
		[[nodiscard]] bool empty() const { return _unit == nullptr;}
		void push(std::shared_ptr<Unit> unit) {_unit = std::move(unit);}
		[[nodiscard]] std::shared_ptr<Unit>& get() {return _unit;}
		[[nodiscard]] const std::shared_ptr<Unit>& get() const {return _unit;}
		void clear() {_unit.reset();}

	private:
		std::shared_ptr<Unit> _unit = nullptr;
	};
}
