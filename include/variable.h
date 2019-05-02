#ifndef VARIABLE
#define VARIABLE

#include <string>

// ---- Defs ----------------------------------------------------------------------

#define POINT "."
#define FINISH "$"
#define INIT_VAR "SS"

typedef enum {TERM, NON_TERM, SPECIAL} VariableTypes;

struct Variable {
	
	std::string id;
	VariableTypes type;

};

// ---- Prototypes ----------------------------------------------------------------------

Variable variable_new (std::string, VariableTypes);

#endif