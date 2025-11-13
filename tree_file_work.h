#ifndef TREE_FILE_WORK_H
#define TREE_FILE_WORK_H

#include <sys/stat.h>
#include <string.h>
#include <assert.h>

#include "tree.h"


TreeErr ParseTreeFromFile(Tree* tree, const char* filename);
void PrintFileNodePrefix(TreeNode* node, FILE* file);
bool ParsePathToFile(Tree* tree, TreeNode* node, const char* mask, FILE* file, bool* found);

#endif