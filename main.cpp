/*****************************************
 * Joe Howarth, comp 15 proj2, 11/17/16
 * main.cpp
 *
 * Contains main() for gerp
 * 	processes cmd-line arguments
 * 	
 * 	controls indexing and searching
 * 	helpers
 *
 ****************************************/
#include <iostream>
#include <vector>
#include <queue>

#include "DirNode.h"
#include "FSTree.h"
#include "File_inf.h"
#include "FSTreeTraversal.h"
#include "Search.h"

using namespace std;

void cleanup(vector<File_inf *> &Files);

int main(int argc, char* argv[]) {
	/*
	** Manage arguments
	*/
	if (argc != 2) {
		cerr << "Usage:  gerp directory" << endl
		     << "            where: directory" 
		     << " is a valid directory"; 
		return EXIT_FAILURE;
	}

	/*
	** Index supplied directory 
	*/
	

	// create FSTree from supplied directory 	
	string root = argv[1];
	FSTree tre(root); // TODO check if valid dir??

	// create sequence of File_inf objects
	vector<File_inf *> Files; // help out expansion a bit
	treeTraverse(tre.getRoot(), root, Files);

	/*
	 *  Query command loop
	 *  Search using Boyer-Moore, 
	 *  cache found newline positions
	 */
	bool case_ins = false;
	while (true) {
		cout << "Query? ";
		
		string pattern;
		if (!(cin >> pattern)) {
			cleanup(Files);
			return 0;
		}
		
		if (pattern == "@i" || pattern == "@insensitive") {
			case_ins = true;
			continue; // get next word, ie real pattern
		}
		
		
		if (pattern == "@q" || pattern == "@quit") { // quit!
				cleanup(Files);
				return 0;
		}
		
		
		// TODO clean up pattern, remove punctuation etc.

		// init SearchClass
		// create Boyer-Moore offset table based on pattern
		int num_files = Files.size();
		
		SearchClass S(pattern, case_ins);

		int num_empty = 0; // number of empty files in Files
		// open files to mmap
		for (int i = 0; i < num_files; i++) {
			Files[i]->open_m();
			
			// if non-empty file, add ptr to SearchClass
			if (!Files[i]->Empty()) {
				S.Fpush_back(Files[i]);
			}
			// add empty index to list to remove
			else {
				num_empty++;
			}
		}
		num_files -= num_empty;
	
		S.Search(num_files);
		case_ins = false;
	}

}

void cleanup(vector<File_inf *> &Files) {
	cout << "Goodbye! Thank you and have a nice day." << endl;
	
	for (int i = 0; i < Files.size(); i++) {
		delete Files[i]; 
	}


}


