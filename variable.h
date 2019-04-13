#ifndef VARIABLE
#define VARIABLE

using namespace std;

// ---- Defs ----------------------------------------------------------------------

#define POINT "@"
#define FINISH "$"
#define INIT_VAR "SS"

typedef enum {TERM, NON_TERM, SPECIAL} var_types;

typedef struct variable {
	
	string id;
	var_types type;

} variable_t;

// ---- Prototypes ----------------------------------------------------------------------

variable_t variable_new (string, var_types);

// ---- Implementation ----------------------------------------------------------------------

variable_t variable_new (string id, var_types type) {

	variable_t v;

	v.id = id;
	v.type = type;

	return v;
}

#endif