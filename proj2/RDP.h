/*
File: RDP.h
Authors: Jessica Chen & Shadiya Akhter
CSC 173 | George Ferguson | Project 2
Last Modified: 10/07/24
*/

#ifndef _RDP_H_
#define _RDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"

extern char *next_input;
extern TREE root;

extern TREE new_RDP(char *input);
extern bool lookahead(char c);
extern int match(char c);
extern bool is_digit(char c);
extern TREE E();
extern TREE U();
extern TREE T();
extern TREE G();
extern TREE F();
extern TREE A();
extern TREE N();
extern TREE M();
extern TREE D();

#endif
