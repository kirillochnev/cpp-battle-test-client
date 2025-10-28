//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <vector>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace sw
{

	class GameRule
	{
		const RuleBook* _owner = nullptr;
		friend RuleBook;
	public:
		[[nodiscard]] virtual int32_t priority() const noexcept {return 0;}
	protected:
		[[nodiscard]] const RuleBook& owner() const noexcept {return *_owner;}
	};

	class RuleBook : Uncopiable
	{
	public:
		template <typename TRule, typename... ARGS>
		auto apply(ARGS&&... args) const
		{
			using ResultType = typename TRule::ResultType;
			if constexpr (std::is_same_v<void, ResultType >)
			{
				for (const auto& rule : _rules)
				{
					if (auto typedRule = dynamic_cast<TRule*>(rule.get()))
					{
						if (typedRule->tryExecute(std::forward<ARGS>(args)...))
						{
							return;
						}
					}
				}
				TRule fallback;
				fallback._owner = this;
				if (!fallback.tryExecute(std::forward<ARGS>(args)...))
				{
					throw std::runtime_error(std::string("Can not apply any rule of type: ") + typeid(TRule).name());
				}
			}
			else
			{
				ResultType result;
				for (const auto& rule : _rules)
				{
					if (auto typedRule = dynamic_cast<TRule*>(rule.get()))
					{
						if (typedRule->tryExecute(result, std::forward<ARGS>(args)...))
						{
							return result;
						}
					}
				}
				TRule fallback;
				if (!fallback.tryExecute(result, std::forward<ARGS>(args)...))
				{
					throw std::runtime_error(std::string("Can not apply any rule of type: ") + typeid(TRule).name());
				}
				return result;
			}
		}

	template <typename T, typename... ARGS>
	void addRule(ARGS&&... args)
	{
		auto rule = std::make_unique<T>(std::forward<ARGS>(args)...);
		rule->_owner = this;
		_rules.emplace_back(std::move(rule));
		sortRules();
	}
	private:
		void sortRules();
		std::vector<std::unique_ptr<GameRule> > _rules;
	};
}