#include "state.h"

#include <iostream>
#include <vector>

#include "rule.h"
#include "grammar.h"
#include "variable.h"

using namespace std;

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

	for (auto defR = defaultRules.begin(); defR != defaultRules.end(); ++defR)
	{
		defR->production.insert(defR->production.begin(), variable_new(POINT, SPECIAL));
	}

	vector<rule_t> oldRules = s.rules, newRules, auxRules;

	do {

		newRules = rule_expand(oldRules, defaultRules);

		auxRules.clear();

		for (std::vector<rule_t>::iterator n = newRules.begin(); n != newRules.end(); ++n) {
			
			bool exists = false;

			for (std::vector<rule_t>::iterator o = s.rules.begin(); o != s.rules.end(); ++o) {

				if (rule_compare(*o, *n)) {

					exists = true;
					break;
				}
			}

			if (!exists) {

				auxRules.push_back(*n);
			}
		}

		oldRules = auxRules;

		s.rules.insert(s.rules.end(), auxRules.begin(), auxRules.end());
	
	} while (oldRules.size() > 0);

	return s;
}

void state_show (state_t s) {

	cout << "------------- "<< s.num << " ---------------------" << endl << endl;

	cout << "  Rules: " << endl << endl;

	for (unsigned int k = 0; k < s.rules.size(); ++k)
	{	
		cout << "    ";
		rule_show(s.rules[k]);
	}

	cout << endl;

	cout << "  Transitions: " << endl << endl;
	
	for (unsigned int k = 0; k < s.transitions.size(); ++k)
	{	
		cout << "    " << s.transitions[k].var.id << " " << s.transitions[k].dest << endl;
	}
	
	cout << endl;
	
	cout << "  Type: ";

	if (s.acc) {

		cout << "ACC" << endl << endl;
	}
	
	else if (s.hasReduction) {

		cout << "REDUCE" << endl << endl;
	}

	else {

		cout << endl << endl;
	}

}

bool state_order_rule (state_t s1, state_t s2) {

	return s1.num < s2.num;
}