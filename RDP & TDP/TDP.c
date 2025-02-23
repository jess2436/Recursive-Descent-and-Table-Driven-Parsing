/*
File: TDP.c
Authors: Jessica Chen & Shadiya Akhter
CSC 173 | George Ferguson | Project 2
Last Modified: 10/07/24
*/

#include "TDP.h"
#include "Stack.h"
#include "Tree.h"
#include <string.h>

// define the production rules 
Production *create_production_array() {
    Production *productions = (Production *)malloc(26 * sizeof(Production));
    
    productions[0] = (Production){'E', "TU"};
    productions[1] = (Production){'U', "+E"};
    productions[2] = (Production){'U', "-E"};
    productions[3] = (Production){'U', "ε"}; // ε (epsilon)
    productions[4] = (Production){'T', "FG"};
    productions[5] = (Production){'G', "*T"};
    productions[6] = (Production){'G', "/T"};
    productions[7] = (Production){'G', "ε"}; // ε
    productions[8] = (Production){'F', "+F"};
    productions[9] = (Production){'F', "-F"};
    productions[10] = (Production){'F', "A"};
    productions[11] = (Production){'A', "(E)"};
    productions[12] = (Production){'A', "N"};
    productions[13] = (Production){'N', "DM"};
    productions[14] = (Production){'M', "N"};
    productions[15] = (Production){'M', "ε"}; // ε
    productions[16] = (Production){'D', "0"};
    productions[17] = (Production){'D', "1"};
    productions[18] = (Production){'D', "2"};
    productions[19] = (Production){'D', "3"};
    productions[20] = (Production){'D', "4"};
    productions[21] = (Production){'D', "5"};
    productions[22] = (Production){'D', "6"};
    productions[23] = (Production){'D', "7"};
    productions[24] = (Production){'D', "8"};
    productions[25] = (Production){'D', "9"};

    return productions;
}

// helper function to map syntactic categories to their corresponding row in the parse table
int get_non_terminal_index(char non_terminal) {
    switch (non_terminal) {
        case 'E': return 0;
        case 'U': return 1;
        case 'T': return 2;
        case 'G': return 3;
        case 'F': return 4;
        case 'A': return 5;
        case 'N': return 6;
        case 'M': return 7;
        case 'D': return 8;
        default: return -1; 
    }
}

// helper function to map terminals to their corresponding column in the parse table
int get_terminal_index(char terminal) {
    switch (terminal) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case '0': return 6;
        case '1': return 7;
        case '2': return 8;
        case '3': return 9;
        case '4': return 10;
        case '5': return 11;
        case '6': return 12;
        case '7': return 13;
        case '8': return 14;
        case '9': return 15;
        case '\0': return 16;  
        default: return -1;
    }
}

// function to create the parse table
int **create_parse_table() {
    int **parse_table = (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++) {
        parse_table[i] = (int *)malloc(17 * sizeof(int));
        for (int j = 0; j < 17; j++) {
            parse_table[i][j] = -1; 
        }
    }

    // populating parse table according to the grammar rules
    parse_table[0][0] = 0; // E → T U
    parse_table[0][1] = 0;
    parse_table[0][4] = 0;
    for (int i = 6; i <= 16; i++) parse_table[0][i] = 0;

    parse_table[1][0] = 1;  // U → +E
    parse_table[1][1] = 2;  // U → -E
    for (int i = 2; i <= 16; i++) parse_table[1][i] = 3;

    // T → F G 
    for (int i = 0; i <= 16; i++) parse_table[2][i] = 4;

    parse_table[3][0] = 7;
    parse_table[3][1] = 7;
    parse_table[3][2] = 5;  // G → *T
    parse_table[3][3] = 6;  // G → /T
    for (int i = 4; i <= 16; i++) parse_table[3][i] = 7; // G → ϵ 

    parse_table[4][0] = 8;  // F → +F
    parse_table[4][1] = 9;  // F → -F
    parse_table[4][4] = 10; // F → A 
    for (int i = 6; i <= 15; i++) parse_table[4][i] = 10;

    parse_table[5][4] = 11; // A → (E)
    for (int i = 6; i <= 15; i++) parse_table[5][i] = 12; // A → N

    parse_table[6][6] = 13; // N → D M
    for (int i = 7; i <= 16; i++) parse_table[6][i] = 13;

    parse_table[7][0] = 15; // M → +
    parse_table[7][1] = 15; // M → -
    parse_table[7][2] = 15; // M → *
    parse_table[7][3] = 15; // M → /
    parse_table[7][4] = 15; // M → (
    parse_table[7][6] = 14; // M → N
    for (int i = 7; i <= 15; i++) parse_table[7][i] = 14;
    parse_table[7][5] = 15; // M → ε 
    parse_table[7][16] = 15; // M → ε 

    parse_table[8][6] = 16; // D → 0
    parse_table[8][7] = 17; // D → 1
    parse_table[8][8] = 18; // D → 2
    parse_table[8][9] = 19; // D → 3
    parse_table[8][10] = 20; // D → 4
    parse_table[8][11] = 21; // D → 5
    parse_table[8][12] = 22; // D → 6
    parse_table[8][13] = 23; // D → 7
    parse_table[8][14] = 24; // D → 8
    parse_table[8][15] = 25; // D → 9

    return parse_table;
}

void print_stack(Stack *stack) {
    printf("Current Stack: ");
    StackNode *current = stack->top;
    while (current != NULL) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

// parsing function
TREE parse(char *input, char start_symbol, int **parse_table) {
    Production *productions = create_production_array(); 
    Stack *stack = create_stack();
    push(stack, '$');        
    print_stack(stack);         
    push(stack, start_symbol); 
    print_stack(stack);         

    TREE root = new_node(start_symbol);
    TREE curr = root;
    char *lookahead = input;  

    while (!is_empty(stack)) {
        char top = pop(stack);  
        print_stack(stack);    

        if (top == '$' && *lookahead == '\0') {
            printf("Input successfully parsed!\n");
            break; 
        }

        if (top >= 'A' && top <= 'Z') {  
            int row = get_non_terminal_index(top);
            int col = get_terminal_index(*lookahead);  

            printf("Accessing parse table at row (non-terminal '%c'): %d, column (terminal '%c'): %d\n",
                   top, row, *lookahead, col);

            if (row == -1 || col == -1) {
                printf("Error: Invalid input or non-terminal.\n");
                break;  
            }

            int production_index = parse_table[row][col];
            if (production_index == -1) {
                printf("Error: No matching production found for input '%c'.\n", *lookahead);
                break;  
            }

            Production prod = productions[production_index];
            printf("Using production: %c → %s\n", prod.lhs, prod.rhs);

            // epsilon handling
            if (production_index == 3 || production_index == 7 || production_index == 15) {
                printf("Handling epsilon transition (index %d).\n", production_index);
                if (curr != NULL) {
                    // ereate an epsilon node
                    TREE epsilon_node = new_node('e');
                    set_LMC(curr, epsilon_node);
                    // move curr to parent
                    curr = get_parent(curr);
                } else {
                    printf("Error: curr is NULL during epsilon handling.\n");
                    break;
                }
                continue;  
            }

            // push symbols onto the stack in reverse order
            for (int i = strlen(prod.rhs) - 1; i >= 0; i--) {
                printf("Pushing %c onto stack\n", prod.rhs[i]);
                push(stack, prod.rhs[i]);
                print_stack(stack);
            }

            // create tree nodes for RHS symbols
            TREE prev_node = NULL;
            for (int i = 0; i < strlen(prod.rhs); i++) {
                TREE node = new_node(prod.rhs[i]);
                node->parent = curr; 
                if (prev_node == NULL) {
                    if (curr != NULL) {
                        set_LMC(curr, node);
                    } else {
                        printf("Error: curr is NULL when setting left-most child.\n");
                        break;
                    }
                } else {
                    set_RS(prev_node, node);
                }
                prev_node = node;
            }

            // move curr to the left-most child
            if (curr != NULL) {
                curr = get_LMC(curr);
            } else {
                printf("Error: curr is NULL when moving to left-most child.\n");
                break;
            }

        } else if (top == *lookahead) {  
            printf("Matched terminal: %c\n", *lookahead);
            lookahead++;  
            if (curr != NULL) {
                // move curr to parent after matching a terminal
                curr = get_parent(curr);
            } else {
                printf("Error: curr is NULL when moving to parent after matching terminal.\n");
                break;
            }
        } else {
            printf("Error: Terminal mismatch. Expected '%c' but got '%c'.\n", top, *lookahead);
            break;  
        }
    }

    free(productions);  

    if (*lookahead == '\0' && is_empty(stack)) {
        printf("Parsing complete with success!\n");
        return root;
    } else {
        printf("Parsing incomplete or stack/input mismatch.\n");
        return NULL;
    }
}
