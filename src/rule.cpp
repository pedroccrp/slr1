#include "rule.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "variable.h"

using namespace std;

// ---- Implementation ----------------------------------------------------------------------

Rule rule_new (Variable head, vector<Variable> production) {

	Rule r;

	r.head = head;
	r.production = production;

	return r;
}

bool rule_compare (Rule r1, Rule r2) {

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

void rule_show (Rule r) {

	cout << r.head.id << " -> ";

	for (unsigned int i = 0; i < r.production.size(); ++i)
	{
		cout << r.production[i].id << " ";
	}

	cout << endl;
}

vector<Rule> rule_expand (vector<Rule> oldRules, vector<Rule> defaultRules) {

	vector<Rule> newRules;
	
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

void rules_generate_first_follow (vector<Variable> vars, vector<Rule> rules, map<string, set<string>>& first, map<string, set<string>>& follow) {

	for (auto variable_iterator : vars) {
		
		if (variable_iterator.type == NON_TERM) {

			set<string> partial_first, partial_follow;

			rules_follow(follow[variable_iterator.id], partial_first, partial_follow, variable_iterator.id, rules);
		}
	}

	for (auto it = vars.begin(); it != vars.end(); ++it) {
		
		if (it->type == NON_TERM) {

			set<string> partial_first;

			rules_find_first(first[it->id], partial_first, follow, it->id, rules);
		}
	}
}

void rules_first (set<string>& first, set<string>& partial_first, set<string>& partial_follow, string var, vector<Rule>& rules) {

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

				rules_follow(follow, pfi, pfo, rule->head.id, rules);

				first.insert(follow.begin(), follow.end());	
			}
		}	
	}
}

void rules_follow (set<string>& follow, set<string>& partial_first, set<string>& partial_follow, string var, vector<Rule>& rules) {

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

					rules_follow(follow, pfi, pfo, rule->head.id, rules);
				}
			}
		}	
	}
}

void rules_find_first (set<string>& first, set<string>& partial_first, map<string, set<string>>& follows, string var, vector<Rule>& rules) {

	if (partial_first.count(var)) {

		return;
	}

	partial_first.insert(var);

	for (unsigned int i = 0; i < rules.size(); ++i)	{
		
		if (var == rules[i].head.id) {

			if (rules[i].production.size() > 0) {

				if (rules[i].production[0].type == TERM) {

					first.insert(rules[i].production[0].id);
				}

				else {

					set<string> fi;

					rules_find_first(fi, partial_first, follows, rules[i].production[0].id, rules);

					first.insert(fi.begin(), fi.end());	
				}	
			}

			else {

				first.insert(follows[var].begin(), follows[var].end());	
			}
		}
	}
}

void first_follow_print (map<string, set<string>> conj, bool isFirst) {

	cout << endl << endl << "------- " << (isFirst ? "First" : "Follow") << " ----------------------------------------------------------------------" << endl << endl;

	for (auto fi = conj.begin(); fi != conj.end(); ++fi) {

		cout << "-----------------------" << endl << endl;

		cout << "  " << fi->first << endl << endl;

		for (auto v = fi->second.begin(); v != fi->second.end(); ++v)
		{
			cout << "    " << *v << endl;
		}
		
		cout << endl;
	}

	cout << endl;
}