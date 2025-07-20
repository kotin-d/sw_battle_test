#pragma once

#include <list>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include "Logic/Unit.h"
#include <functional>


namespace sw::logic
{
	class Model
	{
	public:
		void clear();
		[[nodiscard]] size_t size() const;

		[[nodiscard]] bool exist(const std::shared_ptr<Unit>& unit) const;
		[[nodiscard]] bool exist(uint32_t id) const;
		void push(const std::shared_ptr<Unit>& unit);

		void erase(uint32_t id);

		[[nodiscard]] bool isForEach(const std::function<bool(const std::shared_ptr<Unit>&)>& pred) const;
		[[nodiscard]] bool isEveryFinish() const;

		void forEach(const std::function<void(const std::shared_ptr<Unit>&)>& function);

		std::shared_ptr<Unit>& findUnit(uint32_t id);

	private:
		std::list<uint32_t> _orders;
		std::unordered_map<uint32_t, std::shared_ptr<Unit>> _units;
	};
}


