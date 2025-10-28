//
// Created by kirill on 10/28/2025.
//

#include "EventSystem.hpp"


using namespace sw;

void EventSystem::unsubscribe(EventSystem::SubId id) noexcept
{
	for (auto it = _subs.begin(); it != _subs.end(); ++it)
	{
		if (std::erase_if(it->second, [id](const auto& info){return info.id == id;}) > 0)
		{
			return;
		}
	}
}

EventSystem::SubId EventSystem::genNextId()
{
	return ++_nextId;
}

void EventSystem::post(std::any&& event)
{
	if (!event.has_value())
	{
		return;
	}
	const auto type = std::type_index(event.type());
	auto it = _subs.find(type);
	if (it == _subs.end())
	{
		return;
	}
	for (const auto& info : it->second)
	{
		info.callback(event);
	}
}
