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

	automata_t aut = automata_make(gram);

	// automata_show(aut);

	// automata_get_state_from_num(aut, 1);

	table_t tab = table_make(aut, gram);

	table_show(tab, gram);

	return 0;
}