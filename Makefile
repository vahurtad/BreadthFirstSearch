# Vanessa Hurtado

#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 4
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c  -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c -g

GraphClient.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c -g

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)
clean :
	$(REMOVE) FindPath GraphTest FindPath.o GraphTest.o $(BASE_OBJECTS)

submit : List.c List.h FindPath.c Graph.c Graph.h GraphTest.c Makefile README
	submit cmps101-pt.w15 pa4 List.c List.h Graph.c Graph.h GraphTest.c FindPath.c Makefile README
