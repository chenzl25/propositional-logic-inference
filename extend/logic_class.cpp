#include "logic_class.h"
#include "visitor.h"

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
	_relation_vec.push_back(new Relation(symbol, sentence));
}



Sentence::Sentence() {

}
bool Sentence::check(Model& model) {

}
bool Sentence::check(std::set<std::string>& symbol_set) {

}
Sentence* Sentence::accept(Visitor* v) {
	return NULL;
}
SentenceType Sentence::type() {

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
bool AtomicSentence::check(Model& model) {
	return model._m[*_symbol];
}
bool AtomicSentence::check(std::set<std::string>& symbol_set) {
	return symbol_set.count(*_symbol) == 1;
}
Sentence* AtomicSentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType AtomicSentence::type() {
	return ATOMIC;
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
bool NotSentence::check(Model& model) {
	return !_sentence->check(model);
}
bool NotSentence::check(std::set<std::string>& symbol_set) {
	return _sentence->check(symbol_set);
}
Sentence* NotSentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType NotSentence::type() {
	return NOT;
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
bool AndSentence::check(Model& model) {
	return _sentence1->check(model) && _sentence2->check(model);
}
bool AndSentence::check(std::set<std::string>& symbol_set) {
	return _sentence1->check(symbol_set) && _sentence2->check(symbol_set);
}
Sentence* AndSentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType AndSentence::type() {
	return AND;
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
bool OrSentence::check(Model& model) {
	return _sentence1->check(model) || _sentence2->check(model);
}
bool OrSentence::check(std::set<std::string>& symbol_set) {
	return _sentence1->check(symbol_set) && _sentence2->check(symbol_set);
}
Sentence* OrSentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType OrSentence::type() {
	return OR;
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
bool ImplySentence::check(Model& model) {
	return !_sentence1->check(model) || _sentence2->check(model);
}
bool ImplySentence::check(std::set<std::string>& symbol_set) {
	return _sentence1->check(symbol_set) && _sentence2->check(symbol_set);
}
Sentence* ImplySentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType ImplySentence::type() {
	return IMPLY;
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
bool EqualSentence::check(Model& model) {
	return _sentence1->check(model) == _sentence2->check(model);
}
bool EqualSentence::check(std::set<std::string>& symbol_set) {
	return _sentence1->check(symbol_set) && _sentence2->check(symbol_set);
}
Sentence* EqualSentence::accept(Visitor* v) {
  return v->visit(this);
}
SentenceType EqualSentence::type() {
	return EQUAL;
}


Model::Model() {

}
Model::Model(Model& another_model) {
	for (std::map<std::string, bool>::iterator it = another_model._m.begin();
		 it != another_model._m.end(); it++) {
		_m[it->first] = it->second;
	}
}
Model::Model(SymbolList* symbol_list) {
	if (symbol_list != NULL) {
		for (int i = 0; i < symbol_list->_symbol_vec.size(); i++) {
			_m[*(symbol_list->_symbol_vec[i])] = false;
		}
	}
}
Model::~Model() {

}
void Model::induce(RelationList* relation_list) {
	if (relation_list != NULL) {
		for (int i = 0; i < relation_list->_relation_vec.size(); i++) {
			Relation* ptr = relation_list->_relation_vec[i];
			_m[*(ptr->_symbol)] = ptr->_sentence->check(*this);
		}
	}
}