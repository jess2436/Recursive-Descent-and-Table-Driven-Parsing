/*
File: Tree.h
Authors: Jessica Chen & Shadiya Akhterd
CSC 173 | George Ferguson | Project 2
Last Modified: 10/07/24
*/

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE *TREE;
struct NODE{
    char data;
    int depth;
    TREE parent, leftmost_child, right_sibling;
};

extern TREE new_node(char data);
extern void set_parent(TREE child, TREE parent);
extern void set_LMC(TREE n, TREE child);
extern void set_RS(TREE n, TREE rs);
extern void count_depth(TREE root);
extern int seek_top(TREE n);
extern void tree_print(TREE root);
extern char get_data(TREE n);
extern TREE get_LMC(TREE n);
extern TREE get_RS(TREE n);
extern TREE get_parent(TREE n);
extern void tree_free(TREE root);

#endif