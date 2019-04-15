#include <vector>

#include "variable.h"

using namespace std;

#ifndef RULE
#define RULE
	
// ---- Defs ----------------------------------------------------------------------

typedef struct rule {
	
	variable_t head;
	vector<variable_t> production;

} rule_t;

// ---- Prototypes ----------------------------------------------------------------------

rule_t rule_new (variable_t, vector<variable_t>);
void rule_show (rule_t r);
bool rule_compare (rule_t, rule_t);

vector<variable_t> rules_first (variable_t, vector<rule_t>);  // First 1
vector<variable_t> rules_follow (variable_t, vector<rule_t>); // Follow 1

// ---- Implementation ----------------------------------------------------------------------

rule_t rule_new (variable_t head, vector<variable_t> production) {

	rule_t r;

	r.head = head;
	r.production = production;

	return r;
}

bool rule_compare (rule_t r1, rule_t r2) {

	if ((r1.head.id != r2.head.id) || r1.production.size() != r2.production.size()) {

		return false;
	}

	for (unsigned int i = 0; i < r1.production.size(); ++i)
	{
		if (r1.production[i].id != r2.production[i].id) {

			return false;
		}
	}

	return true;
}

void rule_show (rule_t r) {

	cout << r.head.id << " -> ";

	for (unsigned int i = 0; i < r.production.size(); ++i)
	{
		cout << r.production[i].id << " ";
	}

	cout << endl;
}

vector<rule_t> rule_expand (vector<rule_t> oldRules, vector<rule_t> defaultRules) {

	vector<rule_t> newRules;
	
	for (unsigned int i = 0; i < oldRules.size(); ++i)
	{
		for (unsigned int k = 0; k < oldRules[i].production.size(); ++k) {

			if (oldRules[i].production[k].id == POINT) {

				if (k + 1 < oldRules[i].production.size()) {

					if (oldRules[i].production[k + 1].type == NON_TERM) {

						string nonTerm = oldRules[i].production[k + 1].id;

						// Expand rule 
						{
							for (unsigned int j = 0; j < defaultRules.size(); ++j)
							{
								if (defaultRules[j].head.id == nonTerm) {

									bool ruleExists = false;

									for (unsigned int l = 0; l < newRules.size(); ++l)
									{
										if (rule_compare(defaultRules[j], newRules[l])) {

											ruleExists = true;
											break;
										}
									}

									if (!ruleExists) {

										newRules.push_back(defaultRules[j]);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return newRules;
}

vector<variable_t> rules_first (variable_t var, vector<rule_t> rules) {

	vector<variable_t> first;

	return first;
}

vector<variable_t> rules_follow (variable_t var, vector<rule_t> rules) {
		
	vector<variable_t> follow;

	return follow;
}

#endif	