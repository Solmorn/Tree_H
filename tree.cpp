#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <assert.h>

#include "tree.h"

void AddDotNodeRanks(TreeNode* cur_node, FILE* out, size_t rank);
void AddDotArrows(TreeNode* cur_node, FILE* out, size_t from);
void MakeDotFromTree(Tree* tree, const char* filename);

void PrintNodeInfix(TreeNode* node) {

    assert(node);

    //printf("(");

    if (node->son1) PrintNodeInfix(node->son1);

    printf("%s ", node->value);

    if (node->son2) PrintNodeInfix(node->son2);

    //printf(")");
}

void KillSubtree(Tree* tree, TreeNode* node) {

    assert(node);

    if (node->son1) KillSubtree(tree, node->son1);
    if (node->son2) KillSubtree(tree, node->son2);

    free(node);
    tree->number_of_elements--;
}

void AddValueToSubtree(Tree* tree, TreeNode* subtree_root, tree_type value) {

    assert(tree);

    if (tree->root_node_ptr == nullptr) {

        tree->root_node_ptr = AlocateTreeNode(nullptr, value);
        tree->number_of_elements++;
        return;
    }

    if (atoi(value) > atoi(subtree_root->value)) {

        if (subtree_root->son2 == nullptr) {
            subtree_root->son2 = AlocateTreeNode(subtree_root, value);
            tree->number_of_elements++;
        } else AddValueToSubtree(tree, subtree_root->son2, value);

    } else {

        if (subtree_root->son1 == nullptr) {
            subtree_root->son1 = AlocateTreeNode(subtree_root, value);
            tree->number_of_elements++;
        } else AddValueToSubtree(tree, subtree_root->son1, value);
    }
}

TreeNode* AlocateTreeNode(TreeNode* parent, tree_type value) {

    TreeNode* new_node_ptr = (TreeNode*)calloc(1, sizeof(TreeNode));

    new_node_ptr->value = value;
    new_node_ptr->parent = parent;

    return new_node_ptr;
}

void DumpTree(Tree* tree, DumpingMode mode, FILE* out) {

    assert(tree);

    if (mode == HTMLFileMode) {
        fprintf(out, "<pre>\n");
    }
    if (mode == HTMLFileMode) {

        static size_t number_of_images = 0;

        char command[CHAR_STRING_SIZE] = "";
        char img_file[CHAR_STRING_SIZE] = "";


        const char* temp_dot_code = "temp_dot_code.dot";

        MakeDotFromTree(tree, temp_dot_code);

        sprintf(img_file, "images/img%lu.svg", number_of_images);

        sprintf(command, "dot -Tsvg %s -o %s", temp_dot_code, img_file);
        system(command);

        fprintf(out, "<img src=\"%s\" style=\"max-width: 100%; height: auto;\" />\n", img_file);

        number_of_images++;

    }

}

void AddDotNodeRanks(TreeNode* cur_node, FILE* out, size_t rank) {

    static size_t node_num = 0;

    const char* style = "";
    if (cur_node->son1 == nullptr && cur_node->son2 == nullptr) {
        style = "penwidth=3, color=yellow";
    } else if (cur_node->parent == nullptr) {
        style = "penwidth=3, color=black";
    } else {
        style = "penwidth=3, color=gray";
    }
    //fprintf(out,
    //    "    node%lu [rank=%lu, shape=record, style=\"rounded,filled\", fillcolor=%s, label=\"{ parent: %p | ptr: %p | value: \'%s\' | { left: %p | right: %p } }\", %s];\n",
    //    node_num, rank, fill_color, cur_node->parent, cur_node, cur_node->value, cur_node->son1, cur_node->son2, style);
    //node_num++;

    fprintf(out,    "node%lu [rank=%lu,\n"
                        "shape=plaintext,\n"
                        "label=<"
                        "  <table BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"lightgray\">\n"
                        "    <tr><td>parent: %p</td></tr>\n"
                        "    <tr><td BGCOLOR=\"lightblue\">ptr: %p</td></tr>\n"
                        "    <tr><td BGCOLOR=\"lightgreen\">value: %s</td></tr>\n"
                        "    <tr>\n"
                        "      <td>\n"
                        "        <table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n"
                        "          <tr><td>left: %p</td><td>right: %p</td></tr>\n"
                        "        </table>\n"
                        "      </td>\n"
                        "    </tr>\n"
                        "  </table>\n"
                        ">\n"
                    "%s];\n", node_num, rank, cur_node->parent, cur_node, cur_node->value, cur_node->son1, cur_node->son2, style);
    node_num++;

    if (cur_node->son1) AddDotNodeRanks(cur_node->son1, out, rank+1);
    if (cur_node->son2) AddDotNodeRanks(cur_node->son2, out, rank+1);
}

void AddDotArrows(TreeNode* cur_node, FILE* out, size_t from) {

    static size_t node_num = 0;

    if (cur_node->parent) {
        fprintf(out, "node%lu -> node%lu [color=green, weight=2];\n", from, node_num);
    }
    size_t from_cpy = node_num;
    node_num++;

    if (cur_node->son1) AddDotArrows(cur_node->son1, out, from_cpy);
    if (cur_node->son2) AddDotArrows(cur_node->son2, out, from_cpy);

}

void MakeDotFromTree(Tree* tree, const char* filename) {

    FILE* out = fopen(filename, "w");
    fclose(out);

    out = fopen(filename, "a");


    fprintf(out, "digraph G {\n");
    fprintf(out, "    orientation=portrait;\n");
    fprintf(out, "    rankdir=TB;\n");

    
    AddDotNodeRanks(tree->root_node_ptr, out, 1);

    AddDotArrows(tree->root_node_ptr, out, 0);
    
    fprintf(out, "}\n");

    fclose(out);
}