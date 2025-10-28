//
// Created by kirill on 10/28/2025.
//

#include "Position.hpp"
#include "Unit.hpp"

using namespace sw;


bool GetDistance::tryExecute(GetDistance::ResultType& out, Position a, Position b)
{

	const auto delta =  Position {
		a.x > b.x ? a.x - b.x : b.x - a.x,
		a.y > b.y ? a.y - b.y : b.y - a.y
	};
	// ChebyshevDistanceRule
	out = delta.x > delta.y ? delta.x : delta.y;
	return true;
}

bool GetDistance::tryExecute(GetDistance::ResultType& out, const Unit& a,const  Unit& b, InteractionType)
{
	return tryExecute(out, a, b.position());
}

bool GetDistance::tryExecute(GetDistance::ResultType& out, const Unit& a, Position b, InteractionType interactionType)
{
	return tryExecute(out, a.position(), b);
}
