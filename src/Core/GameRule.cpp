//
// Created by kirill on 10/28/2025.
//

#include "GameRule.hpp"

#include <algorithm>

void sw::RuleBook::sortRules()
{
	std::stable_sort(_rules.begin(), _rules.end(), [](const auto& a, const auto& b){
 		return a->priority() > b->priority();
	});
}

sw::RuleBook::RuleBook(sw::Game& game):
	_game(game)
{

}
