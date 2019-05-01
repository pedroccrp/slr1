#ifndef RULE
#define RULE

#include <map>
#include <set>
#include <string>
#include <vector>

#include "variable.h"
	
// ---- Defs ----------------------------------------------------------------------

struct Rule {
	
	Variable head;
	std::vector<Variable> production;

};

// ---- Prototypes ----------------------------------------------------------------------

Rule rule_new (Variable, std::vector<Variable>);

void rule_show (Rule r);

bool rule_compare (Rule, Rule);

std::vector<Rule> rule_expand (std::vector<Rule>, std::vector<Rule>);

void rules_generate_first_follow (std::vector<Variable>, std::vector<Rule>, std::map<std::string, std::set<std::string>>&, std::map<std::string, std::set<std::string>>&);

void rules_first (std::set<std::string>&, std::set<std::string>&, std::set<std::string>&, std::string, std::vector<Rule>&);  // First 1
void rules_follow (std::set<std::string>&, std::set<std::string>&, std::set<std::string>&, std::string, std::vector<Rule>&);  // First 1

void rules_find_first (std::set<std::string>&, std::set<std::string>&, std::map<std::string, std::set<std::string>>&, std::string, std::vector<Rule>&);  // Follow 1

void first_follow_print (std::map<std::string, std::set<std::string>>, bool);

#endif	