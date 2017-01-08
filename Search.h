/****************************************************
 * Joe Howarth, Comp 15 Proj2, 11/22/16
 * Serach.h
 *
 * Interface for Search class
 * 	takes in queue of opened file_inf*
 * 		pattern
 *
 ****************************************************/

#include <vector>
#include <queue>
#include <iostream>
#include <climits>

#include "File_inf.h"

#ifndef SEARCHCLASS_H
#define SEARCHCLASS_H

class SearchClass
{
public:
	SearchClass(std::string pat, bool case_ins);
	~SearchClass();

	void Search(int num_files); // searches all files in directory for pattern

	void preBM(); // create Boyer-Moore offset table based on pattern
	
	void BMSearch(const char* hay, std::vector<int> &positions, 
				unsigned int cSize);
	
	void Fpush_back(File_inf *F);
	
private:
	bool case_ins;
	unsigned int table[UCHAR_MAX + 1];
	
	std::queue<File_inf *> Opened;

	char *pattern; // pattern to look for
	int len; // length of pattern

	std::string Pattern;


};

#endif
