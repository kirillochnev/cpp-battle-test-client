//
// Created by kirill on 10/28/2025.
//

#include "BattleField.hpp"

using namespace sw;


BattleField::BattleField(Real w, Real h):
	_width(w),
	_height(h)
{
	_occupancy.resize(w * h, false);
}


Real BattleField::width() const noexcept
{
	return _width;
}

Real BattleField::height() const noexcept
{
	return _height;
}

bool BattleField::isCeilValid(Real x, Real y) const noexcept
{
	return x >= 0 && y >= 0 && x < _width && y < _height;
}

void BattleField::blockCeil(Real x, Real y)
{
	if (isCeilValid(x, y))
	{
		_occupancy[ceilIndex(x, y)] = true;
	}
}

void BattleField::releaseCeil(Real x, Real y)
{
	if (isCeilValid(x, y))
	{
		_occupancy[ceilIndex(x, y)] = false;
	}
}

size_t BattleField::ceilIndex(Real x, Real y) const noexcept
{
	return x + y * _width;
}
