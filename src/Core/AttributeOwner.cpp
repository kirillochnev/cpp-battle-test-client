//
// Created by kirill on 10/28/2025.
//

#include "AttributeOwner.hpp"

using namespace sw;

Real AttributeOwner::getAttribute(AttributeType type) const noexcept
{
	auto it = _attributes.find(type);
	if (it == _attributes.end())
	{
		return 0;
	}
	return it->second;
}

void AttributeOwner::setAttribute(AttributeType type, Real value) noexcept
{
	_attributes[type] = value;
}

void AttributeOwner::removeAttribute(AttributeType type) noexcept
{
	_attributes.erase(type);
}
