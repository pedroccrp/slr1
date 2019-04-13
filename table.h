#include <vector>
#include <map>

#include "state.h"

using namespace std;

#ifndef TABLE
#define TABLE
	
// ---- Defs ----------------------------------------------------------------------

short stateCount = 0;

typedef enum {NONE, SHIFT, REDUCE} act_types;

typedef struct action {
	
	act_types type;

	union {

		short noneNum;
		state_t* shiftDest;
		rule_t* reduceRule;
	};

} action_t;

typedef struct table {
	
	vector<state_t> states;

	map<state_t*, map<string, action_t>> relations;

} table_t;

// ---- Prototypes ----------------------------------------------------------------------

// ---- Implementation ----------------------------------------------------------------------

table_t generate_states (table_t& tab, state_t& fromState, vector<variable_t> variables) {

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
				
				}

				// else {

				// 	// Need to make a reduce
				// }

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

		for (unsigned int k = 0; k < tab.states.size(); ++k) {

			if (state_compare(tab.states[k], createdState)) {

				stateExists = true;
				
				transitionAux.dest = tab.states[k].num;
				
				break;
			}
		}

		if (!stateExists) {

			createdState.num = stateCount++;

			transitionAux.dest = createdState.num;

			state_complete(createdState, tab.states[0].rules);

			tab.states.push_back(createdState);

			tab = generate_states(tab, createdState, variables);
		}

		fromState.transitions.push_back(transitionAux);
	}

	return tab;
}

table_t table_make (grammar_t gram) {

	// Add S' and $ to the variables of the grammar
	gram.variables.push_back(variable_new(INIT_VAR, NON_TERM));
	gram.variables.push_back(variable_new(FINISH, TERM));

	table_t tab;

	stateCount = 0;

	// Make E0
	{
		state_t stateAux = state_new(stateCount++);

		stateAux = state_add_rule(stateAux, 
			rule_new(variable_new(INIT_VAR, NON_TERM), {variable_new(POINT, SPECIAL), gram.variables[0], variable_new(FINISH, NON_TERM)}));

		for (unsigned int i = 0; i < gram.rules.size(); ++i)
		{
			rule_t ruleAux = gram.rules[i];

			ruleAux.production.insert(ruleAux.production.begin(), variable_new(POINT, SPECIAL));

			stateAux = state_add_rule(stateAux, ruleAux);
		}

		tab.states.push_back(stateAux);
	}

	state_t stateAux = tab.states[0];

	generate_states(tab, stateAux, gram.variables);

	tab.states[0] = stateAux;

	return tab;
}

void table_show (table_t t) {

	for (unsigned int i = 0; i < t.states.size(); ++i)
	{
		state_show(t.states[i]);
	}
}

#endif	