#include <map>
#include <vector>
#include <algorithm>

#include "state.h"

using namespace std;

#ifndef AUTOMATA
#define AUTOMATA
	
// ---- Defs ----------------------------------------------------------------------

short stateCount = 0;

vector<variable_t> variables;

typedef struct automata {
	
	vector<state_t> states;

} automata_t;

// ---- Prototypes ----------------------------------------------------------------------

automata_t generate_states (automata_t&, state_t&);
automata_t automata_make (grammar_t&);

void automata_show (automata_t);

state_t automata_get_state_from_num (automata_t aut, unsigned short num);

// ---- Implementation ----------------------------------------------------------------------

automata_t generate_states (automata_t& aut, state_t& fromState) {

	// Organizes rules by variable after point
	map<string, vector<rule_t>> separetedRules;

	for (unsigned int i = 0; i < fromState.rules.size(); ++i)
	{
		for (unsigned int k = 0; k < fromState.rules[i].production.size(); ++k)
		{
			if (fromState.rules[i].production[k].id == POINT) {

				if ((k + 1) < fromState.rules[i].production.size()) {

					rule_t ruleAux = fromState.rules[i];

					if (ruleAux.production[k + 1].id != FINISH) {

						ruleAux.production[k] = ruleAux.production[k + 1];

						ruleAux.production[k + 1].id = POINT;
						ruleAux.production[k + 1].type = SPECIAL;


						separetedRules[fromState.rules[i].production[k + 1].id].push_back(ruleAux);
					}

					else {

						fromState.acc = true;
					}
				}

				else {

					fromState.hasReduction = true;
				}

				break;
			}
		}
	}

	// For each possible transition, make a new state and add transition to it
	for (std::map<string, vector<rule_t>>::iterator it = separetedRules.begin(); it != separetedRules.end(); ++it)
	{
		state_t createdState;

		for (unsigned int k = 0; k < it->second.size(); ++k)
		{
			createdState = state_add_rule(createdState, it->second[k]);
		}

		bool stateExists = false;

		transition_t transitionAux;

		for (unsigned int i = 0; i < variables.size(); ++i)
		{
			if (it->first == variables[i].id) {
				
				transitionAux.var = variables[i];
				break;
			}
		}

		for (unsigned int k = 0; k < aut.states.size(); ++k) {

			if (state_compare(aut.states[k], createdState)) {

				stateExists = true;
				
				transitionAux.dest = aut.states[k].num;
				
				break;
			}
		}

		if (!stateExists) {

			createdState.num = stateCount++;

			transitionAux.dest = createdState.num;

			state_complete(createdState, aut.states[0].rules);

			aut.states.push_back(createdState);

			int index = stateCount - 1;

			generate_states(aut, createdState);

			aut.states[index] = createdState;
		}

		else {

			for (unsigned int l = 0; l < aut.states.size(); ++l)
			{
				if (state_compare(aut.states[l], createdState)) {

					transitionAux.dest = aut.states[l].num;

					break;
				}
			}
		}

		fromState.transitions.push_back(transitionAux);
	}

	return aut;
}

automata_t automata_make (grammar_t& gram) {

	// Add S' and $ to the variables of the grammar
	gram.variables.insert(gram.variables.begin(), variable_new(INIT_VAR, NON_TERM));
	gram.variables.push_back(variable_new(FINISH, TERM));


	automata_t aut;

	stateCount = 0;

	// Make E0
	{
		state_t stateAux = state_new(stateCount++);

		stateAux = state_add_rule(stateAux, 
			rule_new(variable_new(INIT_VAR, NON_TERM), {variable_new(POINT, SPECIAL), gram.variables[1], variable_new(FINISH, NON_TERM)}));

		for (unsigned int i = 0; i < gram.rules.size(); ++i)
		{
			rule_t ruleAux = gram.rules[i];

			ruleAux.production.insert(ruleAux.production.begin(), variable_new(POINT, SPECIAL));

			stateAux = state_add_rule(stateAux, ruleAux);
		}

		aut.states.push_back(stateAux);
	}

	state_t stateAux = aut.states[0];

	variables = gram.variables;

	generate_states(aut, stateAux);

	aut.states[0] = stateAux;

	sort(aut.states.begin(), aut.states.end(), state_order_rule);

	gram.rules.push_back(rule_new(variable_new(INIT_VAR, NON_TERM), {gram.variables[1], variable_new(FINISH, TERM)}));
	
	return aut;
}

void automata_show (automata_t aut) {

	for (unsigned int i = 0; i < aut.states.size(); ++i)
	{
		state_show(aut.states[i]);
	}
}

state_t automata_get_state_from_num (automata_t aut, unsigned short num) {
	
	if (num >= aut.states.size()) {

		cout << "Num is greater than number of states!" << endl;
		exit(1);
	}

	return aut.states[num];
}
#endif	