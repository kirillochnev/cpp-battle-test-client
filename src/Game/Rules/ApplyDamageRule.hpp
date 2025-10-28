//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

namespace sw
{
    // Apply non-negative damage to target: modify HP, post events, schedule death
    class ApplyDamageRule : public GameRule
    {
    public:
        using ResultType = void;
        virtual bool tryExecute(Unit* source, Unit& target, Real damage);
    };
}
