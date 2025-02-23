/*
File: TDP.h
Authors: Jessica Chen & Shadiya Akhter
CSC 173 | George Ferguson | Project 2
Last Modified: 10/07/24
*/

#ifndef _TDP_H_
#define _TDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "Stack.h"

typedef struct {
    char lhs; 
    char *rhs; 
} Production;

extern Production *create_production_array();
extern int get_non_terminal_index(char non_terminal);
extern int get_terminal_index(char terminal);
extern int **create_parse_table();
extern void print_stack(Stack *stack);
extern TREE parse(char *input, char start_symbol, int **parse_table);

#endif
