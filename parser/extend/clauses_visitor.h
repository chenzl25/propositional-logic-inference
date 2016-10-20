#ifndef CLAUSES_VISITOR_H
#define CLAUSES_VISITOR_H
#include "visitor.h"
#include <set>

typedef std::set<std::string> Clause;
struct Clause_cmp {
  bool operator() (const Clause& c1, const Clause& c2) const {
  	if (c1.size() == c2.size()) {
			return c1 < c2;
  	}
  	return c1.size()<c2.size();
  }
};
typedef std::set< Clause , Clause_cmp> Clauses;
// typedef std::set<std::string> Clause;
// typedef std::set< Clause > Clauses;
class ClausesVisitor : public Visitor {
 public:
	virtual Sentence* visit(AtomicSentence* atomic_sentence);
	virtual Sentence* visit(NotSentence* not_sentence);
	virtual Sentence* visit(AndSentence* and_sentence);
	virtual Sentence* visit(OrSentence* or_sentence);
	virtual Sentence* visit(ImplySentence* imply_sentence);
	virtual Sentence* visit(EqualSentence* equal_sentence);
	Clauses _clauses;
	Clause _cur_clause;
};

#endif