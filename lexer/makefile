SRCS  = src/nfa.cpp
SRCS += src/util.cpp
SRCS += src/dfa.cpp
SRCS += src/digraph.cpp
SRCS += src/re_parse.cpp
SRCS += src/lex.cpp

OBJS=$(SRCS:.cpp=.o)

CXX?=g++
CPPFLAGS =-w -std=c++11
# CPPFLAGS +=-D DEBUG

lex: $(OBJS)
	$(CXX) -o mylex $(OBJS)  src/main_lex.cpp

nfa.o:      src/nfa.h

util.o: 		src/util.h

dfa.o: 			src/dfa.h

digraph.o:  src/digraph.h

re_parse.o: src/re_parse.h

lex.o:      src/lex.h

clean:
	-rm -f $(OBJS) mylex 