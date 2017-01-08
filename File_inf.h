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
#include <string>

#ifndef FILE_INF_H
#define FILE_INF_H

// a struct of file info and useful caches
struct File_inf 
{
public:
	File_inf();
	File_inf(std::string path);
	~File_inf();

	void Fsetup(std::string path); 
	void open_m(); // open file to mmap, get filesize if first open
	void close_m(); // clears mmap from memory using munmap
	void Print();    // prints output for matches in file


	std::string Path;
	char *contents;	// pointer to mmap, servers as a c_string
	
	std::vector<int>  pos;    // array of match positions
		      		  // set to NULL after each query	
	
	int cSize;       // number of chars in size
	bool Empty(); // returns if file is empty
	bool isFirstPrint(); // checks if first time a match was found
				// gathers line numbers etc
			
private:
	std::vector<int> known_lines; // positions of known newlines
			 // after each query, positions of newlines 
			 // added to vector

	void getLinePos(); // saves unknown endline positions to cache

	// gets line number of match	
	int getLineNum(int target, int l, int r, int m);
	void printLine(int left, int right);

	size_t fSize; 	// size of file. used when opening mmap
	bool empty; // if file is empty
	bool first_print; // is this the first time printing from file?
	void getFSize(int fd); // gets size of file


	char *Path_c;
	

};

#endif
