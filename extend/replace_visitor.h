#ifndef REPLACE_VISITOR_H
#define REPLACE_VISITOR_H
#include "visitor.h"

class ReplaceVisitor : public Visitor {
 public:
 	ReplaceVisitor(RelationList* relation_list);
	virtual Sentence* visit(AtomicSentence* atomic_sentence);
	virtual Sentence* visit(NotSentence* not_sentence);
	virtual Sentence* visit(AndSentence* and_sentence);
	virtual Sentence* visit(OrSentence* or_sentence);
	virtual Sentence* visit(ImplySentence* imply_sentence);
	virtual Sentence* visit(EqualSentence* equal_sentence);
	RelationList* _relation_list;
};

#endif