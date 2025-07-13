#pragma once

#include "Helpers/Position.h"


namespace sw::logic
{
	class IFinder;

	// Тут самое сложное место.  Из-за проклятого ворона.  Это классический вариант двойной диспечерезации, но есть, но.
	// Двойнная диспечерезация дает таблицу соединения каждый с каждым. Но наша таблица соответствий очень вырожденная.
	// Реализовывать честную двойную диспечерезацию не имеет смысла, будет много одинаковости. Поэтому часть ее заменяем
	// просто динамической проверкой типа
	class IReacher
	{
	public:
		virtual ~IReacher() = default;
		[[nodiscard]] virtual bool check(const IFinder* finder, const Position& attacker, const Position& target) const = 0;
	};

	class ReacherFull final: public IReacher
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class ReacherOnlyClose final : public IReacher
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class ReacherOnlyRange final : public IReacher
	{
	public:
		[[nodiscard]] bool check(const IFinder* finder, const Position& attacker, const Position& target) const override;
	};

	class ReacherRange final : public IReacher
	{

	};

}


