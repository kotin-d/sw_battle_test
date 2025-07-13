#pragma once

#include "Damager.h"
#include <cinttypes>

namespace sw::logic
{
	// компонент отвечающий за здоровье и смерть фируры
	class IHealther
	{
	public:
		virtual ~IHealther() = default;
		[[nodiscard]] virtual uint32_t health() const = 0;
		virtual void takeAttack(const IDamager* damager) = 0;
		virtual void kill() = 0;
		[[nodiscard]] virtual bool isDied() const = 0;
	};

	// типичное здоровье и смерть
	class HealtherRegular final : public IHealther
	{
	public:
		explicit HealtherRegular(const uint32_t hp) : _maxHp(hp), _currentHp(hp) {}
		~HealtherRegular() override = default;
		[[nodiscard]] uint32_t health() const override {return _currentHp;}
		void takeAttack(const IDamager* damager) override{_currentHp = damager->changeHp(_currentHp);}
		void kill() override{_currentHp = 0;}
		[[nodiscard]] bool isDied() const override{return _currentHp == 0;}

	private:
		uint32_t _maxHp;
		uint32_t _currentHp;
	};

	// неуязвимый объект, который умирает по особому правилу (например мина)
	class HealtherSingle final : public IHealther
	{
	public:
		virtual ~HealtherSingle() = default;
		[[nodiscard]] uint32_t health() const override {return 0;}
		void takeAttack(const IDamager* damager) override {}
		void kill() override {_died = true;}
		[[nodiscard]] bool isDied() const override {return _died;}

	private:
		bool _died = false;
	};

}


