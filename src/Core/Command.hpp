//
// Created by kirill on 10/28/2025.
//

#include <Core/Types.hpp>

namespace sw
{
	class ICommand
	{
	public:
		[[nodiscard]] virtual bool isInProgress() const noexcept {
			return _inProgress;
		}

		void start(UnitObject& owner);
		void update(UnitObject& owner);
		void terminate(UnitObject& owner);

	protected:
		bool _inProgress = false;
		virtual void onStart(UnitObject& owner) = 0;
		virtual void onFinished(UnitObject& owner) = 0;
		virtual void onUpdate(UnitObject& owner) = 0;
		virtual void onTerminate(UnitObject& owner) = 0;
	};
}
