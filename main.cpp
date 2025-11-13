#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


#include "tree.h"
#include "tree_file_work.h"
#include "akinator.h"
//#include "testing.h"







int main() {
    const char* tree_condition = "tree_easy.txt";
    //const char* tree_condition = "tree_sample.txt";

    const char* for_parse = "for_parse.txt";
    FILE* test_parse = fopen(for_parse, "w");

    Tree tree = {};
    INIT_TREE(tree);

    ParseTreeFromFile(&tree, tree_condition);

    ParsePathToFile(&tree, "jarry", test_parse);
    fclose(test_parse);

    Akinate(&tree, tree.root_node_ptr);
    TreeDump(&tree, HTMLFileMode, "dump after akinator");

    FILE* tree_file = fopen(tree_condition, "w");

    PrintFileNodePrefix(tree.root_node_ptr, tree_file);

    fclose(tree_file);



    KillTree(&tree);

    printf("\n\nCOMMIT_ME_I_WORK!!!");

    return 0;

}



