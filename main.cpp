#include <stdlib.h>
#include <stdio.h>


#include "tree.h"

int main() {

    const char* html_filename = "out_br.html";

    FILE* out_html = fopen(html_filename, "w");
    fclose(out_html);
    out_html = fopen(html_filename, "a");

    Tree tree1 = {};

    AddValueToSubtree(&tree1, tree1.root_node_ptr, 33);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 93);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 2);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 3333);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 12);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 6);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 1);
    AddValueToSubtree(&tree1, tree1.root_node_ptr, 555);

    PrintNodeInfix(tree1.root_node_ptr);

    DumpTree(&tree1, HTMLFileMode, out_html);


    fclose(out_html);

    printf("\n\nCOMMIT_ME_I_WORK!!!");

    return 0;

}
