#include "Logic.h"
#include "execute.h"
#include <set>
#include <string>
#include <iostream>

namespace Logic {

Interpreter* Interpreter::_instance = NULL;

Interpreter::Interpreter() {
}
Interpreter::~Interpreter() { // order is importance
  // if (_symbol_list != NULL) {
  //   delete _symbol_list;
  //   _symbol_list = NULL;
  // }
  // if (_relation_list != NULL) {
  //   delete _relation_list;
  //   _relation_list = NULL;
  // }
  // if (_KB != NULL) {
  //   delete _KB;
  //   _KB = NULL;
  // }
  // if (_alpha != NULL) {
  //   delete _alpha;
  //   _alpha = NULL;
  // }
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

void Interpreter::dealloc() {
  delete _instance;
  _instance = NULL;
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

bool Interpreter::semantic_check() {
  set<std::string> symbol_set;
  for (int i = 0; i < _symbol_list->_symbol_vec.size(); i++) {
    symbol_set.insert(*(_symbol_list->_symbol_vec[i]));
  }
  if (!_KB->check(symbol_set)) {
    std::cout << "KB semantic_check fail!" << endl;
    return false;
  }
  if (!_alpha->check(symbol_set)) {
    std::cout << "alpha semantic_check fail!" << endl;
    return false;
  }
  for (int i = 0; i < _relation_list->_relation_vec.size(); i++) {
    Relation* ptr = _relation_list->_relation_vec[i];
    symbol_set.erase(*(ptr->_symbol));
  }
  for (int i = 0; i < _relation_list->_relation_vec.size(); i++) {
    Relation* ptr = _relation_list->_relation_vec[i];
    if (!ptr->_sentence->check(symbol_set)) {
      std::cout << "relation No." << i+1 << " semantic_check fail!" << endl;
      return false;
    }
  }
  return true;
}

void Interpreter::execute() {
  // from excute.h
  if (!semantic_check()) {
    return;
  }
  std::cout << "enter number:" << std::endl;
  std::cout << "[1]: model checking" << std::endl;
  std::cout << "[2]: resolution" << std::endl;
  std::cout << "[3]: forward chaining" << std::endl;
  int n;
  std::cin >> n;
  switch (n) {
    case 1:
      std::cout << "result: " << tt_entails(_symbol_list, _relation_list, _KB, _alpha) << std::endl;
      break;
    case 2:
      std::cout << "result: " << resolution(_symbol_list, _relation_list, _KB, _alpha) << std::endl;
      break;
    case 3:
      std::cout << "result: " << forward_chaining(_symbol_list, _relation_list, _KB, _alpha) << std::endl;
      break;
  }
}

} // end of namespace Logic