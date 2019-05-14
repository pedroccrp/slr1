#ifndef GRAMMAR
#define GRAMMAR

#include <vector>
#include <string>

#include "rule.h"
#include "variable.h"

// ---- Defs ----------------------------------------------------------------------

enum GrammarStates {
    NON_TERMS = 0, 
    TERMS     = 1, 
    RULES     = 2
};

struct Grammar {
	
	std::vector<Variable> variables;
	std::vector<Rule> rules;

};

// ---- Global Variables --------------------------------------------------------------------

// Variable containing the grammar obtained
extern Grammar grammar_global;

// ---- Prototypes ----------------------------------------------------------------------

Grammar grammar_request ();

Variable grammar_find_variable (std::string);

void grammar_string_to_var (std::string, VariableTypes, Grammar&);

void grammar_show ();

#endif