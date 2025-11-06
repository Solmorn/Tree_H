#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>


typedef const char* tree_type;

static const size_t     CHAR_STRING_SIZE   =  128;


enum DumpingMode {
    HTMLFileMode
};

struct AdditionalTreeNodeInfo {
    //TreeNode* parent_ptr = nullptr;
};

struct TreeNode {
    tree_type value;

    TreeNode* parent = nullptr;

    TreeNode* son1 = nullptr;
    TreeNode* son2 = nullptr;

    AdditionalTreeNodeInfo add_node_info = {};
};

struct Tree {

    size_t number_of_elements = 0;

    TreeNode* root_node_ptr;

};


void PrintNodeInfix(TreeNode* node);
void KillSubtree(Tree* tree, TreeNode* node);
void AddValueToSubtree(Tree* tree, TreeNode* subtree_root, tree_type value);
TreeNode* AlocateTreeNode(TreeNode* parent, tree_type value);
void DumpTree(Tree* tree, DumpingMode mode, FILE* out);



#endif
