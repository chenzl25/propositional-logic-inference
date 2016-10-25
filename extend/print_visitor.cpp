#include "print_visitor.h"
#include <iostream>

Sentence* PrintVisitor::visit(AtomicSentence* atomic_sentence) {
	std::cout << *(atomic_sentence->_symbol);
}
Sentence* PrintVisitor::visit(NotSentence* not_sentence) {
	std::cout << "!(";
	not_sentence->_sentence->accept(this);
	std::cout << ")";
}
Sentence* PrintVisitor::visit(AndSentence* and_sentence) {
	std::cout << "(";
	and_sentence->_sentence1->accept(this);
	std::cout << ")";
	std::cout << " & ";
	std::cout << "(";
	and_sentence->_sentence2->accept(this);
	std::cout << ")";
}
Sentence* PrintVisitor::visit(OrSentence* or_sentence) {
	std::cout << "(";
	or_sentence->_sentence1->accept(this);
	std::cout << ")";
	std::cout << " | ";
	std::cout << "(";
	or_sentence->_sentence2->accept(this);
	std::cout << ")";
}
Sentence* PrintVisitor::visit(ImplySentence* imply_sentence) {
	std::cout << "(";
	imply_sentence->_sentence1->accept(this);
	std::cout << ")";
	std::cout << " => ";
	std::cout << "(";
	imply_sentence->_sentence2->accept(this);
	std::cout << ")";
}
Sentence* PrintVisitor::visit(EqualSentence* equal_sentence) {
	std::cout << "(";
	equal_sentence->_sentence1->accept(this);
	std::cout << ")";
	std::cout << " <=> ";
	std::cout << "(";
	equal_sentence->_sentence2->accept(this);
	std::cout << ")";
}