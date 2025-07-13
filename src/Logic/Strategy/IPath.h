#pragma once

#include "Helpers/Position.h"

namespace sw::logic
{
	// Стратегия пути
	class IPath
	{
	public:
		virtual ~IPath() = default;

		[[nodiscard]] virtual bool isGenerated() const = 0;
		[[nodiscard]] virtual Position currentPosition() const = 0;
		[[nodiscard]] virtual Position nextPosition() = 0;

		[[nodiscard]] virtual bool finish() const {return currentPosition() == _endPoint;}

		// Эти две функции нужны только для логера
		[[nodiscard]] Position startPoint() const {return _startPoint;}
		[[nodiscard]] Position endPoint() const {return _endPoint;}

		void setStartPoint(const Position& startPoint) {_startPoint = startPoint;}
		void setEndPoint(const Position& endPoint) {_endPoint = endPoint; generate();}

	protected:
		virtual void generate() {}

		Position _startPoint;
		Position _endPoint;
	};
}

