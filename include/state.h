#ifndef STATE
#define STATE
	
#include <vector>

#include "rule.h"
#include "grammar.h"
#include "variable.h"

// ---- Defs ----------------------------------------------------------------------

typedef struct state state_t;

typedef struct transition {

	variable_t var;

	short dest;
	
} transition_t;

typedef struct state {

	short num;

	std::vector<rule_t> rules;
	std::vector<transition_t> transitions;

	bool acc = false;
	bool hasReduction = false;

	inline bool operator == (state_t comparing_state) {

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

} state_t;

// ---- Prototypes ----------------------------------------------------------------------

transition_t transition_new (variable_t, short);

state_t state_new (short);
state_t state_add_rule (state_t, rule_t);
state_t state_add_transition (state_t, transition_t);
state_t state_complete (state_t&, std::vector<rule_t>);
void state_show (state_t);

bool state_order_rule (state_t, state_t);

#endif	