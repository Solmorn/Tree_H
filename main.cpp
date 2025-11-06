#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "tree.h"

int main() {

    const char* html_filename = "out_br.html";

    FILE* out_html = fopen(html_filename, "w");
    fclose(out_html);
    out_html = fopen(html_filename, "a");

    Tree tree1 = {};

    char* arr[20];
    srand((unsigned int)time(NULL));

    for (size_t counter = 0; counter < 20; counter++) {

        int num = rand() % 9 + 1;
        arr[counter] = (char*)calloc(2, sizeof(char));

        printf("%d\n", num);

        sprintf(arr[counter], "%d", num);
        printf("%d\n", atoi(arr[counter]));
    }


    for (int i = 0; i < 20; i++) {
        AddValueToSubtree(&tree1, tree1.root_node_ptr, arr[i]);
        free(arr[i]);
    }

    PrintNodeInfix(tree1.root_node_ptr);

    DumpTree(&tree1, HTMLFileMode, out_html);

    KillSubtree(&tree1, tree1.root_node_ptr);


    fclose(out_html);

    printf("\n\nCOMMIT_ME_I_WORK!!!");

    return 0;

}
