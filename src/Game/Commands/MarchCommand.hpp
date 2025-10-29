//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Command.hpp>

namespace sw
{
	class MarchCommand : public ICommand
	{
		Real _targetX;
		Real _targetY;
	public:
		MarchCommand(Real x, Real y);
	protected:
		void onStart(UnitObject& owner) override;
		void onFinished(UnitObject& owner) override;
		void onUpdate(UnitObject& owner) override;
		void onTerminate(UnitObject& owner) override;
	};
}
