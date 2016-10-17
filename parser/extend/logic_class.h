#ifndef LOGIC_CLASS_H
#define LOGIC_CLASS_H
#include <string>
#include <vector>

class SymbolList {
public:  
  SymbolList();
  ~SymbolList();
  void add_symbol(std::string* symbol);
  std::vector<std::string*> _symbol_vec;
private:
};

class Sentence;
class Relation {
public:  
  Relation(std::string* symbol, Sentence* sentence);
  ~Relation();
  std::string* _symbol;
  Sentence* _sentence;
private:
};

class RelationList {
public:  
  RelationList();
  ~RelationList();
  void add_relation(std::string* symbol, Sentence* sentence);
  std::vector<std::string*> _relation_vec;
private:
};


class Sentence {
public:
  Sentence();
  virtual ~Sentence() = default;
private:
};

class AtomicSentence : public Sentence {
public:
  AtomicSentence(std::string* symbol);
  virtual ~AtomicSentence();
  std::string* _symbol;
private:
};

class NotSentence : public Sentence {
public:
  NotSentence(Sentence* sentence);
  virtual ~NotSentence();
  Sentence* _sentence;
private:
};

class AndSentence : public Sentence {
public:
  AndSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~AndSentence();
  Sentence* _sentence1;
  Sentence* _sentence2;
private:
};

class OrSentence : public Sentence {
public:
  OrSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~OrSentence();
  Sentence* _sentence1;
  Sentence* _sentence2;
private:
};

class ImplySentence : public Sentence {
public:
  ImplySentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~ImplySentence();
  Sentence* _sentence1;
  Sentence* _sentence2;
private:
};

class EqualSentence : public Sentence {
public:
  EqualSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~EqualSentence();
  Sentence* _sentence1;
  Sentence* _sentence2;
private:
};

#endif