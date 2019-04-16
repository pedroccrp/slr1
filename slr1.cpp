#include <iostream>

#include "grammar.h"
#include "state.h"
#include "automata.h"
#include "table.h"

using namespace std;

int main(int argc, char const *argv[])
{
	grammar_t gram = grammar_request();

	// grammar_show(gram);

	map<string, set<string>> first, follow;

	rules_generate_first_follow (gram.variables, gram.rules, first, follow);

	cout << "-----------------------" << endl;
	cout << "First" << endl;
	first_follow_print(first);
	cout << "-----------------------" << endl;
	cout << "Follow" << endl;
	first_follow_print(follow);

	automata_t aut = automata_make(gram);

	// automata_show(aut);

	// automata_get_state_from_num(aut, 1);

	table_t tab = table_make(aut, gram);

	// table_show(tab, gram);

	return 0;
}