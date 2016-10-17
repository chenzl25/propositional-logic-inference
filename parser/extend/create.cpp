#include "logic_class.h"

SymbolList* logic_create_symbol_list(std::string* symbol) {
	auto symbol_list = new SymbolList();
  symbol_list->add_symbol(symbol);
  return symbol_list;
}

SymbolList* logic_chain_symbol_list(SymbolList* symbol_list, std::string* symbol) {
	symbol_list->add_symbol(symbol);
  return symbol_list;
}

RelationList* logic_create_relation_list(std::string* symbol, Sentence* sentence) {
	auto relation_list = new RelationList();
  relation_list->add_relation(symbol, sentence);
  return relation_list;
}

RelationList* logic_create_relation_list(RelationList* relation_list, std::string* symbol, Sentence* sentence) {
	relation_list->add_relation(symbol, sentence);
  return relation_list;
}


Sentence* logic_create_atomic_sentence(std::string* symbol) {
	return new AtomicSentence(symbol);
}

Sentence* logic_create_logical_not_sentence(Sentence* sentence) {
	return new NotSentence(sentence);
}

Sentence* logic_create_logical_and_sentence(Sentence* sentence1, Sentence* sentence2) {
	return new AndSentence(sentence1, sentence2);
}

Sentence* logic_create_logical_or_sentence(Sentence* sentence1, Sentence* sentence2) {
	return new OrSentence(sentence1, sentence2);
}

Sentence* logic_create_logical_imply_sentence(Sentence* sentence1, Sentence* sentence2) {
	return new ImplySentence(sentence1, sentence2);
}

Sentence* logic_create_logical_equal_sentence(Sentence* sentence1, Sentence* sentence2) {
	return new EqualSentence(sentence1, sentence2);
}

