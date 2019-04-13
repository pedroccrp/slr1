#include <vector>

#include "grammar.h"

using namespace std;

#ifndef STATE
#define STATE
	
// ---- Defs ----------------------------------------------------------------------


typedef struct transition transition_t;
typedef struct state state_t;

typedef struct transition
{
	variable_t var;

	short dest;
	
} transition_t;

typedef struct state
{
	short num;

	vector<rule_t> rules;

	vector<transition_t> transitions;

} state_t;

// ---- Prototypes ----------------------------------------------------------------------

transition_t transition_new (variable_t, short);

state_t state_new (short);
state_t state_add_rule (state_t, rule_t);
state_t state_add_transition (state_t, transition_t);
state_t state_complete (state_t&, vector<rule_t>);
void state_show (state_t);

// ---- Implementation ----------------------------------------------------------------------

transition_t transition_new (variable_t v, short d) {

	transition_t t;

	t.var = v;
	t.dest = d;

	return t;
}

state_t state_new (short num) {

	state_t s;

	s.num = num;

	return s;
}

state_t state_add_rule (state_t s, rule_t r) {

	s.rules.push_back(r);

	return s;
}

state_t state_add_transition (state_t s, transition_t t) {

	s.transitions.push_back(t);

	return s;
}

state_t state_complete (state_t& s, vector<rule_t> defaultRules) {

	vector<rule_t> oldRules = s.rules, newRules;

	while (newRules = rule_expand(oldRules, defaultRules), newRules.size() > 0) {

		oldRules = newRules;

		s.rules.insert(s.rules.end(), newRules.begin(), newRules.end());
	}

	return s;
}

bool state_compare (state_t s1, state_t s2) {

	for (unsigned int i = 0; i < s1.rules.size(); ++i)
	{
		for (unsigned int k = 0; k < s2.rules.size(); ++k) {

			if (!rule_compare(s1.rules[i], s2.rules[k])) {

				return false;
			}
		}
	}

	return true;
}

void state_show (state_t s) {

	cout << "------------- "<< s.num << " ---------------------" << endl;

	cout << "Rules: " << endl;

	for (unsigned int k = 0; k < s.rules.size(); ++k)
	{	
		cout << " ";
		rule_show(s.rules[k]);
	}

	cout << endl;

	cout << "Transitions: " << endl;
	
	for (unsigned int k = 0; k < s.transitions.size(); ++k)
	{	
		cout << " " << s.transitions[k].var.id << " " << s.transitions[k].dest << endl;

	}
	
	cout << endl;
}

#endif	