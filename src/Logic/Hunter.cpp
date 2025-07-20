#include "Hunter.h"
#include "Strategy/PathLinear.h"
#include "Strategy/Healther.h"
#include "Strategy/UnDetector.h"
#include "Strategy/AttackClose.h"
#include "Strategy/AttackRange.h"
#include "Strategy/Move.h"


namespace sw::logic
{
	Hunter::Hunter(const uint32_t id, const uint32_t hp, const uint32_t strength, const uint32_t agility, const uint32_t range)
		: Unit(id)
	{
		setPathStrategy(new PathLinear());
		setHealtherStrategy(new HealtherRegular(hp));
		setUnDetectorStrategy(new UnDetectorFull());

		pushAction(new AttackClose(*this, strength));
		pushAction(new AttackRange(*this, range, agility));
		pushAction(new Move(*this));
	}
}