/*
File: main.c
Authors: Jessica Chen & Shadiya Akhter
CSC 173 | George Ferguson | Project 2
Last Modified: 10/07/24
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Tree.h"
#include "RDP.h"
#include "TDP.h"

int main (int argc, char *argv[]){

    printf("C173 Project 2 by Jessica Chen & Shadiya Akhter\n");

    int **parse_table = create_parse_table();

    while(true){
        printf("\nEnter your input ('quit' to quit): ");
        char *input = (char *) malloc(65);
        fgets(input, 65, stdin);

        // exit condition
        if(strncmp(input, "quit", 4) == 0){
            printf("BYE.");
            free(input);
            break;
        }

        // testing RDP
        printf("\nRECURSIVE DESCENT PARSING...\n");

        TREE rdp_tree = new_RDP(input);
        if (rdp_tree == NULL){
            printf("Invalid Input (RDP). Please enter a new input.\n");
        } else {
            tree_print(rdp_tree);
            tree_free(rdp_tree);
        }

        // testing TDP
        printf("\nTABLE DRIVEN PARSING...\n");
        input[strcspn(input, "\n")] = 0;
        TREE tdp_tree = parse(input, 'E',parse_table);
        if(tdp_tree == NULL){
            printf("Invalid Input. Please enter a new input.\n");
        }
        else{
            tree_print(tdp_tree);
        }
        tree_free(tdp_tree);
        free(input);
    }
    return 0;
}

