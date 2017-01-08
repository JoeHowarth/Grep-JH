CXXFLAGS = -Wall -Wextra -g -pedantic -std=c++11
CXX = clang++
LDFLAGS = -g

all: 
	${CXX} $(CXXFLAGS) -o gerp main.cpp File_inf.cpp Search.cpp FSTreeTraversal.cpp FSTree.o DirNode.o	

#all: sortAlgs.o sorter.o sortAlgs.h
#	${CXX} $(CXXFLAGS) -o sorter sorter.o sortAlgs.o

Bm: BM.cpp
	${CXX} $(CXXFLAGS) -o testBM BM.cpp

provide:
	provide comp15 proj2part3 README Makefile DirNode.h DirNode.o File_inf.cpp File_inf.h FSTree.h FSTree.o FSTreeTraversal.cpp FSTreeTraversal.h main.cpp Search.cpp Search.h

