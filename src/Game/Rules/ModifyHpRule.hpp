//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

namespace sw
{
    // Adjust unit HP by delta (positive heals, negative damages)
    class ModifyHpRule : public GameRule
    {
    public:
        using ResultType = void;
        virtual bool tryExecute(Unit& unit, Real deltaHp);
    };
}
