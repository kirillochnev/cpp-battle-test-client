//
// Created by kirill on 10/28/2025.
//
#pragma once

#include <Core/Types.hpp>
#include <map>

namespace sw
{
	class AttributeOwner
	{
	public:
		virtual Real getAttribute(AttributeType type) const noexcept;
		virtual void setAttribute(AttributeType type, Real value) noexcept;
		virtual void removeAttribute(AttributeType type) noexcept;

	private:
		std::map<AttributeType, Real > _attributes;

	};

}
