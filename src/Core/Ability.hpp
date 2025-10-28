//
// Created by kirill on 10/28/2025.
//

#include <Core/Types.hpp>

namespace sw
{
	class IAbility
	{
	public:
		[[nodiscard]] virtual int32_t priority() const noexcept {return 0;}
		[[nodiscard]] virtual bool execute(Unit& ) = 0;
	};
}
