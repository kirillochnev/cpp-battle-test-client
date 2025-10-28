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
		void onStart(Unit& owner) override;
		void onFinished(Unit& owner) override;
		void onUpdate(Unit& owner) override;
		void onTerminate(Unit& owner) override;
	};
}
