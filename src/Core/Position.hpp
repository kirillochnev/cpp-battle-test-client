//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

namespace sw

{
		struct Position
		{
			Real x;
			Real y;
			auto operator<=>(const Position&) const = default;
			// to handle unsigned Real data type
		};

		class GetDistance : public GameRule
		{
		public:
			using ResultType = Real;
			virtual bool tryExecute(ResultType& out, Position a, Position b);
			virtual bool tryExecute(ResultType& out, const Unit& a, const Unit& b, InteractionType interactionType = InteractionType::kUnknown);
			virtual bool tryExecute(ResultType& out, const Unit& a, Position b, InteractionType interactionType = InteractionType::kMovement);
		};


}