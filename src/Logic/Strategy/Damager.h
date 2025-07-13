#pragma once
#include <cstdint>

namespace sw::logic
{
	// компонент повреждения
	class IDamager
	{
	public:
		virtual ~IDamager() = default;
		[[nodiscard]] virtual uint32_t changeHp(uint32_t hp) const = 0;
		// нужен исключительно что бы правильно работал логер. Для остальной работы этот параметр не нужен
		[[nodiscard]] virtual uint32_t power() const = 0;
	};

	// вспомогательный дамагер
	class DamagerHit: public IDamager
	{
	public:
		~DamagerHit() override = default;
		explicit DamagerHit(const uint32_t power) : _power(power) {};
		[[nodiscard]] uint32_t power() const override { return _power; }
		[[nodiscard]] uint32_t changeHp(const uint32_t hp) const override
		{
			if (hp < _power)
				return 0;
			return hp - _power;
		}

	private:
		uint32_t _power;
	};

	// повреждение в ближнем бою
	class DamagerClose final : public DamagerHit
	{
	public:
		~DamagerClose() override = default;
		explicit DamagerClose(const uint32_t power) : DamagerHit(power) {};
	};

	// повреждение в дальнем бою
	class DamagerRange final : public DamagerHit
	{
	public:
		~DamagerRange() override = default;
		explicit DamagerRange(const uint32_t agility) : DamagerHit(agility) {};
	};

	// лечение
	class DamagerHeal final : public IDamager
	{
	public:
		~DamagerHeal() override = default;
		explicit DamagerHeal(const uint32_t spirit) : _spirit(spirit) {};
		[[nodiscard]] uint32_t power() const override {return _spirit;}
		[[nodiscard]] uint32_t changeHp(const uint32_t hp) const override
		{
			return hp + _spirit;
		}

	private:
		uint32_t _spirit;
	};

	// повреждение взрывом
	class DamagerExplosion final : public DamagerHit
	{
	public:
		~DamagerExplosion() override = default;
		explicit DamagerExplosion(const uint32_t power) : DamagerHit(power) {};
	};
}
