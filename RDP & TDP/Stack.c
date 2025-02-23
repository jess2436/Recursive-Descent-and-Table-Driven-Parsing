/*
File: Stack.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

// function to create a new stack
Stack *create_stack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// push an element onto the stack
void push(Stack *stack, char data) {
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;

    printf("Pushed: '%c'\n", data);
}

// pop element from the stack
char pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Error: Attempt to pop from an empty stack.\n");
        return '\0'; 
    }
    StackNode *temp = stack->top;
    char data = temp->data;
    stack->top = temp->next;
    free(temp);

    printf("Popped: '%c'\n", data);
    return data;
}

// check if the stack is empty
bool is_empty(Stack *stack) {
    return stack->top == NULL;
}

// free stack
void free_stack(Stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

