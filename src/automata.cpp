#include "automata.h"

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#include "state.h"

using namespace std;

// ---- Global Variables --------------------------------------------------------------------

short state_count = 0;

automata_t automata_global;

// ---- Implementation ----------------------------------------------------------------------

automata_t automata_make () {

	// Add S' as the start non terminal
	grammar_global.variables.insert(grammar_global.variables.begin(), variable_new(INIT_VAR, NON_TERM));
	
	// Add $ as the finish terminal
	grammar_global.variables.push_back(variable_new(FINISH, TERM));

	state_t first_state = state_new(state_count++);

	// Make state 0
	{
		// Add the rule (SS . <Initial> $) to state 0
		first_state = state_add_rule(first_state, 
			rule_new(variable_new(INIT_VAR, NON_TERM), 
			{variable_new(POINT, SPECIAL), grammar_global.variables[1], variable_new(FINISH, NON_TERM)}));

		if (grammar_global.variables.size() < 2) {

			cerr << "Insufficient variables in grammar!" << endl;

			exit(1);
		}
		
		string initial_non_terminal = grammar_global.variables[1].id;
		
		// Find all the rules in the grammar that starts with the <Inital Non Terminal> and add to the first state (with a POINT before it)
		for (auto rule_iterator : grammar_global.rules) {

			if (rule_iterator.head.id == initial_non_terminal) {

				rule_t rule_aux = rule_iterator;

				rule_aux.production.insert(rule_aux.production.begin(), variable_new(POINT, SPECIAL));

				first_state = state_add_rule(first_state, rule_aux);
			}
		}
	}

	first_state = state_complete(first_state, grammar_global.rules);

	automata_global.states.push_back(first_state);

	automata_generate_states(first_state);

	automata_global.states[0] = first_state;

	sort(automata_global.states.begin(), automata_global.states.end(), state_order_rule);

	grammar_global.rules.push_back(rule_new(variable_new(INIT_VAR, NON_TERM), {grammar_global.variables[1], variable_new(FINISH, TERM)}));
	
	return automata_global;
}

automata_t automata_generate_states (state_t& fromState) {

	// Organizes rules by variable after point
	map<string, vector<rule_t>> separetedRules;

	for (auto rule_iterator : fromState.rules) {

		unsigned int production_index = 0;

		for (auto production_iterator : rule_iterator.production) {

			if (production_iterator.id == POINT) {

				if ((production_index + 1) < rule_iterator.production.size()) {

					if (rule_iterator.production[production_index + 1].id != FINISH) {

						rule_iterator.production[production_index] = rule_iterator.production[production_index + 1];

						rule_iterator.production[production_index + 1].id = POINT;
						rule_iterator.production[production_index + 1].type = SPECIAL;

						separetedRules[rule_iterator.production[production_index].id].push_back(rule_iterator);
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

			production_index++;
		}
	}

	// For each possible transition, make a new state and add transition to it
	for (auto rule_iterator : separetedRules) {

		state_t createdState;

		for (unsigned int k = 0; k < rule_iterator.second.size(); ++k) {

			createdState = state_add_rule(createdState, rule_iterator.second[k]);
		}

		bool stateExists = false;

		transition_t transition_aux;

		for (auto variable_iterator : grammar_global.variables) {

			if (rule_iterator.first == variable_iterator.id) {
				
				transition_aux.var = variable_iterator;
				break;
			}
		}

		state_complete(createdState, grammar_global.rules);

		for (auto state_iterator : automata_global.states) {

			if (state_iterator == createdState) {

				stateExists = true;
				
				transition_aux.dest = state_iterator.num;
				
				break;
			}
		}

		if (!stateExists) {

			createdState.num = state_count++;

			transition_aux.dest = createdState.num;

			automata_global.states.push_back(createdState);

			int index = state_count - 1;

			automata_generate_states(createdState);

			automata_global.states[index] = createdState;
		}

		else {

			for (auto state_iterator : automata_global.states) {

				if (state_iterator == createdState) {

					transition_aux.dest = state_iterator.num;
					break;
				}
			}
		}

		fromState.transitions.push_back(transition_aux);
	}

	return automata_global;
}

void automata_show () {

	cout << endl << endl << "------- Automata --------------------------------------------------------------------" << endl << endl;

	for (auto state_iterator : automata_global.states) {

		state_show(state_iterator);
	}
}
