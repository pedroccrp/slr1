#include "state.h"

#include <iostream>
#include <vector>

#include "rule.h"
#include "grammar.h"
#include "variable.h"

using namespace std;

// ---- Implementation ----------------------------------------------------------------------

Transition transition_new (Variable v, short d) {

	Transition t;

	t.var = v;
	t.dest = d;

	return t;
}

State state_new (short num) {

	State s;

	s.num = num;

	return s;
}

State state_add_rule (State s, Rule r) {

	s.rules.push_back(r);

	return s;
}

State state_add_transition (State s, Transition t) {

	s.transitions.push_back(t);

	return s;
}

State state_complete (State& s, vector<Rule> defaultRules) {

	for (auto defR = defaultRules.begin(); defR != defaultRules.end(); ++defR)
	{
		defR->production.insert(defR->production.begin(), variable_new(POINT, SPECIAL));
	}

	vector<Rule> oldRules = s.rules, newRules, auxRules;

	do {

		newRules = rule_expand(oldRules, defaultRules);

		auxRules.clear();

		for (std::vector<Rule>::iterator n = newRules.begin(); n != newRules.end(); ++n) {
			
			bool exists = false;

			for (std::vector<Rule>::iterator o = s.rules.begin(); o != s.rules.end(); ++o) {

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

void state_show (State s) {

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

bool state_order_rule (State s1, State s2) {

	return s1.num < s2.num;
}