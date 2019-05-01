#ifndef VARIABLE
#define VARIABLE

#include <string>

// ---- Defs ----------------------------------------------------------------------

#define POINT "."
#define FINISH "$"
#define INIT_VAR "SS"

typedef enum {TERM, NON_TERM, SPECIAL} var_types;

struct Variable {
	
	std::string id;
	var_types type;

};

// ---- Prototypes ----------------------------------------------------------------------

Variable variable_new (std::string, var_types);

#endif