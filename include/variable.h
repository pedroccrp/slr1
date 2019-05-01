#ifndef VARIABLE
#define VARIABLE

#include <string>

// ---- Defs ----------------------------------------------------------------------

#define POINT "."
#define FINISH "$"
#define INIT_VAR "SS"

typedef enum {TERM, NON_TERM, SPECIAL} var_types;

typedef struct variable {
	
	std::string id;
	var_types type;

} variable_t;

// ---- Prototypes ----------------------------------------------------------------------

variable_t variable_new (std::string, var_types);

#endif