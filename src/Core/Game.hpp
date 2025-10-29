//
// Created by kirill on 10/28/2025.
//

#include "IO/System/CommandParser.hpp"
#include <Core/BattleField.hpp>
#include <Core/EventSystem.hpp>
#include <Core/GameRule.hpp>
#include <Core/Unit.hpp>
#include <Core/Types.hpp>
#include <Core/UnitFactory.hpp>

namespace sw
{
	class Game
	{
		RuleBook _ruleBook;
		EventSystem _events;
		std::unique_ptr<BattleField> _battleField;
		UnitFactory _unitFactory;
		std::vector<UnitId> _toRemove;
		uint32_t _frameIndex = 0;
		std::vector<std::unique_ptr<UnitObject> > _units;
		std::unordered_map<UnitId, size_t> _idToIndex;
		bool _tickInProgress = false;
		std::vector<UnitObject*> _tickUnits; // stable indexable view for current tick
		io::CommandParser _parser;
	public:
		Game();
		~Game();

		void init();
		void update();

		uint32_t frameIndex() const noexcept {return _frameIndex;}

		RuleBook& ruleBook() noexcept {return _ruleBook;}
		const RuleBook& ruleBook() const noexcept {return _ruleBook;}

		BattleField* battleField() noexcept {return _battleField.get();}
		const BattleField* battleField() const noexcept {return _battleField.get();}

		EventSystem& eventSystem() noexcept {return _events;}
		const EventSystem& eventSystem() const noexcept {return _events;}

		UnitFactory& unitFactory() noexcept {return _unitFactory;}
		const UnitFactory& unitFactory() const noexcept {return _unitFactory;}

		const auto& units() const noexcept {return _units;}

		void createBattleField(Real w, Real h);

		Unit addUnit(std::unique_ptr<UnitObject>&& unit);

		Unit findUnit(UnitId id) const noexcept;
		void removeUnit(UnitId id);

		io::CommandParser& parser() noexcept {return _parser;}
		const io::CommandParser& parser() const noexcept {return _parser;}
private:

		// Index-based access during the current tick
		size_t tickUnitCount() const noexcept { return _tickInProgress ? _tickUnits.size() : _units.size(); }

		UnitObject* tickUnitAt(size_t index) const noexcept { return _tickInProgress ? _tickUnits[index] : _units[index].get(); }


		UnitObject* findUnitRaw(UnitId id) const noexcept;
		friend Unit;
		void rebuildIndex();

	};


	class AutoRegistrator
	{
	public:
		AutoRegistrator();
		virtual ~AutoRegistrator();
		virtual std::string name() const noexcept = 0;
		virtual void registerIn(Game& ) = 0;

		static void forEach(const std::function<void (AutoRegistrator&)>& callback);
	};

}
