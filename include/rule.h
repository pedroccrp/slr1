#ifndef RULE
#define RULE

#include <map>
#include <set>
#include <string>
#include <vector>

#include "variable.h"
	
// ---- Defs ----------------------------------------------------------------------

typedef struct rule {
	
	variable_t head;
	std::vector<variable_t> production;

} rule_t;

// ---- Prototypes ----------------------------------------------------------------------

rule_t rule_new (variable_t, std::vector<variable_t>);

void rule_show (rule_t r);

bool rule_compare (rule_t, rule_t);

std::vector<rule_t> rule_expand (std::vector<rule_t>, std::vector<rule_t>);

void rules_generate_first_follow (std::vector<variable_t>, std::vector<rule_t>, std::map<std::string, std::set<std::string>>&, std::map<std::string, std::set<std::string>>&);

void rules_first (std::set<std::string>&, std::set<std::string>&, std::set<std::string>&, std::string, std::vector<rule_t>&);  // First 1
void rules_follow (std::set<std::string>&, std::set<std::string>&, std::set<std::string>&, std::string, std::vector<rule_t>&);  // First 1

void rules_find_first (std::set<std::string>&, std::set<std::string>&, std::map<std::string, std::set<std::string>>&, std::string, std::vector<rule_t>&);  // Follow 1

void first_follow_print (std::map<std::string, std::set<std::string>>, bool);

#endif	