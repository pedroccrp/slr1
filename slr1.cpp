#include <iostream>

#include "grammar.h"
#include "state.h"
#include "automata.h"
#include "table.h"

using namespace std;

int main(int argc, char const *argv[])
{	
	// --------- Grammar --------------------------------------
	
	grammar_t gram = grammar_request();

	grammar_show(gram);

	// --------- Automata --------------------------------------
	
	automata_t aut = automata_make(gram);

	automata_show(aut);

	// --------- First Follow ----------------------------------
	
	map<string, set<string>> first, follow;

	rules_generate_first_follow(gram.variables, gram.rules, first, follow);

	first_follow_print(first, true);
	first_follow_print(follow, false);

	// --------- Table -----------------------------------------
	
	table_t tab = table_make(aut, gram, first, follow);

	table_show(tab, gram);

	return 0;
}