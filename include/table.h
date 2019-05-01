#ifndef TABLE
#define TABLE

#include <map>
#include <set>
#include <string>

#include "rule.h"

// ---- Defs ----------------------------------------------------------------------

typedef enum {NONE, SHIFT, REDUCE, ACC} act_types;

typedef struct action {
	
	act_types type;

	short stateDest;

	rule_t reduceRule;

} action_t;

typedef std::map<short, std::map<std::string, action_t>> table_t;

// ---- Global Variables --------------------------------------------------------------------

// Variable containing the table produced
extern table_t table_global;

// ---- Prototypes ----------------------------------------------------------------------

table_t table_make (std::map<std::string, std::set<std::string>>&, std::map<std::string, std::set<std::string>>&);

void table_show ();

#endif