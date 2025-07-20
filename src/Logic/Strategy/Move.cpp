#include "Move.h"
#include "Logic/Unit.h"
#include "Logic/Map.h"


namespace sw::logic
{
	bool Move::execute(Map& map)
	{
		if (parent().getPath() != nullptr)
		{
			if (parent().getPath()->isGenerated() && !parent().getPath()->finish())
			{
				const auto old = parent().getPath()->currentPosition();
				const auto now = parent().getPath()->nextPosition();
				map.moveUnit(old, now);

				if (parent().getPath()->finish() && parent().getDelegate())
					parent().getDelegate()->onMarchEnd(parent().id(), parent().getPath()->currentPosition());
			}
			return false;
		}
		return true;
	}
}