#ifndef LOGIC_H
#define LOGIC_H
#include <string>
#include <vector>
#include "logic_class.h"
#include "../lexer/src/lex.h"
#include "../parser/src/slr.h"

namespace Logic {

class Interpreter {
 private:
  static Interpreter* _instance;
  Interpreter();
  ~Interpreter();
  SymbolList* _symbol_list;
  RelationList* _relation_list;
  Sentence* _KB;
  Sentence* _alpha;
  SLR _slr;
  Lex _lex;
 public:
  static Interpreter* getInstance();
  void setup(SymbolList* symbol_list, 
             RelationList* relation_list, 
             Sentence* KB, 
             Sentence* alpha);
  void parse(std::string code_path);
  void set_lexer(Lex& lex_);
  void set_parsr(SLR& slr_);
  void execute();
  bool semantic_check();
  void dealloc();
};

}

#endif 