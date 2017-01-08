/********************************************
 * Joe Howarth, Comp 15 proj2, 11/25/16
 * FSTreeTraversal.h
 *
 * Interface for finding paths for all files 
 *    in given directory
 ********************************************/

#include <vector>
#include "DirNode.h"
#include "File_inf.h"

#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H

void treeTraverse(DirNode *curr, std::string Path, std::vector<File_inf *> &Files); 

#endif
