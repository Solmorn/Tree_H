
#include "tree_file_work.h"



#define SKIP_SPACES(ptr) \
    while(*ptr == ' ') (ptr)++; \



static TreeNode* ParseTreeFromBuffer(Tree* tree, TreeNode* parent, char** pos) {
    SKIP_SPACES(*pos);
    if (**pos == '(') {
        (*pos)++;
        SKIP_SPACES(*pos);

        TreeNode* node = AlocateTreeNode(parent, (*pos)+1, NoNewMemory); //offset from "
        if (tree->root_node_ptr == nullptr) tree->root_node_ptr = node;
        tree->number_of_elements++; //new node created


        int cur_str_len = 0;
        sscanf(*pos, "\"%*[^\"]\"%n", &cur_str_len);
        *pos+=cur_str_len-1; // moved to next "
        **pos = '\0';
        (*pos)++;

        TreeDump(tree, HTMLFileMode, "Parsing tree: %s\nPos:%s", __func__, *pos);

        node->son1 = ParseTreeFromBuffer(tree, node, pos);
        node->son2 = ParseTreeFromBuffer(tree, node, pos);



        SKIP_SPACES(*pos);
        (*pos)++;

        return node;
    } else if (**pos == 'n') {
        *pos += strlen("nill");
        return nullptr;
    }

    return nullptr;
    

}


TreeErr ParseTreeFromFile(Tree* tree, const char* filename) {

    struct stat buf = {};
    stat(filename, &buf);
    tree->buffer = (char*)calloc(buf.st_size + 2, sizeof(char));
    tree->buffer[buf.st_size] = '\0';
    FILE* file = fopen(filename, "r");

    fread(tree->buffer, buf.st_size, sizeof(char), file);
    fclose(file);

    char* pos = tree->buffer;
    tree->root_node_ptr = ParseTreeFromBuffer(tree, nullptr, &pos);
    TreeDump(tree, HTMLFileMode, "Parsed tree: %s\nPos:%s", __func__, pos);

    FILE* test = fopen("test.txt","w");
    fprintf(test, "\n\n%s", pos);
    fclose(test);

    

    return Ok;

}

bool ParsePathToFile(Tree* tree, TreeNode* node, const char* mask, FILE* file, bool* found) {

    if (!(strncmp(node->data, mask, strlen(mask)))) {
        *found = true;
        return true;
    }

    if (node->son1 && ParsePathToFile(tree, node->son1, mask, file, found)) {}
    else if (node->son2 && ParsePathToFile(tree, node->son2, mask, file, found)) {}

    if (*found) fprintf(file, " \"%s\" ", node->data);

    return Ok;

}

void PrintFileNodePrefix(TreeNode* node, FILE* file) {

    assert(node);

    fprintf(file, " ( ");

    fprintf(file, " \"%s\" ", node->data);

    if (node->son1) PrintFileNodePrefix(node->son1, file);
    else fprintf(file, " nill ");
    if (node->son2) PrintFileNodePrefix(node->son2, file);
    else fprintf(file, " nill ");

    fprintf(file, " ) ");
}

