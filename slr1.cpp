#include <iostream>

#include "grammar.h"
#include "state.h"
#include "table.h"

using namespace std;

int main(int argc, char const *argv[])
{
	grammar_t gram = grammar_request();

	// grammar_show(gram);

	table_t tab = table_make(gram);

	table_show(tab);

	return 0;
}