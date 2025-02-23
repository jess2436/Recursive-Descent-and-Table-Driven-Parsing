/*
File: RDP.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "RDP.h"

char *next_input;
TREE root;
TREE curr;

// new recursive descent parser
TREE new_RDP(char *input){
    next_input = input;
    root = E();

    if (root == NULL){
        return NULL;
    }

    if(!match('\n')){
        return NULL;
    }   
    return root;
}

// lookahead function, peeking at the next symbol
bool lookahead(char c){
    return *next_input == c;
}

// match ("consume")
int match(char c) {
    if (next_input == NULL || *next_input == '\0') {
        return false;
    }
    if (*next_input == c) {
        next_input++;
        return true;
    }
    return false;
}


// determine if symbol is valid digit / digit production
bool is_digit(char c){
    return c >= '0' && c <= '9';
}

// E: syntactic category production (E -> T U)
TREE E(){
    TREE E_Node = new_node('E');
    TREE p1 = T();
    if (p1== NULL){
        return NULL;
    }
    TREE p2 = U();
    if(p2== NULL){
        return NULL;
    }
    set_LMC(E_Node, p1);
    set_RS(p1, p2);
    return E_Node;
}

// U: syntactic category production (U -> +E | -E | ε)
TREE U(){
    TREE U_Node = new_node('U');
    char c = *next_input;

    if (lookahead('+') || lookahead('-')) {
        if (!match(c)) {
            return NULL;
        }
        TREE p1 = E();
        if (p1 == NULL) {
            return NULL;
        }
        set_LMC(U_Node, new_node(c));
        set_RS(get_LMC(U_Node), p1);
    }
    else {
        set_LMC(U_Node, new_node('\0'));
    }
    return U_Node;
}

// T: syntactic category production (T -> F G)
TREE T(){
    TREE T_Node = new_node('T');
    TREE p1 = F();
    if (p1== NULL){
        return NULL;
    }
    TREE p2 = G();
    if (p2==NULL){
        return NULL;
    }
    set_LMC(T_Node, p1);
    set_RS(p1,p2);
    return T_Node;
}

// G: syntactic category production (G -> *T | /T | ε)
TREE G(){
    TREE G_Node = new_node('G');
    char c = *next_input;
    if (lookahead('*') || lookahead('/')) {
        if (!match(c)) {
            return NULL;
        }
        TREE p1 = T();
        if (p1 == NULL) {
            return NULL;
        }
        TREE temp = new_node(c);
        set_LMC(G_Node, temp);
        set_RS(temp, p1);
    }
    else {
        set_LMC(G_Node, new_node('\0'));  
    }
    return G_Node;
}

// F: syntactic category production (F -> +F | -F | A)
TREE F() {
    TREE F_Node = new_node('F');
    char c = *next_input;
    if (lookahead('+') || lookahead ('-')){
        if (!match(c)){
            return NULL;
        }
        TREE p1 = F();
        if (p1 == NULL){
            return NULL;
        }
        TREE temp = new_node(c);
        set_LMC(F_Node, temp);
        set_RS(temp, p1);
    }
    else{
        TREE p1 = A();
        if (p1==NULL){
            return NULL;
        }
        set_LMC(F_Node, p1);
    }
    return F_Node;
}


// A: syntactic category production (A -> (E) | N)
TREE A(){
      TREE A_Node = new_node('A');
    if (lookahead('(')){
        if (!match('(')){
            return NULL;
        }
        TREE p1 = E();
        if (p1 == NULL){
            return NULL;
        }
        if (!match(')')){
            return NULL;
        }
        set_LMC(A_Node, new_node('('));
        set_RS(get_LMC(A_Node), p1);
        set_RS(p1, new_node(')'));
    }
    else if (is_digit(*next_input)){
        TREE p1 = N();
        if (p1== NULL){
            return NULL;
        }
        set_LMC(A_Node, p1);
    }
    else {
        return NULL;
    }
    return A_Node;
}

// N: syntactic category production (N -> D M)
TREE N(){
    TREE N_Node = new_node('N');
    TREE p1 = D();
    if (p1 == NULL){
        return NULL;
    }
    TREE p2 = M();
    if (p2 == NULL){
        return NULL;
    }
    set_LMC(N_Node, p1);
    set_RS(p1,p2);
    return N_Node;
}

// M: syntactic category production (M -> N | ε)
TREE M(){
    TREE M_Node = new_node('M');
    if (is_digit(*next_input)) {
        TREE p1 = N();
        if (p1 == NULL) {
            return NULL;
        }
        set_LMC(M_Node, p1);
    }
    else {
        set_LMC(M_Node, new_node('\0'));  
    }
    return M_Node;
}

// D: syntactic category production (D -> 0|1|2|3|4|5|6|7|8|9)
TREE D(){
    TREE D_Node = new_node('D');
    if (!is_digit(*next_input)){
        return NULL;
    }
    else {
        TREE p1 = new_node(*next_input);
        set_LMC(D_Node, p1);
        next_input++;
    }
    return D_Node;
}
