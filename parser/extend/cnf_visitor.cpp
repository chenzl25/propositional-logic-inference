#include "cnf_visitor.h"
#include "clone_visitor.h"
#include <iostream>
#include <typeinfo>

Sentence* CNFVisitor::visit(AtomicSentence* atomic_sentence) {
	// std::cout << "atomic" << std::endl;
	return atomic_sentence;
}
Sentence* CNFVisitor::visit(NotSentence* not_sentence) {
	// std::cout << "!" << std::endl;
	Sentence* result;
	if (NOT == not_sentence->_sentence->type()) {
	 	NotSentence* sub = dynamic_cast<NotSentence*>(not_sentence->_sentence);
	 	result = sub->_sentence;
	} else if (AND  == not_sentence->_sentence->type()) {
		AndSentence* sub = dynamic_cast<AndSentence*>(not_sentence->_sentence);
		Sentence* s1, *s2;
		s1 = sub->_sentence1->accept(this);
		s2 = sub->_sentence2->accept(this);
		result = new OrSentence((new NotSentence(s1))->accept(this), 
														(new NotSentence(s2))->accept(this));
	} else if (OR == not_sentence->_sentence->type()) {
		OrSentence* sub = dynamic_cast<OrSentence*>(not_sentence->_sentence);
		Sentence *s1, *s2;
		s1 = sub->_sentence1->accept(this);
		s2 = sub->_sentence2->accept(this);
		result = new AndSentence((new NotSentence(s1))->accept(this), 
														(new NotSentence(s2))->accept(this));
	} else if (ATOMIC == not_sentence->_sentence->type()) {
		return not_sentence;
	} else {
		// impossible case
		std::cout << "impossible case #NotSentence " << not_sentence->_sentence->type() << std::endl;
	}

	result = result->accept(this);
	return result;
}
Sentence* CNFVisitor::visit(AndSentence* and_sentence) {
	// std::cout << "&" << std::endl;
	and_sentence->_sentence1 = and_sentence->_sentence1->accept(this);
	and_sentence->_sentence2 = and_sentence->_sentence2->accept(this);
	return and_sentence;
}
Sentence* CNFVisitor::visit(OrSentence* or_sentence) {
	// std::cout << "|" << std::endl;
	Sentence *s1, *s2, *s11, *s22, *result;
	s1 = or_sentence->_sentence1;
	s2 = or_sentence->_sentence2;
	CloneVisitor cv;
	if (AND == s1->type()) {
		AndSentence* sub = dynamic_cast<AndSentence*>(s1);
		s22 = s2->accept(&cv);
		result = new AndSentence(new OrSentence(s2, sub->_sentence1), 
														 new OrSentence(s22, sub->_sentence2));
	} else if (AND == s2->type()) {
		AndSentence* sub = dynamic_cast<AndSentence*>(s2);
		s11 = s1->accept(&cv);
		result = new AndSentence(new OrSentence(s1, sub->_sentence1), 
														 new OrSentence(s11, sub->_sentence2));
	} else {
		return or_sentence;
	}
	result = result->accept(this);	
	return result;
}
Sentence* CNFVisitor::visit(ImplySentence* imply_sentence) {
	// std::cout << "=>" << std::endl;
	Sentence *s1, *s2, *result;
	s1 = imply_sentence->_sentence1->accept(this);
	s2 = imply_sentence->_sentence2->accept(this);
	s1 = new NotSentence(s1);
	s1 = s1->accept(this);
	result = new OrSentence(s1, s2);
	result = result->accept(this);
	return result;
}
Sentence* CNFVisitor::visit(EqualSentence* equal_sentence) {
	// std::cout << "<=>" << std::endl;
	Sentence *s1, *s11, *s2, *s22, *result;
	CloneVisitor cv;
	s1 = equal_sentence->_sentence1;
	s2 = equal_sentence->_sentence2;
	s11 = equal_sentence->_sentence1->accept(&cv);
	s22 = equal_sentence->_sentence2->accept(&cv);
	result = new AndSentence(new ImplySentence(s1, s2), new ImplySentence(s22, s11));
	result = result->accept(this);
	return result;
}