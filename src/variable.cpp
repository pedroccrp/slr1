#include "variable.h"

#include <string>

using namespace std;

// ---- Implementation ----------------------------------------------------------------------

Variable variable_new (string id, var_types type) {

	Variable v;

	v.id = id;
	v.type = type;

	return v;
}
