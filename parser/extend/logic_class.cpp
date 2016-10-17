#include "logic_class.h"

SymbolList::SymbolList() {

}
SymbolList::~SymbolList() {
	for (int i = 0; i < _symbol_vec.size(); i++) {
    if(_symbol_vec[i] != NULL) delete _symbol_vec[i];
    _symbol_vec[i] = NULL;
  }
}
void SymbolList::add_symbol(std::string* symbol) {
	_symbol_vec.push_back(symbol);
}



Relation::Relation(std::string* symbol, Sentence* sentence) {
	_symbol = symbol;
	_sentence = sentence;
}
Relation::~Relation() {
	if (_symbol != NULL) {
		delete _symbol;
		_symbol = NULL;
	}
	if (_sentence != NULL) {
		delete _sentence;
		_sentence = NULL;
	}
}



RelationList::RelationList() {

}
RelationList::~RelationList() {
	for (int i = 0; i < _relation_vec.size(); i++) {
    if(_relation_vec[i] != NULL) delete _relation_vec[i];
    _relation_vec[i] = NULL;
  }
}
void RelationList::add_relation(std::string* symbol, Sentence* sentence) {
	_relation_vec.push_back(symbol);
}



Sentence::Sentence() {

}


AtomicSentence::AtomicSentence(std::string* symbol) {
	_symbol = symbol;
}
AtomicSentence::~AtomicSentence() {
	if (_symbol != NULL) {
		delete _symbol;
		_symbol = NULL;
	}
}



NotSentence::NotSentence(Sentence* sentence) {
	_sentence = sentence;
}
NotSentence::~NotSentence() {
	if (_sentence != NULL) {
		delete _sentence;
		_sentence = NULL;
	}
}



AndSentence::AndSentence(Sentence* sentence1, Sentence* sentence2) {
	_sentence1 = sentence1;
	_sentence2 = sentence2;
}
AndSentence::~AndSentence() {
	if (_sentence1 != NULL) {
		delete _sentence1;
		_sentence1 = NULL;
	}
	if (_sentence2 != NULL) {
		delete _sentence2;
		_sentence2 = NULL;
	}
}



OrSentence::OrSentence(Sentence* sentence1, Sentence* sentence2) {
	_sentence1 = sentence1;
	_sentence2 = sentence2;
}
OrSentence::~OrSentence() {
	if (_sentence1 != NULL) {
		delete _sentence1;
		_sentence1 = NULL;
	}
	if (_sentence2 != NULL) {
		delete _sentence2;
		_sentence2 = NULL;
	}
}



ImplySentence::ImplySentence(Sentence* sentence1, Sentence* sentence2) {
	_sentence1 = sentence1;
	_sentence2 = sentence2;
}
ImplySentence::~ImplySentence() {
	if (_sentence1 != NULL) {
		delete _sentence1;
		_sentence1 = NULL;
	}
	if (_sentence2 != NULL) {
		delete _sentence2;
		_sentence2 = NULL;
	}
}



EqualSentence::EqualSentence(Sentence* sentence1, Sentence* sentence2) {
	_sentence1 = sentence1;
	_sentence2 = sentence2;
}
EqualSentence::~EqualSentence() {
	if (_sentence1 != NULL) {
		delete _sentence1;
		_sentence1 = NULL;
	}
	if (_sentence2 != NULL) {
		delete _sentence2;
		_sentence2 = NULL;
	}
}
