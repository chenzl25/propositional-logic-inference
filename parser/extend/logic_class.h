#ifndef LOGIC_CLASS_H
#define LOGIC_CLASS_H
#include <string>
#include <vector>
#include <map>
#include <set>

class Visitor;
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
  std::vector<Relation*> _relation_vec;
 private:
};

enum SentenceType {
  ATOMIC = 1, NOT, AND , OR, IMPLY, EQUAL
};

class Model;
class Sentence {
 public:
  Sentence();
  virtual ~Sentence() = default;
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
 private:
};

class AtomicSentence : public Sentence {
 public:
  AtomicSentence(std::string* symbol);
  virtual ~AtomicSentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  std::string* _symbol;
 private:
};

class NotSentence : public Sentence {
 public:
  NotSentence(Sentence* sentence);
  virtual ~NotSentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  Sentence* _sentence;
 private:
};

class AndSentence : public Sentence {
 public:
  AndSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~AndSentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  Sentence* _sentence1;
  Sentence* _sentence2;
 private:
};

class OrSentence : public Sentence {
 public:
  OrSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~OrSentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  Sentence* _sentence1;
  Sentence* _sentence2;
 private:
};

class ImplySentence : public Sentence {
 public:
  ImplySentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~ImplySentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  Sentence* _sentence1;
  Sentence* _sentence2;
 private:
};

class EqualSentence : public Sentence {
 public:
  EqualSentence(Sentence* sentence1, Sentence* sentence2);
  virtual ~EqualSentence();
  virtual bool check(Model& model);
  virtual bool check(std::set<std::string>& symbol_set);
  virtual Sentence* accept(Visitor* v);
  virtual SentenceType type();
  Sentence* _sentence1;
  Sentence* _sentence2;
 private:
};

class Model {
 public:
  Model();
  Model(Model& another_model);
  Model(SymbolList* symbol_list);
  ~Model();
  void induce(RelationList* relation_list);
  std::map<std::string, bool> _m;
 private:
};

#endif