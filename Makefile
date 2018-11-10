CXX = g++

# We add -ansi for sane regular expression parsing
CXXFLAGS = -W -Wall -Wextra -ansi -g --std=c++14
LINK = -lfl

decaf: visitor.o class.o
	$(CXX) $(CXXFLAGS) -o $@ $? $(LINK)
	rm *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

parser.cc: parser.y
	bison -o parser.cc --defines=parser.h parser.y

scanner.cc: scanner.l
	flex -o scanner.cc scanner.l
