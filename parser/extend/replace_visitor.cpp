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
	return NULL;
}
Sentence* ReplaceVisitor::visit(NotSentence* not_sentence) {
	Sentence* s = not_sentence->_sentence->accept(this);
	if (s != NULL) not_sentence->_sentence = s;
}
Sentence* ReplaceVisitor::visit(AndSentence* and_sentence) {
	Sentence* s;
	s = and_sentence->_sentence1->accept(this);
	if (s != NULL) and_sentence->_sentence1 = s;
	s = and_sentence->_sentence2->accept(this);
	if (s != NULL) and_sentence->_sentence2 = s;
}
Sentence* ReplaceVisitor::visit(OrSentence* or_sentence) {
	Sentence* s;
	s = or_sentence->_sentence1->accept(this);
	if (s != NULL) or_sentence->_sentence1 = s;
	s = or_sentence->_sentence2->accept(this);
	if (s != NULL) or_sentence->_sentence2 = s;
}
Sentence* ReplaceVisitor::visit(ImplySentence* imply_sentence) {
	Sentence* s;
	s = imply_sentence->_sentence1->accept(this);
	if (s != NULL) imply_sentence->_sentence1 = s;
	s = imply_sentence->_sentence2->accept(this);
	if (s != NULL) imply_sentence->_sentence2 = s;
}
Sentence* ReplaceVisitor::visit(EqualSentence* equal_sentence) {
	Sentence* s;
	s = equal_sentence->_sentence1->accept(this);
	if (s != NULL) equal_sentence->_sentence1 = s;
	s = equal_sentence->_sentence2->accept(this);
	if (s != NULL) equal_sentence->_sentence2 = s;
}