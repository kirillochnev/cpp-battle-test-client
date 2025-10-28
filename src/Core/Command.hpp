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

		void start(Unit& owner);
		void update(Unit& owner);
		void terminate(Unit& owner);

	protected:
		bool _inProgress = false;
		virtual void onStart(Unit& owner) = 0;
		virtual void onFinished(Unit& owner) = 0;
		virtual void onUpdate(Unit& owner) = 0;
		virtual void onTerminate(Unit& owner) = 0;
	};
}
