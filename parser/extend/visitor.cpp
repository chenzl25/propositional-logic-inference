#include "visitor.h"

Sentence* Visitor::visit(AtomicSentence* atomic_sentence) {}
Sentence* Visitor::visit(NotSentence* not_sentence) {}
Sentence* Visitor::visit(AndSentence* and_sentence) {}
Sentence* Visitor::visit(OrSentence* or_sentence) {}
Sentence* Visitor::visit(ImplySentence* imply_sentence) {}
Sentence* Visitor::visit(EqualSentence* equal_sentence) {}