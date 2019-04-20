#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "grammar.h"
#include "automata.h"

#ifndef TABLE
#define TABLE

// ---- Defs ----------------------------------------------------------------------

typedef enum {NONE, SHIFT, REDUCE, ACC} act_types;

typedef struct action {
	
	act_types type;

	short stateDest;

	rule_t reduceRule;

} action_t;

typedef map<short, map<string, action_t>> table_t;

// ---- Prototypes ----------------------------------------------------------------------

table_t table_make (automata_t, grammar_t, map<string, set<string>>&, map<string, set<string>>&);

void table_show (table_t, grammar_t);

// ---- Implementation ----------------------------------------------------------------------

table_t table_make (automata_t aut, grammar_t gram, map<string, set<string>>& first, map<string, set<string>>& follow) {

	table_t tab;

	vector<state_t> states = aut.states;

	map<string, action_t> base;

	for (unsigned short i = 0; i < states.size(); ++i)
	{
		state_t currentState = states[i];

		tab[i] = base;

		// STATE IS ACCEPTANCE
		if (currentState.acc) {

			action_t act;

			act.type = ACC;	

			tab[i][FINISH] = act;

			continue;
		}

		// SHIFTS and NORMAL TRANSITIONS
		for (unsigned int k = 0; k < currentState.transitions.size(); ++k)
		{	
			variable_t transitionVar = currentState.transitions[k].var;

			action_t act;

			act.type = (transitionVar.type == NON_TERM) ? NONE : SHIFT;

			act.stateDest = currentState.transitions[k].dest;

			tab[i][transitionVar.id] = act;
		}

		// REDUCES
		if (currentState.hasReduction) {

			for (unsigned int k = 0; k < currentState.rules.size(); ++k) {

				vector<variable_t> prod = currentState.rules[k].production;

				if (prod[prod.size() - 1].id == POINT) {

					action_t act;
					
					act.type = REDUCE;

					act.reduceRule = currentState.rules[k];
					act.reduceRule.production.pop_back();

					for (auto fol = follow[currentState.rules[k].head.id].begin(); fol != follow[currentState.rules[k].head.id].end(); ++fol)
					{
						if (tab[i].count(*fol)) {

							cerr << "Conflict: " << i << " " << currentState.rules[k].head.id << " " << *fol << endl;

							// exit(1);
						}

						tab[i][*fol] = act;
					}
				}
			}
		}
	}

	return tab;
}

void table_show (table_t tab, grammar_t gram) {

	cout << endl << endl << "------- Table -----------------------------------------------------------------------" << endl << endl;

	#define print_spaces(n) for (unsigned int count = 0; count < n; count++) {cout << " ";};

	unsigned short maxSize = 20, minSize = 20;

	vector<unsigned short> spaces;

	print_spaces(maxSize);

	for (unsigned int i = 0; i < gram.variables.size(); ++i)
	{
		cout << " | ";
		cout << gram.variables[i].id;

		short size = gram.variables[i].id.length();


		if (size < minSize) {

			print_spaces((unsigned short)(minSize - size));
			spaces.push_back(minSize);
		}

		else {

			spaces.push_back(size);
		}
	}

	cout << " | " << endl << endl;

	for (table_t::iterator it = tab.begin(); it != tab.end(); it++)
	{
		string num = to_string(it->first);

		cout << "  " << num;

		print_spaces(maxSize - num.length() - 2);

		for (unsigned int i = 0; i < gram.variables.size(); ++i) {
			
			cout << " | ";

			if ((it->second).find(gram.variables[i].id) == (it->second).end()) {

				print_spaces(spaces[i]);
			}

			else {

				action_t act = it->second[gram.variables[i].id];

				if (act.type == NONE) {

					string dest = to_string(act.stateDest);

					cout << dest;

					print_spaces(spaces[i] - dest.length());
				}

				else if (act.type == SHIFT) {

					string dest = to_string(act.stateDest);

					cout << "s" << dest;

					print_spaces(spaces[i] - dest.length() - 1);

				}

				else if (act.type == ACC) {

					cout << "ACC";

					print_spaces((unsigned int)(spaces[i] - 3));
				}

				else {

					vector<variable_t> prod = act.reduceRule.production;

					cout << "r" << " " << prod.size() << " " << act.reduceRule.head.id; 

					print_spaces(spaces[i] - to_string(prod.size()).length() - act.reduceRule.head.id.length() - 3);	
				}
			}
		}


		cout << " | ";
		cout << endl << endl;
	}
}

#endif