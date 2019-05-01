#ifndef TABLE
#define TABLE

#include <map>
#include <set>
#include <string>

#include "rule.h"

// ---- Defs ----------------------------------------------------------------------

typedef enum {NONE, SHIFT, REDUCE, ACC} ActionTypes;

struct Action {
	
	ActionTypes type;

	short stateDest;

	Rule reduceRule;
};

typedef std::map<short, std::map<std::string, Action>> Table;

// ---- Global Variables --------------------------------------------------------------------

// Variable containing the table produced
extern Table table_global;

// ---- Prototypes ----------------------------------------------------------------------

Table table_make (std::map<std::string, std::set<std::string>>&, std::map<std::string, std::set<std::string>>&);

void table_show ();

#endif