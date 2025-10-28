//
// Created by kirill on 10/28/2025.
//

#include <Core/Types.hpp>
#include <Core/GameRule.hpp>
#include <Core/EventSystem.hpp>
#include <Core/UnitFactory.hpp>
#include <Core/BattleField.hpp>

namespace sw
{
	class Game
	{
		RuleBook _ruleBook;
		std::unique_ptr<BattleField> _battleField;
		EventSystem _events;
		UnitFactory _unitFactory;
	public:
		Game();
		~Game();

		RuleBook& ruleBook() noexcept {return _ruleBook;}
		const RuleBook& ruleBook() const noexcept {return _ruleBook;}

		BattleField* battleField() noexcept {return _battleField.get();}
		const BattleField* battleField() const noexcept {return _battleField.get();}

		EventSystem& eventSystem() noexcept {return _events;}
		const EventSystem& eventSystem() const noexcept {return _events;}

		UnitFactory& unitFactory() noexcept {return _unitFactory;}
		const UnitFactory& unitFactory() const noexcept {return _unitFactory;}

	};
}
