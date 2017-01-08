/*******************************************
 * Joe Howarth, Comp 15 proj 2, 11/17/16
 * FSTreeTraversal.cpp
 *
 * Traverses given directory, create 
 * 	file_inf object for each file,
 * 	saves path
 *
 *'*'* UNCOMMENT 2nd MAIN FOR PRINTING *'*'*
 * 	Traverses given directory, printing 
 * 	   full paths for each file in dir
 *
 *
 ******************************************/

#include <iostream>

#include "DirNode.h"
#include "FSTree.h"
#include "File_inf.h"

using namespace std;

// add all file paths to File_inf vector in current directory
void pFNames(DirNode* curr, string Path, vector<File_inf *> &Files) {
	int num_files = curr->numFiles();

	
	// loop over all files in dir and print their path
	for (int i = 0; i < num_files; i++) {
		string fPath = Path + curr->getFile(i);

		File_inf *temp = new File_inf;
		temp->Fsetup(fPath);

		// create new File_inf object, add it to list
		Files.push_back( temp );
		// cout << fPath << endl;
	}
}

void treeTraverse(DirNode *curr, string Path, vector<File_inf *> &Files)
{

	// update path 
	if (curr->getParent() != NULL) // if root, already in path
		Path += curr->getName();
	Path += "/";

	// processes files in current directory
	pFNames(curr, Path, Files);

	// recurse through child directories
	int Dirs = curr->numSubDirs();
	for (int i = 0; i < Dirs; i++) {
		DirNode *childDir = curr->getSubDir(i);
		treeTraverse(childDir, Path, Files); 
	}

}

/*
 * 
 * Prints paths for all files in specified directory
 * For submission 2 of proj
 */
/* ~~ UNCOMMENT FOR OTHER FUNCTIONALITY ~~
int main(int argc, char* argv[]) {
	// if more than 1 arg, specify usage, exit
	if (argc != 2) {
		cout << "Usage: treeTraversal Directory" << endl;
		return 0;
	}
	
	// create FSTree
	string root = argv[1]; // convert c_string to std::string
	FSTree tre(root);  
	
	// print all files in dir
	treeTraverse(tre.getRoot(), root);
}
*/
