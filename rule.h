#include <vector>
#include <set>
#include <map>

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

void rules_first (set<string>&, set<string>&, set<string>&, string, vector<rule_t>&);  // First 1
void rules_follow (set<string>&, set<string>&, set<string>&, string, vector<rule_t>&);  // First 1
void rules_find_first (set<string>&, map<string, set<string>>&, string, vector<rule_t>&);  // Follow 1

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

void rules_generate_first_follow (vector<variable_t> vars, vector<rule_t> rules, map<string, set<string>>& first, map<string, set<string>>& follow) {

	for (auto it = vars.begin(); it != vars.end(); ++it) {
		
		if (it->type == NON_TERM) {

			set<string> partial_first, partial_follow;

			rules_follow(follow[it->id], partial_first, partial_follow, it->id, rules);
		}
	}

	for (auto it = vars.begin(); it != vars.end(); ++it) {
		
		if (it->type == NON_TERM) {

			set<string> partial_first, partial_follow;

			rules_find_first(first[it->id], follow, it->id, rules);
		}
	}
}

void rules_first (set<string>& first, set<string>& partial_first, set<string>& partial_follow, string var, vector<rule_t>& rules) {

	if (partial_first.count(var)) {

		return;
	}

	partial_first.insert(var);

	for (auto rule = rules.begin(); rule != rules.end(); ++rule) {

		if (var == rule->head.id) {

			if (rule->production.size() > 0) {

				if (rule->production[0].type == TERM) {

					first.insert(rule->production[0].id);
				}

				else {

					auto pfi = partial_first;
					auto pfo = partial_follow;

					rules_first(first, pfi, pfo, rule->production[0].id, rules);
				}	
			}

			else {

				set<string> follow;

				auto pfi = partial_first;
				auto pfo = partial_follow;

				rules_follow(follow, pfi, pfo, rule->production[0].id, rules);

				first.insert(follow.begin(), follow.end());	
			}
		}	
	}
}

void rules_follow (set<string>& follow, set<string>& partial_first, set<string>& partial_follow, string var, vector<rule_t>& rules) {

	if (partial_follow.count(var)) {

		return;
	}

	partial_follow.insert(var);

	for (auto rule = rules.begin(); rule != rules.end(); ++rule) {

		for (auto prod = rule->production.begin(); prod != rule->production.end(); ++prod) {

			if (prod->id == var) {

				if ((prod + 1) != rule->production.end()) {

					if ((prod + 1)->type == TERM) {

						follow.insert((prod + 1)->id);
					}

					else {

						set<string> first;

						auto pfi = partial_first;
						auto pfo = partial_follow;

						rules_first(first, pfi, pfo, (prod + 1)->id, rules);
	
						follow.insert(first.begin(), first.end());	
					}	
				}

				else {

					auto pfi = partial_first;
					auto pfo = partial_follow;

					rules_follow(follow, pfi, pfo, rule->production[0].id, rules);
				}
			}
		}	
	}
}

void rules_find_first (set<string>& first, map<string, set<string>>& follows, string var, vector<rule_t>& rules) {
	
	for (unsigned int i = 0; i < rules.size(); ++i)	{
		
		if (var == rules[i].head.id) {

			if (rules[i].production.size() > 0) {

				if (rules[i].production[0].type == TERM) {

					first.insert(rules[i].production[0].id);
				}

				else {

					first.insert(follows[rules[i].production[0].id].begin(), follows[rules[i].production[0].id].end());
				}	
			}

			else {

				first.insert(follows[var].begin(), follows[var].end());	
			}
		}
	}
}

void first_follow_print (map<string, set<string>> conj) {

	for (auto fi = conj.begin(); fi != conj.end(); ++fi) {

		cout << "-----------------------" << endl << endl;

		cout << fi->first << endl << endl;

		for (auto v = fi->second.begin(); v != fi->second.end(); ++v)
		{
			cout << "  " << *v << endl;
		}
		
		cout << endl;
	}

	cout << endl;
}

#endif	