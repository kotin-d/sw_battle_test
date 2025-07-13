#pragma once

#include "IPath.h"


namespace sw::logic
{
	// стратегия пути, для неперемещаемого объекта
	class PathStand final : public IPath
	{
	public:
		~PathStand() override = default;

		[[nodiscard]] bool isGenerated() const override {return false;}
		[[nodiscard]] Position currentPosition() const override {return _startPoint;}
		[[nodiscard]] Position nextPosition() override {return _startPoint;}
		[[nodiscard]] bool finish() const override {return true;}

	};
}


