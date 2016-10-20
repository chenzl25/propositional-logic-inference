#include "replace_visitor.h"
#include "clone_visitor.h"
#include <iostream>

ReplaceVisitor::ReplaceVisitor(RelationList* relation_list) {
	_relation_list = relation_list;
}

Sentence* ReplaceVisitor::visit(AtomicSentence* atomic_sentence) {
	for (int i = 0; i < _relation_list->_relation_vec.size(); i++) {
		Relation* ptr = _relation_list->_relation_vec[i];
		if (*(atomic_sentence->_symbol) == *(ptr->_symbol)) {
			CloneVisitor cv;
			return ptr->_sentence->accept(&cv);
		}
	}
	return atomic_sentence;
}
Sentence* ReplaceVisitor::visit(NotSentence* not_sentence) {
	not_sentence->_sentence = not_sentence->_sentence->accept(this);
	return not_sentence;
}
Sentence* ReplaceVisitor::visit(AndSentence* and_sentence) {
	and_sentence->_sentence1 = and_sentence->_sentence1->accept(this);
	and_sentence->_sentence2 = and_sentence->_sentence2->accept(this);
	return and_sentence;
}
Sentence* ReplaceVisitor::visit(OrSentence* or_sentence) {
	or_sentence->_sentence1 = or_sentence->_sentence1->accept(this);
	or_sentence->_sentence2 = or_sentence->_sentence2->accept(this);
	return or_sentence;
}
Sentence* ReplaceVisitor::visit(ImplySentence* imply_sentence) {
	imply_sentence->_sentence1 = imply_sentence->_sentence1->accept(this);
	imply_sentence->_sentence2 = imply_sentence->_sentence2->accept(this);
	return imply_sentence;
}
Sentence* ReplaceVisitor::visit(EqualSentence* equal_sentence) {
	equal_sentence->_sentence1 = equal_sentence->_sentence1->accept(this);
	equal_sentence->_sentence2 = equal_sentence->_sentence2->accept(this);
	return equal_sentence;
}