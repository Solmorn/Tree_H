#ifndef TREE_FILE_WORK_H
#define TREE_FILE_WORK_H

#include <sys/stat.h>
#include <string.h>
#include <assert.h>

#include "tree.h"

bool ParsePathToFile(Tree* tree, const char* mask, FILE* file);
TreeErr ParseTreeFromFile(Tree* tree, const char* filename);
void PrintFileNodePrefix(TreeNode* node, FILE* file);
void FindNode(Tree* tree, TreeNode* node, const char* mask, bool* found, TreeNode** found_node);

#endif