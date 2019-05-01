#include "grammar.h"

#include <iostream>
#include <vector>
#include <string>

#include "variable.h"
#include "rule.h"

using namespace std;

// ---- Global Variables --------------------------------------------------------------------

grammar_t grammar_global;

// ---- Implementation ----------------------------------------------------------------------

grammar_t grammar_request () {

	short i = 0;

	string aux;

	while (i++, getline(cin, aux)) {

		if (aux == "") {

			continue;
		}

		// Non-terminals
		if (i == 1) {
			
			grammar_string_to_var(aux, NON_TERM, grammar_global);	
		}

		// Terminals
		else if (i == 2) {

			grammar_string_to_var(aux, TERM, grammar_global);
		}

		// Rules (Head + Production)
		else {

			string token = "";

			bool gotHead = false;

			rule_t r;

			for (unsigned int j = 0; j < aux.length(); ++j)
			{
				if (aux[j] == ' ') {

					if (!gotHead) {

						gotHead = true;

						r.head = grammar_find_variable(token);
					}

					else {

						r.production.push_back(grammar_find_variable(token));
					}

					token = "";
				}

				else {

					token += aux[j];
				}
			}

			if (token != "") {

				r.production.push_back(grammar_find_variable(token));
			}

			grammar_global.rules.push_back(r);
		}
	}	

	return grammar_global;
}

void grammar_string_to_var (string str, var_types type, grammar_t& grammar_global) {

	variable_t v = variable_new("", type);

	string token = "";

	for (unsigned int j = 0; j < str.length(); ++j)
	{
		if (str[j] == ' ') {

			if (token != "") {

				v.id = token;
				grammar_global.variables.push_back(v);
				
				token = "";
			}
		}

		else {

			token += str[j];
		}
	}

	if (token != "") {

		v.id = token;
		grammar_global.variables.push_back(v);
	}
}

variable_t grammar_find_variable (string id) {

	for (unsigned int i = 0; i < grammar_global.variables.size(); ++i)
	{
		if (grammar_global.variables[i].id == id) {

			return grammar_global.variables[i];
		}
	}

	// Should never return this :p
	return variable_new("", TERM);
}

void grammar_show () {


	cout << endl << endl << "------- Grammar ----------------------------------------------------------------------" << endl << endl;

	cout << "  Variables:" << endl << endl;

	for (unsigned int i = 0; i < grammar_global.variables.size(); ++i)
	{

		cout << "    ID: " << grammar_global.variables[i].id << endl; 
		cout << "    Tp: " << ((grammar_global.variables[i].type == NON_TERM) ? "Non-Terminal" : "Terminal") << endl; 
		cout << endl;
	}

	cout << " Rules:" << endl << endl;

	for (unsigned int i = 0; i < grammar_global.rules.size(); ++i)
	{
		cout << "    ";

		rule_show(grammar_global.rules[i]);
	}
}