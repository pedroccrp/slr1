#include <iostream>
#include <vector>
#include <string>

#include "rule.h"

using namespace std;

#ifndef GRAMMAR
#define GRAMMAR

// ---- Defs ----------------------------------------------------------------------

typedef struct grammar {
	
	vector<variable> variables;
	vector<rule> rules;

} grammar_t;

// ---- Prototypes ----------------------------------------------------------------------

grammar_t grammar_request ();

variable_t grammar_find_variable (grammar, string);

void grammar_string_to_var (string, var_types, grammar_t&);

// ---- Implementation ----------------------------------------------------------------------

grammar_t grammar_request () {

	grammar_t g;

	short i = 0;

	string aux;

	while (i++, getline(cin, aux)) {

		// Non-terminals
		if (i == 1) {
			
			grammar_string_to_var(aux, NON_TERM, g);	
		}

		// Terminals
		else if (i == 2) {

			grammar_string_to_var(aux, TERM, g);
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

						r.head = grammar_find_variable(g, token);
					}

					else {

						r.production.push_back(grammar_find_variable(g, token));
					}

					token = "";
				}

				else {

					token += aux[j];
				}
			}

			if (token != "") {

				r.production.push_back(grammar_find_variable(g, token));
			}

			g.rules.push_back(r);
		}
	}	

	return g;
}

void grammar_string_to_var (string str, var_types type, grammar_t& g) {

	variable_t v = variable_new("", type);

	string token = "";

	for (unsigned int j = 0; j < str.length(); ++j)
	{
		if (str[j] == ' ') {

			v.id = token;
			g.variables.push_back(v);
			
			token = "";
		}

		else {

			token += str[j];
		}
	}

	if (token != "") {

		v.id = token;
		g.variables.push_back(v);
	}
}

variable_t grammar_find_variable (grammar g, string id) {

	for (unsigned int i = 0; i < g.variables.size(); ++i)
	{
		if (g.variables[i].id == id) {

			return g.variables[i];
		}
	}

	// Should never return this :p
	return variable_new("", TERM);
}

void grammar_show (grammar g) {

	cout << "Variables:" << endl << endl;

	for (unsigned int i = 0; i < g.variables.size(); ++i)
	{

		cout << " ID: " << g.variables[i].id << endl; 
		cout << " Tp: " << g.variables[i].type << endl; 
		cout << endl;
	}

	cout << "Rules:" << endl << endl;

	for (unsigned int i = 0; i < g.rules.size(); ++i)
	{
		rule_show(g.rules[i]);
	}
}

#endif