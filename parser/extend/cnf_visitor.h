#ifndef CNF_VISITOR_H
#define CNF_VISITOR_H
#include "visitor.h"

class CNFVisitor : public Visitor {
 public:
	virtual Sentence* visit(AtomicSentence* atomic_sentence);
	virtual Sentence* visit(NotSentence* not_sentence);
	virtual Sentence* visit(AndSentence* and_sentence);
	virtual Sentence* visit(OrSentence* or_sentence);
	virtual Sentence* visit(ImplySentence* imply_sentence);
	virtual Sentence* visit(EqualSentence* equal_sentence);
};

#endif