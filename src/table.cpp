#include "table.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "rule.h"
#include "grammar.h"
#include "automata.h"

using namespace std;

// ---- Global Variables --------------------------------------------------------------------

table_t table_global;

// ---- Implementation ----------------------------------------------------------------------

table_t table_make (map<string, set<string>>& first, map<string, set<string>>& follow) {

	map<string, action_t> base;

	for (auto state_iterator : automata_global.states)
	{
		state_t currentState = state_iterator;

		table_global[state_iterator.num] = base;

		// STATE IS ACCEPTANCE
		if (currentState.acc) {

			action_t act;

			act.type = ACC;	

			table_global[state_iterator.num][FINISH] = act;

			continue;
		}

		// SHIFTS and NORMAL TRANSITIONS
		for (unsigned int k = 0; k < currentState.transitions.size(); ++k)
		{	
			variable_t transitionVar = currentState.transitions[k].var;

			action_t act;

			act.type = (transitionVar.type == NON_TERM) ? NONE : SHIFT;

			act.stateDest = currentState.transitions[k].dest;

			table_global[state_iterator.num][transitionVar.id] = act;
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
						if (table_global[state_iterator.num].count(*fol)) {

							cerr << "Conflict: " << state_iterator.num << " " << currentState.rules[k].head.id << " " << *fol << endl;
						}

						table_global[state_iterator.num][*fol] = act;
					}
				}
			}
		}
	}

	return table_global;
}

void table_show () {

	cout << endl << endl << "------- Table -----------------------------------------------------------------------" << endl << endl;

	#define print_spaces(n) for (unsigned int count = 0; count < n; count++) {cout << " ";};

	unsigned short maxSize = 20, minSize = 20;

	vector<unsigned short> spaces;

	print_spaces(maxSize);

	for (unsigned int i = 0; i < grammar_global.variables.size(); ++i)
	{
		cout << " | ";
		cout << grammar_global.variables[i].id;

		short size = grammar_global.variables[i].id.length();


		if (size < minSize) {

			print_spaces((unsigned short)(minSize - size));
			spaces.push_back(minSize);
		}

		else {

			spaces.push_back(size);
		}
	}

	cout << " | " << endl << endl;

	for (table_t::iterator it = table_global.begin(); it != table_global.end(); it++)
	{
		string num = to_string(it->first);

		cout << "  " << num;

		print_spaces(maxSize - num.length() - 2);

		for (unsigned int i = 0; i < grammar_global.variables.size(); ++i) {
			
			cout << " | ";

			if ((it->second).find(grammar_global.variables[i].id) == (it->second).end()) {

				print_spaces(spaces[i]);
			}

			else {

				action_t act = it->second[grammar_global.variables[i].id];

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