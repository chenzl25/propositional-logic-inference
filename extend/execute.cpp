#include "execute.h"
#include "replace_visitor.h"
#include "cnf_visitor.h"
#include "print_visitor.h"
#include "clauses_visitor.h"
#include "clone_visitor.h"
#include <iostream>
#include <set>
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

