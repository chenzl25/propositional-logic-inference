#ifndef CREATE_H
#define CREATE_H

#include <string>
#include "logic_class.h"

SymbolList* logic_create_symbol_list(std::string* symbol);
SymbolList* logic_chain_symbol_list(SymbolList* symbol_list, std::string* symbol);
RelationList* logic_create_relation_list(std::string* symbol, Sentence* sentence);
RelationList* logic_create_relation_list(RelationList* relation_list, std::string* symbol, Sentence* sentence);
Sentence* logic_create_atomic_sentence(std::string* symbol);
Sentence* logic_create_logical_not_sentence(Sentence* sentence);
Sentence* logic_create_logical_and_sentence(Sentence* sentence1, Sentence* sentence2);
Sentence* logic_create_logical_or_sentence(Sentence* sentence1, Sentence* sentence2);
Sentence* logic_create_logical_imply_sentence(Sentence* sentence1, Sentence* sentence2);
Sentence* logic_create_logical_equal_sentence(Sentence* sentence1, Sentence* sentence2);

#endif