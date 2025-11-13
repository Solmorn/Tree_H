#ifndef TESTING_H
#define TESTING_H

#include "tree.h"

#define TEST_ARR_CAP 20


int compare_strings(const void* str1_ptr, const void* str2_ptr);
size_t RandTreeSortTesting(FILE* out_html, size_t number_of_rand_tests);

#endif