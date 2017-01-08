/************************************************************
 * Joe Howarth, Comp 15 proj2, 11/22/16
 * Search.cpp
 *
 * Implements 
 * 	BMSearch - searches through file for given pattern, 
 * 		   returning indeces of matches
 * 	preBM - sets Boyer-Moore offset table based on pattern
 *	FPush_back - enqueues File_inf ptr to Opened queue
 *
 ***********************************************************/

#include <vector>
#include <queue>
#include <iostream>
#include <cctype>
#include <strings.h>

// BM libraries
#include <stddef.h>
#include <string.h>
#include <limits.h>

#include "File_inf.h"
#include "Search.h"

using namespace std;

// constructor
SearchClass::SearchClass(string pat, bool caseIns) {
	pattern = new char[pat.size() + 1];
	strcpy(pattern, pat.c_str());
	Pattern = pat;
	len = pat.size();
	case_ins = false; // silence valgrind warning
	case_ins = caseIns;

	preBM(); // create offset table
}

SearchClass::~SearchClass() {
	delete[] pattern;
}

void SearchClass::Search(int num_files) {
	
	for (int i = 0; i < num_files;) {
		File_inf *curr;
		if (!Opened.empty()) {
			curr = Opened.front();
			Opened.pop();

	//		cerr << "Searching: " << curr->Path << endl;
			BMSearch(curr->contents, curr->pos, curr->cSize);
			
			curr->isFirstPrint();
			curr->Print();
			curr->close_m();
			i++;
		}
	}

}

// initializes offset table based on pattern
void SearchClass::preBM() {
	len = strlen( pattern ); // find length of pattern

	// initialize offset table to highest skip
	for (int i = 0; i <= UCHAR_MAX; i++) {
		table[i] = len;	}

	// for each letter in pattern, set offset as len -i -1
	
	// if case insensitive, both lower and upper case are treated 
	// equally
	if (case_ins) {
		for (int i = 0; i < len; i++) {
			unsigned char ch = (unsigned char) pattern[i];
			table[(unsigned char) tolower(ch)] = len - i - 1;
			table[(unsigned char) toupper(ch)] = len - i - 1;

		}
	}
	// if not case insentive, only that specific char is offset
	else {
		for (int i = 0; i < len; i++) {
			table[(unsigned char) pattern[i]] = len - i - 1;
		}
	}
	/*
	char  whitespaces[] = { ' ', '\t', '\n', '\v', '\f', '\r'};
	for (int i = 0; i < 6; i++) {
		table[ (unsigned char) whitespaces[i]] = 1;
	}*/
}

 /* Implementation of Pratt-Boyer-Moore algorithm
  * 	Based off of Jerry Coffin's work
  * to add: Galil rule
  */
void SearchClass::BMSearch(const char* hay, vector<int> &positions, 
						unsigned int cSize) {

	int shift;
	unsigned int pos = len - 1; // starts looking in hay at end of pat
	unsigned int limit = cSize;
	char *here;
	

	
	// goes while the position being checked is within the buffer/string
	// if case insensitive, uses strncasecmp instead of strncmp
	// 	(duplicated entire function because the looped check 
	// 	 would be very expensive since the loop runs so much)
	if (case_ins) {
		while (pos < limit) {
			// checks offset table, keeps shifting until offset is 0
			while(pos < limit && (shift = 
					table[(unsigned char)hay[pos]]) > 0) {
				pos += shift;
			}
			if (0 == shift) {
				here = (char *) &hay[pos - len + 1];
				// if pattern found, add pos to vector
				if (0 == strncasecmp(pattern, here, len)  
				     && isspace(*(here + len)) 
				     && (here == hay || isspace(*(here - 1)))) 
				{
					positions.push_back(pos);
					pos += len;;
				}
				else 
					pos++;
			}
		}
	}	
	else {	
		// goes while the position being checked is within the buffer/string
		while (pos < limit) {
			// checks offset table, keeps shifting until offset is 0
			while(pos < limit && (shift = 
					table[(unsigned char)hay[pos]]) > 0) {
				pos += shift;
			}
			if (0 == shift) {
				here = (char *) &hay[pos - len + 1];
				// if pattern found, add pos to vector
				if (0 == strncmp(pattern, here, len)  
				     && isspace(*(here + len)) 
				     && (here == hay || isspace(*(here - 1)))) 
				{
				
					positions.push_back(pos);
					pos += len;;
				}
				else 
					pos++;
			}	
		}
	}
}

/*
int strcicmp(char const *a, char const *b) {
	for (;;a++, b++) {
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
			return d
	}
*/

void SearchClass::Fpush_back(File_inf *F) {
	Opened.push(F);
}




