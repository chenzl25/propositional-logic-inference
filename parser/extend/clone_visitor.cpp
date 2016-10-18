#include "clone_visitor.h"
#include <iostream>

Sentence* CloneVisitor::visit(AtomicSentence* atomic_sentence) {
	return new AtomicSentence(new std::string(*(atomic_sentence->_symbol)));
}
Sentence* CloneVisitor::visit(NotSentence* not_sentence) {
	Sentence* s = not_sentence->_sentence->accept(this);
	return new NotSentence(s);
}
Sentence* CloneVisitor::visit(AndSentence* and_sentence) {
	Sentence* s1, *s2;
	s1 = and_sentence->_sentence1->accept(this);
	s2 = and_sentence->_sentence2->accept(this);
	return new AndSentence(s1, s2);
}
Sentence* CloneVisitor::visit(OrSentence* or_sentence) {
	Sentence* s1, *s2;
	s1 = or_sentence->_sentence1->accept(this);
	s2 = or_sentence->_sentence2->accept(this);
	return new OrSentence(s1, s2);
}
Sentence* CloneVisitor::visit(ImplySentence* imply_sentence) {
	Sentence* s1, *s2;
	s1 = imply_sentence->_sentence1->accept(this);
	s2 = imply_sentence->_sentence2->accept(this);
	return new ImplySentence(s1, s2);
}
Sentence* CloneVisitor::visit(EqualSentence* equal_sentence) {
	Sentence* s1, *s2;
	s1 = equal_sentence->_sentence1->accept(this);
	s2 = equal_sentence->_sentence2->accept(this);
	return new EqualSentence(s1, s2);
}