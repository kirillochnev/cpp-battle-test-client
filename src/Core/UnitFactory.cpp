//
// Created by kirill on 10/28/2025.
//

#include "UnitFactory.hpp"
#include <stdexcept>

using namespace sw;


UnitFactory::UnitFactory(Game& game):
	_game(game)
{

}

UnitFactory::~UnitFactory() = default;

bool UnitFactory::unRegisterUnitKind(const std::string& kind)
{
	return _allocators.erase(kind) > 0;
}

bool UnitFactory::registerUnitKind(const std::string& kind, const UnitFactory::UnitAllocator& allocator)
{
	if (!allocator)
	{
		return false;
	}
	_allocators[kind] = allocator;
	return true;
}

void UnitFactory::onError(const std::string& unitKind, const std::any& data, const std::string_view& reason) const
{
	throw std::runtime_error("Can not allocate unit kind: [" + unitKind + "], reason: " + std::string(reason));
}

UnitPtr UnitFactory::allocateUnit(const std::string& kind, const std::any& data)
{
	UnitPtr result;
	auto it = _allocators.find(kind);
	if (it == _allocators.end())
	{
		onError(kind, data, "Can not find allocator");
		return result;
	}

	result = it->second(_game, data);
	if (result == nullptr)
	{
		onError(kind, data, "Factory returned nullptr");
	}

	return result;
}
