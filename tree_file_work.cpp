
#include "tree_file_work.h"



#define SKIP_SPACES(ptr) \
    while(*ptr == ' ') (ptr)++; \



static TreeNode* ParseTreeFromBuffer(Tree* tree, TreeNode* parent, char** pos) {

    assert(tree);
    assert(pos);

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


        node->son1 = ParseTreeFromBuffer(tree, node, pos);
        node->son2 = ParseTreeFromBuffer(tree, node, pos);

    

        SKIP_SPACES(*pos);
        (*pos)++;

        return node;
    } else if (**pos == 'n') {
        *pos += strlen("nill");
        //TreeDump(tree, HTMLFileMode, "Parsing tree: %s\nPos:%s", __func__, *pos);
        return nullptr;
    }


    return nullptr;
    

}


TreeErr ParseTreeFromFile(Tree* tree, const char* filename) {

    assert(tree);
    assert(filename);

    struct stat buf = {};
    stat(filename, &buf);
    tree->buffer = (char*)calloc(buf.st_size + 2, sizeof(char));
    tree->buffer[buf.st_size] = '\0';
    FILE* file = fopen(filename, "r");

    fread(tree->buffer, buf.st_size, sizeof(char), file);
    fclose(file);

    char* pos = tree->buffer;
    tree->root_node_ptr = ParseTreeFromBuffer(tree, nullptr, &pos);
    TreeDump(tree, HTMLFileMode, "Func: %s\nParsed tree\n", __func__);

    FILE* test = fopen("test.txt","w");
    fprintf(test, "\n\n%s", pos);
    fclose(test);

    

    return Ok;

}

struct ForPath {
    TreeNode* node = nullptr;
    bool no = false;

};

static size_t ParsePathToBuffer(TreeNode* node, ForPath* buffer) {

    assert(node);
    assert(buffer);

    if (node->parent != nullptr) {
        buffer->node = node->parent;
        if (node->parent->son1 == node) buffer->no = false;
        if (node->parent->son2 == node) buffer->no = true;

        return 1 + ParsePathToBuffer(node->parent, buffer+1);
    } else {
        return 0;
    }
}

bool ParsePathToFile(Tree* tree, const char* mask, FILE* file) {

    assert(tree);
    assert(mask);
    assert(file);

    if (tree->root_node_ptr == nullptr) return false;

    bool found = false;
    TreeNode* node = nullptr;

    FindNode(tree, tree->root_node_ptr, mask, &found, &node);

    if (found) {

        ForPath buffer[MAX_NODES_NUMBER] = {};

        size_t size_of_path = ParsePathToBuffer(node, buffer);
        
        fprintf(file, "\"%s\"  - ", mask);

        for (ssize_t index = (ssize_t)size_of_path - 1; index >= 0 ; index--) {
            fprintf(file, " \"%s %s\" ", buffer[index].no ? "not" : "", buffer[index].node->data);
        }
    }

    return false;
}

void FindNode(Tree* tree, TreeNode* node, const char* mask, bool* found, TreeNode** found_node) {

    assert(tree);
    assert(node);
    assert(mask);
    assert(found);
    assert(found_node);

    if (!(strncmp(node->data, mask, strlen(mask)))) {
        *found = true;
        *found_node = node;
        return;
    }

    if (node->son1 && !*found) FindNode(tree, node->son1, mask, found, found_node);
    if (node->son2 && !*found) FindNode(tree, node->son2, mask, found, found_node);

    return;

}

void PrintFileNodePrefix(TreeNode* node, FILE* file) {

    assert(file);
    assert(node);

    fprintf(file, " ( ");

    fprintf(file, " \"%s\" ", node->data);

    if (node->son1) PrintFileNodePrefix(node->son1, file);
    else fprintf(file, " nill ");
    if (node->son2) PrintFileNodePrefix(node->son2, file);
    else fprintf(file, " nill ");

    fprintf(file, " ) ");
}

