#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>


typedef char* tree_type;

static const size_t     MAX_STRING_SIZE      =  128;
static const size_t     STRING_SIZE_EXPANDER =    2;
static const size_t     MAX_NODES_NUMBER     =  100;


enum TreeErr {
    Ok,
    AlocationError,
    NumberOfElementsError,
    DataPtrError,
    ParrentError,
    ParentSonError,
    TwoSonsError


};

enum TreeDataMemoryType {
    NoNewMemory,
    NewMemory
};


enum DumpingMode {
    HTMLFileMode,
    StdMode
};

struct AdditionalTreeNodeInfo {
    //TreeNode* parent_ptr = nullptr;
};

struct BirthInfo {
    const char* file;
    const char* func;
    const char* name;
    int         line;
};

struct TreeNode {
    tree_type data = NULL;

    TreeDataMemoryType data_memory_type = NoNewMemory;

    TreeNode* parent = nullptr;

    TreeNode* son1 = nullptr;
    TreeNode* son2 = nullptr;

    AdditionalTreeNodeInfo add_node_info = {};
};

struct Tree {

    size_t number_of_elements = 0;

    char* buffer = nullptr;

    TreeNode* root_node_ptr = nullptr;

    BirthInfo info = {};

    TreeErr error = Ok;

    const char* dump_filename = nullptr;
    FILE* dump_file = nullptr;

};

#define INIT_TREE(tree) do {                                  \
    TreeCtor(&tree, {__FILE__, __func__, #tree, __LINE__});    \
} while(0);


#define ASSERT_OK(tree) do{              \
                                        \
    TreeErr code = Ok;                \
                                        \
    if ((code = TreeVerify(tree)) != Ok) {    \
        TreeDump(tree, StdMode, "ASSERTED");                \
        printf("ASSERTION FAILED\n\n"); \
        return code;                    \
    }                                   \
                                        \
}while(0);




TreeErr TreeVerify(Tree* tree);
void TreeCtor(Tree* tree, BirthInfo info_got);
void PrintNodeInfix(TreeNode* node);
void FillArrNodeInfix(TreeNode* node, char arr[][MAX_STRING_SIZE], size_t arr_size, size_t* index);
void KillSubtree(Tree* tree, TreeNode* node);
void KillTree(Tree* tree);
void AddValueToSortingSubtree(Tree* tree, TreeNode* subtree_root, tree_type value, TreeDataMemoryType data_mem_t);
TreeNode* AlocateTreeNode(TreeNode* parent, tree_type value, TreeDataMemoryType data_mem_t);
void TreeDump(Tree* tree, DumpingMode mode, const char* why_dump, ...);



#endif
