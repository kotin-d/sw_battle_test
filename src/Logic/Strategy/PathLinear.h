#pragma once

#include "IPath.h"


namespace sw::logic
{
	// стратегия линейного пути, на одну клетку
	class PathLinear final : public IPath
	{
	public:
		~PathLinear() override = default;

		[[nodiscard]] bool isGenerated() const override;
		[[nodiscard]] Position currentPosition() const override;
		[[nodiscard]] Position nextPosition() override;

		// TODO: функция не оптимизированна, в ней есть даже деление.
		void generate() override;

	private:
		double _deltaX = 0.0;
		double _deltaY = 0.0;
		double _x = 0.0;
		double _y = 0.0;
		Position _current;
		bool _isGenerated = false;
	};
}

