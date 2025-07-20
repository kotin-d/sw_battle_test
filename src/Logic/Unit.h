#pragma once

#include "Helpers/Position.h"
#include "Strategy/Healther.h"
#include "Strategy/IPath.h"
#include "Strategy/UnDetector.h"
#include "Strategy/Action.h"
#include <cstdint>
#include <list>
#include <memory>


namespace sw::logic
{
	class Map;
	class IFinder;
	class IDamager;

	class Unit
	{
	public:
		class Delegate
		{
		public:
			virtual ~Delegate() = default;
			virtual void onMarchStart(uint32_t id, const Position& start, const Position& end) {};
			virtual void onMarchEnd(uint32_t id, const Position& end) {};
			virtual void onAttack(uint32_t id, uint32_t target, uint32_t damage, uint32_t hp) {};
		};

	public:
		explicit Unit(uint32_t id);
		virtual ~Unit() = default;

		[[nodiscard]] virtual const char* name() const = 0;
		void setDelegate(Delegate* delegate);
		Delegate *getDelegate() const {return _delegate;}

		void setPathStrategy(IPath* strategy);
		void setHealtherStrategy(IHealther* strategy);
		void setUnDetectorStrategy(IUnDetector* strategy);

		[[nodiscard]] IPath* getPath() const { return _path.get(); }
		[[nodiscard]] IHealther* getHealther() const { return _healther.get(); }
		[[nodiscard]] IUnDetector* getUnDetector() const { return _unDetector.get(); }

		[[nodiscard]] uint32_t id() const;

		void pushAction(Action* action);

		void setStartPoint(const Position& start);
		void setEndPoint(const Position& end);

		void makeTurn(Map& map);

	private:
		uint32_t _id = 0;

		std::unique_ptr<IPath> _path = nullptr;
		std::unique_ptr<IHealther> _healther = nullptr;
		std::unique_ptr<IUnDetector> _unDetector = nullptr;

		std::list<std::unique_ptr<Action>> _actions;

		Delegate* _delegate = nullptr;
	};
}


