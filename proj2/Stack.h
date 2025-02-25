/*
File: Stack.h
*/

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNode {
    char data; 
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

extern Stack *create_stack();
extern void push(Stack *stack, char data);
extern char pop(Stack *stack);
extern bool is_empty(Stack *stack);
extern void free_stack(Stack *stack);

#endif

