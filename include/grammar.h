#ifndef GRAMMAR
#define GRAMMAR

#include <vector>
#include <string>

#include "rule.h"
#include "variable.h"

// ---- Defs ----------------------------------------------------------------------

typedef struct grammar {
	
	std::vector<variable> variables;
	std::vector<rule> rules;

} grammar_t;

// ---- Global Variables --------------------------------------------------------------------

// Variable containing the grammar obtained
extern grammar_t grammar_global;

// ---- Prototypes ----------------------------------------------------------------------

grammar_t grammar_request ();

variable_t grammar_find_variable (std::string);

void grammar_string_to_var (std::string, var_types, grammar_t&);

void grammar_show ();

#endif