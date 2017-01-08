/**********************************************
 * Joe Howarth, Comp 15 Proj2, 11/17/16
 * File_inf.h
 * 
 * Interface for File_inf class
 * 	Contains information for a file
 * 	Also caches info after queries
 * 	 to be used by later queries
 *********************************************/
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

// used for mmap
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>

#include "File_inf.h"

#define ENCODE_SIZE 1 // default ascii = 1 byte, change for other encodings

using namespace std;

File_inf::File_inf() {
	contents = NULL;
	fSize = 0;
	empty = false;
	first_print = true;
}

File_inf::File_inf(std::string path) {
	Path = path;
	Path_c = new char[path.size() + 1];
	strcpy(Path_c, path.c_str());
	contents = NULL;
	fSize = 0;
	empty = false;
	first_print = true;
}

void File_inf::Fsetup(string path) {
	Path = path;
	Path_c = new char[path.size() + 1];
	strcpy(Path_c, path.c_str());
}

File_inf::~File_inf() {
	delete[] Path_c;
	if (contents != NULL)
		cerr << Path << " Contents not NULL!" << endl;
}

// opens file to mmap
void File_inf::open_m() {
	// if empty, don't do anything with file
	if (empty)
		return;

	// get file descriptor
	int fd = open (Path_c, O_RDONLY);

	// if file size has not been set, set it
	if (fSize == 0) {
		getFSize(fd);
		
		// if still 0, file is empty and close file
		if (fSize == 0) { 
			close(fd);
			empty = true;
			return;
		}
	}

	contents = (char *) mmap (0, fSize, PROT_READ, MAP_PRIVATE, fd, 0);

	// close file
	if (close(fd) != 0)
		cerr << Path << "  Could not close" << endl;
	
}

void File_inf::close_m() {
	munmap((void *) contents, (size_t) fSize);
	contents = NULL;
}

void File_inf::getFSize(int fd) {
	struct stat stats;
	int status = fstat(fd, &stats);
	(void) status;

	fSize = stats.st_size; // size in bytes
	cSize = fSize / ENCODE_SIZE; // get number of chars in doc
}

/*
 * PRINTING AND LINE NUMBERS
 * ````````````````````````
 */



// prints path + line_num + line contents for each match in file
void File_inf::Print() {
	int line_num = -1;
	int prev_line;
	for (int i = 0; i < (int) pos.size(); i++) {
		prev_line = line_num;
		line_num = getLineNum(pos[i], 0, 
		                         (int) known_lines.size(), 
				         (int) known_lines.size() / 2);
		if (prev_line == line_num)
			continue;

		cout << Path << ":" << line_num + 1 << ": ";
		
		int left = known_lines[line_num - 1];
		if (line_num == 0)
			left = -1;
			
		printLine(left, known_lines[line_num]);

		cout << endl;
	}
	pos.clear();
}

// prints line from opened mmap (char[])
// range from left newline to right newline uninclusive
void File_inf::printLine(int left, int right) {

	for (int i = left + 1; i < right; i++) {
		putchar(contents[i]);
	}
}


// searches known_lines vector for the line numbers sandwiching target
// returns top number, with return - 1 of known_lines being bottom
// TODO utilize how far along target is in positions to start search
int File_inf::getLineNum(int target, int l, int r, int m) {


	if (target < known_lines[m]) {
		if (target > known_lines[m - 1])
			return m;
		else {
			return getLineNum(target, l, m, l + (m - l) / 2);
		}
	}
	else { 
		if (target < known_lines[m + 1]) {
			return (m + 1);
		}
		else {
			return getLineNum(target, m, r, m + (r - m) / 2);
		}
	}
	

}


// find all '/n' in file, save positions in known_lines vector
void File_inf::getLinePos() {
	for (int index = 0; index < cSize; index++) {
	
		if (contents[index] == '\n')
			known_lines.push_back(index);
	}
	known_lines.push_back(cSize);
}

bool File_inf::Empty() {
	return empty;
}



bool File_inf::isFirstPrint() {
	if (first_print == false)
		return false;
	
	first_print = false;
	getLinePos(); // fill known_lines with new line indeces

	return true;

}

