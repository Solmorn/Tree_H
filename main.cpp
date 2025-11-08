#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


#include "tree.h"

#define TEST_ARR_CAP 20

size_t RandTreeSortTesting(FILE* out_html, size_t number_of_rand_tests);

int compare_strings(const void* a, const void* b) {
    const char* str1 = (const char*)a;
    const char* str2 = (const char*)b;
    return atoi(str1) - atoi(str2);
}


int main() {

    const char* html_filename = "out_br.html";

    FILE* out_html = fopen(html_filename, "w");
    fclose(out_html);
    out_html = fopen(html_filename, "a");

    size_t number_of_rand_tests = 10;
    printf("TREE SORTING, RANDOM TESTS\nPASSED: %lu\nFROM:  %lu", 
        RandTreeSortTesting(out_html, number_of_rand_tests), number_of_rand_tests);



    fclose(out_html);

    printf("\n\nCOMMIT_ME_I_WORK!!!");

    return 0;

}


size_t RandTreeSortTesting(FILE* out_html, size_t number_of_rand_tests) {

    size_t passed = 0;

    srand((unsigned int)time(NULL));

    for (size_t  arr_generated = 0; arr_generated < number_of_rand_tests; arr_generated++) {

        Tree tree1 = {};
        char arr[TEST_ARR_CAP][CHAR_STRING_SIZE] = {};
        char arr_check[TEST_ARR_CAP][CHAR_STRING_SIZE] = {};

        for (size_t counter = 0; counter < TEST_ARR_CAP; counter++) {

            int num = rand() % 1000 + 1;


            sprintf(arr[counter], "%d", num);
        }



        for (size_t i = 0; i < TEST_ARR_CAP; i++) {
            AddValueToSubtree(&tree1, tree1.root_node_ptr, arr[i]);
        }

        FillArrNodeInfix(tree1.root_node_ptr, arr_check, TEST_ARR_CAP);

        qsort(arr, TEST_ARR_CAP, sizeof(arr[0]), compare_strings);
        
        printf("Sorted arr%lu:\n", arr_generated);

        for (size_t index = 0; index < TEST_ARR_CAP; index++) {

            printf(" %s ", arr[index]);
        }

        printf("\n");

        printf("Tree%lu:\n", arr_generated);

        PrintNodeInfix(tree1.root_node_ptr);
        printf("\n");

        bool sorted_correct = 1;
        for (size_t index = 0; index < TEST_ARR_CAP; index++) {

            if (atoi(arr[index]) != atoi(arr_check[index])) sorted_correct = 0;
        }

        if (sorted_correct) {
            printf("SORTED_CORRECT\n\n");
            passed++;
        } else {
            printf("SORTED_FAILED\n\n");
        }                

        DumpTree(&tree1, HTMLFileMode, out_html);


        KillSubtree(&tree1, tree1.root_node_ptr);

                
    }

    return passed;

}