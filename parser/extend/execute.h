#ifndef EXCUTE_H
#define EXCUTE_H

#include "logic_class.h"

bool tt_entails(SymbolList* symbol_list, 
							  RelationList* relation_list, 
							  Sentence* KB, 
							  Sentence* alpha);

#endif