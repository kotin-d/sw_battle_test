#include "SwordsMan.h"
#include "Strategy/PathLinear.h"
#include "Strategy/Healther.h"
#include "Strategy/UnDetector.h"
#include "Strategy/AttackClose.h"
#include "Strategy/Move.h"


namespace sw::logic
{
	SwordsMan::SwordsMan(const uint32_t id, const uint32_t hp, const uint32_t strength)
		: Unit(id)
	{
		setPathStrategy(new PathLinear());
		setHealtherStrategy(new HealtherRegular(hp));
		setUnDetectorStrategy(new UnDetectorFull());

		pushAction(new AttackClose(*this, strength));
		pushAction(new Move(*this));
	}
}