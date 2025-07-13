#pragma once

#include "Helpers/Position.h"
#include "Strategy/Healther.h"
#include "Strategy/IPath.h"
#include "Strategy/Reacher.h"
#include <cstdint>
#include <memory>

namespace sw::logic
{
	class Map;
	class IFinder;
	class IDamager;

	class Unit
	{
	public:
		using Ptr = std::shared_ptr<Unit>;

		class Delegate
		{
		public:
			virtual ~Delegate() = default;
			virtual void onMarchStart(uint32_t id, const Position& start, const Position& end) {};
			virtual void onMarchEnd(uint32_t id, const Position& end) {};
			virtual void onAttack(uint32_t id, uint32_t target, uint32_t damage, uint32_t healther) {};
		};

	public:
		Unit(uint32_t id);
		virtual ~Unit() = default;

		[[nodiscard]] virtual const char* name() const = 0;
		void setDelegate(Delegate* delegate);

		[[nodiscard]] uint32_t id() const;

		// Path
		void setStartPoint(const Position& start);
		void setEndPoint(const Position& end);
		[[nodiscard]] bool finishPath() const;
		[[nodiscard]] Position currentPosition() const {return _path->currentPosition();}
		//

		// Health
		[[nodiscard]] uint32_t health() const { return _healther->health();}
		[[nodiscard]] bool isDied() const { return _healther->isDied();}
		//

		virtual bool attack(Map& map) = 0;
		virtual void move(Map& map);

		bool checkReacher(const IFinder* finder, const Position& position) const;
		void takeDamage(const IDamager* damager);

	protected:
		bool oneAttack(Map& map, IFinder* finder, IDamager* damager);

	protected:
		uint32_t _id = 0;

		std::unique_ptr<IPath> _path = nullptr;
		std::unique_ptr<IReacher> _reacher = nullptr;
		std::unique_ptr<IHealther> _healther = nullptr;

		Delegate* _delegate = nullptr;
	};
}


