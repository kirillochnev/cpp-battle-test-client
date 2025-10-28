//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

#include <random>

namespace sw
{
	class GetRandomNumber : public GameRule {
	protected:
		std::mt19937 _generator;
	public:
		using ResultType = Real;
		explicit GetRandomNumber(size_t seed = 42):
				_generator(seed)
		{

		}
		virtual bool tryExecute(ResultType& out, Real min, Real max)
		{
			std::uniform_int_distribution<Real> dist(min, max);
			out = dist(_generator);
			return true;
		}
	};
}
