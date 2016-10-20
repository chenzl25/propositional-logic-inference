#include "clauses_visitor.h"
#include <iostream>

Sentence* ClausesVisitor::visit(AtomicSentence* atomic_sentence) {
	_cur_clause.insert(*(atomic_sentence->_symbol));
}
Sentence* ClausesVisitor::visit(NotSentence* not_sentence) {
	AtomicSentence* sub = dynamic_cast<AtomicSentence*>(not_sentence->_sentence);
	_cur_clause.insert("!" + *(sub->_symbol));
}
Sentence* ClausesVisitor::visit(AndSentence* and_sentence) {
	and_sentence->_sentence1->accept(this);
	if (and_sentence->_sentence1->type() != AND) {
		_clauses.insert(_cur_clause);
		_cur_clause.clear();
	}
	and_sentence->_sentence2->accept(this);
	if (and_sentence->_sentence2->type() != AND) {
		_clauses.insert(_cur_clause);
		_cur_clause.clear();
	}
}
Sentence* ClausesVisitor::visit(OrSentence* or_sentence) {
	or_sentence->_sentence1->accept(this);
	or_sentence->_sentence2->accept(this);
}
Sentence* ClausesVisitor::visit(ImplySentence* imply_sentence) {
	std::cout << "ClausesVisitor error in ImplySentence" << std::endl;
}
Sentence* ClausesVisitor::visit(EqualSentence* equal_sentence) {
	std::cout << "ClausesVisitor error in EqualSentence" << std::endl;
}