#ifndef STATE
#define STATE
	
#include <vector>

#include "rule.h"
#include "grammar.h"
#include "variable.h"

// ---- Defs ----------------------------------------------------------------------

struct Transition {

	Variable var;

	short dest;
	
};

struct State {

	short num;

	std::vector<Rule> rules;
	std::vector<Transition> transitions;

	bool acc = false;
	bool hasReduction = false;

	inline bool operator == (State comparing_state) {

		if (rules.size() != comparing_state.rules.size()) {

			return false;
		}

		for (unsigned int i = 0; i < rules.size(); ++i) {

			if (!rule_compare(rules[i], comparing_state.rules[i])) {

				return false;
			}
		}

		return true;
	}

};

// ---- Prototypes ----------------------------------------------------------------------

Transition transition_new (Variable, short);

State state_new (short);
State state_add_rule (State, Rule);
State state_add_transition (State, Transition);
State state_complete (State&, std::vector<Rule>);
void state_show (State);

bool state_order_rule (State, State);

#endif	