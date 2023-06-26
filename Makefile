###############
## VARIABLES ##
###############

# CC: Program for compiling C programs; default cc
# CXX: Program for compiling C++ programs; default g++
# CFLAGS: Extra flags to give to the C compiler
# CXXFLAGS: Extra flags to give to the C++ compiler
# CPPFLAGS: Extra flags to give to the C preprocessor
# LDFLAGS: Extra flags to give to the linker

DEBUG = 1
EXECUTABLE_NAME = main

CC_STANDARD = c++17
CC_WARNINGS = -Wall -Wextra -Wpedantic
CC = g++
CFLAGS = $(CC_WARNINGS) -std=$(CC_STANDARD)
LDFLAGS =

ifeq ($(DEBUG), 1)
CFLAGS += -g -O0
else
CFLAGS += -O3
endif

COMPILER_CALL = $(CC) $(CFLAGS)

build: filters.o main.o
	$(COMPILER_CALL) main.o filters.o $(LDFLAGS) -o $(EXECUTABLE_NAME)

main.o:
	$(COMPILER_CALL) main.c -c

filters.o:
	$(COMPILER_CALL) src/filters.c -c

execute:
	./main

clean:
	rm -f *.o
	rm -f main
