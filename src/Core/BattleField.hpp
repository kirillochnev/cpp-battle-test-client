//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <vector>

namespace sw
{
	class BattleField : Uncopiable
	{
		const Real _width;
		const Real _height;
		std::vector<bool> _occupancy;
	public:
		explicit BattleField(Real w, Real h);
		[[nodiscard]] Real width() const noexcept;
		[[nodiscard]] Real height() const noexcept;

		[[nodiscard]] bool isCeilValid(Real x, Real y) const noexcept;
		void blockCeil(Real x, Real y);
		void releaseCeil(Real x, Real y);
	private:
		[[nodiscard]] size_t ceilIndex(Real x, Real y) const noexcept;
	};
}
