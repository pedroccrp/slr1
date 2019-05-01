#ifndef AUTOMATA
#define AUTOMATA

#include <vector>

#include "state.h"

// ---- Defs ----------------------------------------------------------------------

struct Automata {

	std::vector<State> states;

};

// ---- Global Variables --------------------------------------------------------------------

// Amount of states created
extern short state_count;

// Variable containing the automata produced
extern Automata automata_global;

// ---- Prototypes ----------------------------------------------------------------------

Automata automata_make ();
Automata automata_generate_states (State&);

void automata_show ();

#endif
