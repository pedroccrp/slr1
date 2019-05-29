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

// For each state the format of the print will be:
// <state_num> <state_num_actions>
// <variable_id> <action_type> <stack_clear_number> <state_destination> <reduce_rule_head>
// .............................
// <blank line>
//
// action_type = none = 0,  shift = 1, reduce = 2 (STRING)
// stack_clear_number - amount of data to reduce from the stack (in pairs) (STRING)
// state_destination - the state that will be inserted on the stack (STRING)
void TableParsedPrint ();

#endif