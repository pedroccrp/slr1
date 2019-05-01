#include <iostream>

#include "grammar.h"
#include "state.h"
#include "automata.h"
#include "table.h"

using namespace std;

int main(int argc, char const *argv[])
{	
	// --------- Grammar --------------------------------------
	
	grammar_request();

	grammar_show();

	// --------- Automata --------------------------------------
	
	automata_make();

	automata_show();

	// --------- First Follow ----------------------------------
	
	map<string, set<string>> first, follow;

	rules_generate_first_follow(grammar_global.variables, grammar_global.rules, first, follow);

	first_follow_print(first, true);
	first_follow_print(follow, false);

	// --------- Table -----------------------------------------
	
	table_t tab = table_make(first, follow);

	table_show();

	return 0;
}