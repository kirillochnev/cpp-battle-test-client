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

		void update();
		void terminate();

	protected:
		bool _inProgress = false;
		virtual void onStart() = 0;
		virtual void onFinished() = 0;
		virtual void onUpdate() = 0;
		virtual void onTerminate() = 0;
	};
}
