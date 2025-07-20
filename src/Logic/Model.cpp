#include "Model.h"


namespace sw::logic
{
	void Model::clear()
	{
		_orders.clear();
		_units.clear();
	}

	size_t Model::size() const
	{
		return _orders.size();
	}

	bool Model::exist(const std::shared_ptr<Unit>& unit) const
	{
		return _units.contains(unit->id());
	}

	bool Model::exist(const uint32_t id) const
	{
		return _units.contains(id);
	}

	void Model::push(const std::shared_ptr<Unit>& unit)
	{
		_orders.push_back(unit->id());
		_units.emplace(unit->id(), unit);
	}

	void Model::erase(const uint32_t id)
	{
		_orders.remove(id);
		_units.erase(id);
	}

	bool Model::isForEach(const std::function<bool(const std::shared_ptr<Unit>&)>& pred) const
	{
		for (const auto& unit : _units)
		{
		 	if (!pred(unit.second))
				return false;
		}
		return true;
	}

	bool Model::isEveryFinish() const
	{
		return isForEach([](const std::shared_ptr<Unit>& unit) ->bool {return unit->getPath()->finish();});
	}

	void Model::forEach(const std::function<void(const std::shared_ptr<Unit>&)>& function)
	{
		for (const auto index : _orders)
		{
			auto& unit = _units[index];
			function(unit);
		}
	}

	std::shared_ptr<Unit>& Model::findUnit(const uint32_t id)
	{
		return _units[id];
	}

}