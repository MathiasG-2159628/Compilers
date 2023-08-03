# -std=c++14: we're limiting ourselves to c++14, since that's what the 
#             GCC compiler on the VSC supports.
# -DNDEBUG: turns off e.g. assertion checks
# -O3: enables optimizations in the compiler

# Settings for optimized build
FLAGS= -O0 -DNDEBUG -DCMAKE_BUILD_TYPE=Debug -std=c++17 -g

# Settings for a debug build
#FLAGS=-g -std=c++14

all: test.tab

clean:
	rm -f test.tab

test.tab: 
	g++ $(FLAGS) test.tab.cpp structs.cpp returnvalue.cpp symboltable.cpp functiontable.cpp lex.yy.c -o test.tab.exe



