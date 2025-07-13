#pragma once

#include "Unit.h"
#include <memory>

namespace sw::logic
{
	class Cell
	{
	public:
		[[nodiscard]] bool empty() const;
		void push(Unit::Ptr unit);
		[[nodiscard]] Unit::Ptr& get();
		[[nodiscard]] const Unit::Ptr& get() const;
		void clear();

	private:
		Unit::Ptr _unit = nullptr;
	};
}
