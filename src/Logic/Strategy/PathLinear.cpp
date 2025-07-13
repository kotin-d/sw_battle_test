#include "PathLinear.h"
#include <cmath>


namespace sw::logic
{
	bool PathLinear::isGenerated() const
	{
		return _isGenerated;
	}

	Position PathLinear::currentPosition() const
	{
		return _current;
	}

	Position PathLinear::nextPosition()
	{
		if (finish())
			return _current;

		_x += _deltaX;
		_y += _deltaY;
		_current.x = static_cast<int>(std::round(_x));
		_current.y = static_cast<int>(std::round(_y));

		return _current;
	}

	void PathLinear::generate()
	{
		_current = _startPoint;
		_x = static_cast<double>(_current.x);
		_y = static_cast<double>(_current.y);
		if (_startPoint == _endPoint)
			return;

		const int xDif = static_cast<int>(_endPoint.x) - static_cast<int>(_startPoint.x);
		const int yDif = static_cast<int>(_endPoint.y) - static_cast<int>(_startPoint.y);
		const int steps = std::max(std::abs(xDif), std::abs(yDif));

		_deltaX = static_cast<double>(xDif) / static_cast<double>(steps);
		_deltaY = static_cast<double>(yDif) / static_cast<double>(steps);
		_isGenerated = true;
	}
}