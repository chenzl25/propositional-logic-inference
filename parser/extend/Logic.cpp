#include "Logic.h"

namespace Logic {

Interpreter* Interpreter::_instance = NULL;

Interpreter::Interpreter() {
}
Interpreter::~Interpreter() { // order is importance
  if (_symbol_list != NULL) {
  	delete _symbol_list;
  	_symbol_list = NULL;
  }
	if (_relation_list != NULL) {
		delete _relation_list;
		_relation_list = NULL;
	}
	if (_KB != NULL) {
		delete _KB;
		_KB = NULL;
	}
	if (_alpha != NULL) {
		delete _alpha;
		_alpha = NULL;
	}
}

void Interpreter::setup(SymbolList* symbol_list, 
  					 RelationList* relation_list, 
  					 Sentence* KB, 
  					 Sentence* alpha) {
	_symbol_list = symbol_list;
	_relation_list = relation_list;
	_KB = KB;
	_alpha = alpha;
}

Interpreter* Interpreter::getInstance() {
  if (_instance == NULL) {
    _instance = new Interpreter();
  } 
  return _instance;
}

void Interpreter::set_lexer(Lex& lex_) {
  _lex = lex_;
}
void Interpreter::set_parsr(SLR& slr_) {
  _slr = slr_;
}
void Interpreter::parse(string code_path) {
  if (!_lex.read_code(code_path)) {
    error("read code file error");
  }
  _slr.parse(_lex);
}

}