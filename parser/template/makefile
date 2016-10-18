SRCS  = main.cpp

SRCS += parser/src/yacc.cpp
SRCS += parser/src/slr.cpp
SRCS += parser/src/bnf_rule.cpp
SRCS += parser/src/hardcode.cpp

SRCS += lexer/src/nfa.cpp
SRCS += lexer/src/util.cpp
SRCS += lexer/src/dfa.cpp
SRCS += lexer/src/digraph.cpp
SRCS += lexer/src/re_parse.cpp
SRCS += lexer/src/lex.cpp

SRCS += extend/logic_class.cpp
SRCS += extend/Logic.cpp
SRCS += extend/create.cpp
SRCS += extend/execute.cpp
SRCS += extend/visitor.cpp
SRCS += extend/replace_visitor.cpp
SRCS += extend/clone_visitor.cpp
SRCS += extend/cnf_visitor.cpp
SRCS += extend/print_visitor.cpp

OBJS=$(SRCS:.cpp=.o)

CXX?=g++
CPPFLAGS =-w -std=c++11
# CPPFLAGS +=-D DEBUG
all:  $(OBJS)
	$(CXX) -o dcompile $(OBJS)

yacc.o:     parser/src/yacc.h

bnf_rule.o: parser/src/bnf_rule.h

hardcode.o: parser/src/hardcode.h

slr.o:      parser/src/slr.h

nfa.o:      lexer/src/nfa.h

util.o:     lexer/src/util.h

dfa.o:      lexer/src/dfa.h

digraph.o:  lexer/src/digraph.h

re_parse.o: lexer/src/re_parse.h

main.o:

logic_class.o:  extend/logic_class.h

create.o:   extend/create.h

Logic.o:      extend/Logic.h

execute.o:  extend/execute.h

visitor.o:  extend/visitor.h

replace_visitor.o:  extend/replace_visitor.h

clone_visitor.o:  extend/clone_visitor.h

cnf_visitor.o:  extend/cnf_visitor.h

print_visitor.o:  extend/print_visitor.h

clean:
	-rm -f $(OBJS) dcompile