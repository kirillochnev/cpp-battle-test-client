//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <Core/Types.hpp>

#include <any>
#include <map>
#include <memory>
#include <typeindex>
#include <functional>

namespace sw
{

	using Subscription = std::shared_ptr<void>;

	class EventSystem
	{
		using EventHandle = std::function<void (const std::any&)>;

	public:
		using SubId = uint32_t;

		void unsubscribe(SubId id) noexcept;

		template <typename TEvent, typename THandle>
		Subscription subscribe(THandle&& handle, SubId* out = nullptr)
		{
			static const auto type = std::type_index(typeid(TEvent));
			auto id = genNextId();

			const auto deleter = [id, this](auto){
				unsubscribe(id);
			};
			if (out != nullptr)
			{
				*out = id;
			}
			EventHandle commonHandle = [handle = std::move(handle)](const std::any& event) {
				handle(std::any_cast<const TEvent&>(event));
			};
			_subs[type].emplace_back(id, std::move(commonHandle));
			return Subscription(nullptr, deleter);
		}

		void post(std::any&& event);
	private:
		Id _nextId = 0;
		struct SubInfo
		{
			SubId id;
			EventHandle callback;
		};

		std::map<std::type_index, std::vector<SubInfo> > _subs;
		SubId genNextId();
	};

}