#include "variable.h"

#include <string>

using namespace std;

// ---- Implementation ----------------------------------------------------------------------

variable_t variable_new (string id, var_types type) {

	variable_t v;

	v.id = id;
	v.type = type;

	return v;
}
