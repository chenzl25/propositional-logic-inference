#include "execute.h"
#include <iostream>
#include <map>

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
	std::cout << result << std::endl;
	return result;
}

