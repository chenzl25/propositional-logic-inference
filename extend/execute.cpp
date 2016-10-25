#include "execute.h"
#include "replace_visitor.h"
#include "cnf_visitor.h"
#include "print_visitor.h"
#include "clauses_visitor.h"
#include "clone_visitor.h"
#include <iostream>
#include <set>
#include <map>
#include <queue>

void remove_relation_from_symbol(SymbolList* symbol_list, 
							  								 RelationList* relation_list) {
	for (int i = 0; i < symbol_list->_symbol_vec.size();) {
		bool isDel = false;
		for (int j = 0; j < relation_list->_relation_vec.size(); j++) {
			Relation* ptr = relation_list->_relation_vec[j];
			if (*(symbol_list->_symbol_vec[i]) == *(ptr->_symbol)) {
				for (int k = i; k < symbol_list->_symbol_vec.size() - 1; k++) {
					*(symbol_list->_symbol_vec[k]) = *(symbol_list->_symbol_vec[k+1]);
				}
				symbol_list->_symbol_vec.pop_back();
				isDel = true;
				break;
			}
		}
		if (!isDel) {
			i++;
		}
	}
}

bool tt_check_all(Sentence* KB, 
							    Sentence* alpha,
							    RelationList* relation_list,
							    SymbolList* symbol_list,
							    int index,
							    Model model) {
	model.induce(relation_list);
	if (index == symbol_list->_symbol_vec.size()) {
		if (KB->check(model)) {
			return alpha->check(model);
		} else {
			return true; // when KB is false, always return true
		}
	} else {
		int next_index = index + 1;
		return tt_check_all(KB, alpha, relation_list, symbol_list, next_index, (model._m[*(symbol_list->_symbol_vec[index])] = true, model))
					 &&
					 tt_check_all(KB, alpha, relation_list, symbol_list, next_index, (model._m[*(symbol_list->_symbol_vec[index])] = false, model));
	}
}

bool tt_entails(SymbolList* symbol_list, 
							  RelationList* relation_list, 
							  Sentence* KB, 
							  Sentence* alpha) {
	remove_relation_from_symbol(symbol_list, relation_list);
	Model model;
	bool result = tt_check_all(KB, alpha, relation_list, symbol_list, 0, model);
	return result;
}

Sentence* replace_with_relation_list(Sentence* s, RelationList* relation_list) {
	ReplaceVisitor rv(relation_list);
	PrintVisitor pv;
	return s->accept(&rv);
}

Sentence* cnfize(Sentence* s) {
	CNFVisitor cnfv;
	return s->accept(&cnfv);
}

void print_clause(Clause &c) {
	std::cout << "{ ";
	for (auto s: c) {
		std::cout << s << " ";
	}
	std::cout << "}";
}
void print_clauses(Clauses &clauses) {
	for (auto c: clauses) {
		print_clause(c);
		std::cout << " , ";
	}
	std::cout << std::endl;
}

bool clause_equal(Clause c1, Clause c2) {
	if (c1.size() != c2.size()) return false;
	for (auto c : c2)
		if (c1.count(c) == 0) return false;
	return true;
}

Clauses resolve(Clause c1, Clause c2) {
	Clauses result;
	Clause  cur_clause;
	Clause A, B, C, D;
	for (auto s1 : c1) {
		if (s1[0] != '!') {
			A.insert(s1);
		} else {
			B.insert(s1);
		}
	}
	for (auto s2 : c2) {
		if (s2[0] != '!') {
			C.insert(s2);
		} else {
			D.insert(s2);
		}
	}
	for (auto b : B)
		for (auto c : C)
			if (b == "!" + c) {
				for (auto aa : A) cur_clause.insert(aa);
				for (auto bb : B) if (bb != b) cur_clause.insert(bb);
				for (auto cc : C) if (cc != c) cur_clause.insert(cc);
				for (auto dd : D) cur_clause.insert(dd);
				result.insert(cur_clause);
				cur_clause.clear();
			}

	for (auto d : D)
		for (auto a : A)
			if (d == "!" + a) {
				for (auto aa : A) if (aa != a) cur_clause.insert(aa);
				for (auto bb : B) cur_clause.insert(bb);
				for (auto cc : C) cur_clause.insert(cc);
				for (auto dd : D) if (dd != d) cur_clause.insert(dd);
				result.insert(cur_clause);
				cur_clause.clear();
			}

	return result;
}

bool contain_empty(Clauses &clauses) {
	for (auto c : clauses)
		if (c.empty()) return true;
	return false;
}

Clauses union_set(Clauses clauses1, Clauses clauses2) {
	Clauses result = clauses1;
	for (auto c2 : clauses2) {
		bool is_same = false;
		for (auto c1 : clauses1) {
			if (clause_equal(c1, c2)) {
				is_same = true;
			}	
		}
		if (!is_same) result.insert(c2);
	}
	return result;
}

bool contain(Clauses clauses1, Clauses clauses2) {
	if (clauses2.size() > clauses1.size()) {
		return false;
	}
	for (auto c2 : clauses2) {
		bool is_contain = false;
		for (auto c1 : clauses1) {
			if (clause_equal(c1, c2)) {
				is_contain = true;
				break;
			}
		}
		if (!is_contain) return false;
	}
	return true;
}

bool resolution(SymbolList* symbol_list, 
							  RelationList* relation_list, 
							  Sentence* KB, 
							  Sentence* alpha) {
	Clauses clauses, new_clauses;
	ClausesVisitor cv;
	PrintVisitor pv;
	KB = replace_with_relation_list(KB, relation_list);
	alpha = replace_with_relation_list(alpha, relation_list);
	Sentence* cnf = cnfize(new AndSentence(KB, new NotSentence(alpha)));
	cnf->accept(&cv);
	// cnf->accept(&pv);
	clauses = cv.get_clauses();
	print_clauses(clauses);
	while (true) {
		std::cout << clauses.size() << std::endl;
		for (auto c1 : clauses) {
			for (auto c2 : clauses) {
				Clauses resolvents = resolve(c1, c2);
				if (contain_empty(resolvents)) return true;
				new_clauses = union_set(new_clauses, resolvents);
			}
		}
		if (contain(clauses, new_clauses)) return false;
		clauses = union_set(clauses, new_clauses);
	}
}

std::set<std::string> and_collector(AndSentence* s) {
	std::set<std::string> result;
	if (s->_sentence1->type() == AND) {
		std::set<std::string> and_set = and_collector(dynamic_cast<AndSentence*>(s->_sentence1));
		for (auto s : and_set) {
			result.insert(s);
		}
	} else if (s->_sentence1->type() == ATOMIC) {
		result.insert(*(dynamic_cast<AtomicSentence*>(s->_sentence1)->_symbol));
	} else {
		std::cout << "and_collector error" << std::endl;
	}
	if (s->_sentence2->type() == AND) {
		std::set<std::string> and_set = and_collector(dynamic_cast<AndSentence*>(s->_sentence2));
		for (auto s : and_set) {
			result.insert(s);
		}
	} else if (s->_sentence2->type() == ATOMIC) {
		result.insert(*(dynamic_cast<AtomicSentence*>(s->_sentence2)->_symbol));
	} else {
		std::cout << "and_collector error" << std::endl;
	}
	return result;
}	

bool forward_chaining(SymbolList* symbol_list, 
										  RelationList* relation_list, 
										  Sentence* KB, 
										  Sentence* alpha) {
	std::map<ImplySentence*, int> count;
	std::set<std::string> inferred;
	std::queue<std::string> agenda;
	std::map<ImplySentence*, std::set<std::string> > premise;
	// we assume relation_list suitable for forwward_chaining algorithm
	// that is all the KB is in relation_list
	for (int i = 0; i < relation_list->_relation_vec.size(); i++) {
		Sentence* s = relation_list->_relation_vec[i]->_sentence;
		switch (s->type()) {
			case AND: {
				std::set<std::string> and_set = and_collector(dynamic_cast<AndSentence*>(s));
				for (auto it : and_set) 
					agenda.push(it);
				break;
			}
			case ATOMIC: {
				std::cout << *(dynamic_cast<AtomicSentence*>(s)->_symbol) << std::endl;
				agenda.push(*(dynamic_cast<AtomicSentence*>(s)->_symbol));
				break;
			}
			case IMPLY: {
				ImplySentence* is = dynamic_cast<ImplySentence*>(s);
				std::set<std::string> and_set;
				if (is->_sentence1->type() == ATOMIC) {
					and_set.insert(*(dynamic_cast<AtomicSentence*>(is->_sentence1)->_symbol));
				} else {
					and_set = and_collector(dynamic_cast<AndSentence*>(is->_sentence1));
				}
				premise[is] = and_set;
				count[is] = and_set.size();
				break;
			}
			default:
				std::cout << "error type in forward_chaining" << std::endl;
				return false;
		}
	}

	std::string q = *(dynamic_cast<AtomicSentence*>(alpha)->_symbol);
	while (!agenda.empty()) {
		std::string p = agenda.front();
		agenda.pop();
		// std::cout << p << std::endl;
		if (p == q) return true;
		if (inferred.count(p) == 0) {
			inferred.insert(p);
			for (auto it : premise) {
				if (it.second.count(p) != 0) {
					count[it.first]--;
					if (count[it.first] == 0) 
						agenda.push(*(dynamic_cast<AtomicSentence*>(it.first->_sentence2)->_symbol));
				}
			}
		}
	}
	return false;
}