/*
File: Tree.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"

// create new node in parse tree
TREE new_node(char data){
    TREE node = (TREE)malloc(sizeof(struct NODE));
    node->data = data;
    node->depth=0;
    node->leftmost_child=NULL;
    node->right_sibling=NULL;
    node->parent=NULL;
    return node;
}

// set parent node
void set_parent(TREE child, TREE parent_node){
    child->parent = parent_node;
}

// set leftmost child node
void set_LMC(TREE node, TREE child){
    node->leftmost_child = child;
    set_parent(child, node);
}

// set right sibling node
void set_RS(TREE node, TREE right){
    node->right_sibling = right;
    set_parent(right, node->parent);
}

// count tree depth
void count_depth(TREE root){
    if (root != NULL){
        root->depth = seek_top(root);
        count_depth(root->leftmost_child);
        count_depth(root->right_sibling);
    }
}

// seek top of tree
int seek_top(TREE node){
    if(node->parent == NULL){
        return 0;
    } else {
        return seek_top(node->parent) + 1;
    }
}

// print tree
void tree_print(TREE root) {
    if (root == NULL) {
        return;
    }
    count_depth(root);
    for (int i = 0; i < root->depth; i++) {
        printf(" ");
    }
    if (root->data == '\0') {
        printf("\u03B5\n");
    } else {
        printf("%c\n", root->data);
    }
    if (root->leftmost_child) {
        tree_print(root->leftmost_child);
    }
    if (root->right_sibling) {
        tree_print(root->right_sibling);
    }
}


// get tree data
char get_data(TREE node){
    return node->data;
}

// get leftmost child node
TREE get_LMC(TREE node){
    return node->leftmost_child;
}

// get right sibling node
TREE get_RS(TREE node){
    return node->right_sibling;
}

// get parent node
TREE get_parent(TREE node){
    return node->parent;
}

// free tree
void tree_free(TREE node) {
    if (node == NULL) return;
    tree_free(get_LMC(node));
    tree_free(get_RS(node));
    free(node);
}


