#ifndef AUTOMATA
#define AUTOMATA
	
#include <vector>

#include "state.h"

// ---- Defs ----------------------------------------------------------------------

typedef struct automata {
	
	std::vector<state_t> states;

} automata_t;

// ---- Global Variables --------------------------------------------------------------------

// Amount of states created
extern short state_count;

// Variable containing the automata produced 
extern automata_t automata_global;

// ---- Prototypes ----------------------------------------------------------------------

automata_t automata_make ();
automata_t automata_generate_states (state_t&);

void automata_show ();

#endif	