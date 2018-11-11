# CXX = g++

# # We add -ansi for sane regular expression parsing
# CXXFLAGS = -W -Wall -Wextra -ansi -g --std=c++14
# LINK = -lfl

# decaf: visitor.o class.o
# 	$(CXX) $(CXXFLAGS) -o $@ $? $(LINK)
# 	rm *.o

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

# parser.cc: parser.y
# 	bison -o parser.cc --defines=parser.h parser.y

# scanner.cc: scanner.l
	# flex -o scanner.cc scanner.l


TARGET=decaf
all=$(TARGET)
CC = g++
CFLAGS = -lfl `llvm-config-6.0 --cxxflags --cppflags mcjit native --ldflags --libs core` -ltinfo -lpthread -ldl
FLAGS = -w -Wno-deprecated -g --std=c++14
all: $(TARGET)
$(TARGET): lex.yy.c parser.tab.c class.cpp class_definition.h
	$(CC) $(FLAGS) lex.yy.c parser.tab.c class.cpp $(CFLAGS)
lex.yy.c: scanner.l
	flex scanner.l
parser.tab.c: parser.y
	bison -vd parser.y
clean:
	rm -f *.c parser.tab.h *.output llout a.out
veryclean:
	rm -f *.c parser.tab.h a.out XML_* *.output