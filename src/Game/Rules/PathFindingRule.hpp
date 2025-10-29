//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>
#include <vector>

namespace sw
{
	class PathFindingRule : public GameRule
	{
	public:
		using ResultType = std::vector<Position>;
		virtual bool tryExecute(ResultType& path, Game&, Position from, Position to,
								bool ignoreCollision, Unit optionalUnit);
	};

}