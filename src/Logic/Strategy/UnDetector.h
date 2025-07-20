#pragma once

#include "Helpers/Position.h"


namespace sw::logic
{
	class IFinder;

	// Тут самое сложное место.  Из-за проклятого ворона.  Это классический вариант двойной диспечерезации, но есть, но.
	// Двойнная диспечерезация дает таблицу соединения каждый с каждым. Но наша таблица соответствий очень вырожденная.
	// Реализовывать честную двойную диспечерезацию не имеет смысла, будет много одинаковости. Поэтому часть ее заменяем
	// просто динамической проверкой типа
	class IUnDetector
	{
	public:
		virtual ~IUnDetector() = default;
		[[nodiscard]] virtual bool check(const IFinder* finder, const Position& attacker, const Position& target) const = 0;
	};

	class UnDetectorFull final: public IUnDetector
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class UnDetectorOnlyClose final : public IUnDetector
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class UnDetectorOnlyRange final : public IUnDetector
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class UnDetectorRange final : public IUnDetector
	{

	};

}


