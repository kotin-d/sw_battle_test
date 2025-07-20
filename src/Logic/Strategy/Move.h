#pragma once

#include "Action.h"


namespace sw::logic
{
	class Move final : public Action
	{
	public:
		explicit Move(Unit& parent) : Action(parent) {}
		~Move() override = default;

		bool execute(Map& map) override;
	};
}

