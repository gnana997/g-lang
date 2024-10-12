#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include <sys/_types/_null.h>
#include "lexer.h"

typedef enum {
    INT_LIT,
    BEGINING,
    STATEMENT,
    SEPARATORS,
    END_OF_STATEMENT,
} NodeTypes;

typedef struct Node {
    char *value;
    NodeTypes type;
    struct Node *right;
    struct Node *left;
} Node;


void print_tree(Node *root) {
    if (root == NULL) {
        return;
    }

    // printf("Node Type: %d\n", root->type);
    for (size_t i = 0; root->value[i] != '\0'; i++) {
        printf("%c", root->value[i]);
    }
    printf("\n");

    print_tree(root->left);
    print_tree(root->right);
}

Node *init_node(Node *node, char *value, NodeTypes type) {
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char) * 2);
    node->value = value;
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    return node;
}


// TODO: Refactor the parser logic to improve readability and maintainability
// 1. Break down the parse function into smaller functions for each parsing step.
// 2. Use a switch-case statement to handle different token types.
// 3. Remove redundant malloc calls and simplify memory management.
// 4. Add error handling for unexpected tokens and memory allocation failures.
// 5. Ensure proper freeing of allocated memory to avoid memory leaks.
Token *parse(Token *tokens) {
    Token *current_token = &tokens[0];

    Node *root = malloc(sizeof(Node));
    
    root = init_node(root, "PROGRAM", BEGINING);
    
    Node *current = root;

    while(current_token->type != END_OF_TOKENS) {
        if (current == NULL) {
            break;
        }

        if (current == root) {
            //
        }

        if(current_token->type == KEYWORD && strcmp(current_token->value, "exit")) {
            Node *exit_node = malloc(sizeof(Node));
            exit_node = init_node(exit_node, current_token->value, STATEMENT);
            root->right = exit_node;
            current = exit_node;
            current_token++;

            if(current_token->type != SEPARATOR) {
                printf("Syntax Error: Expected ;\n");
                break;
            }

            Node *open_paren = malloc(sizeof(Node));
            open_paren = init_node(open_paren, current_token->value, SEPARATORS);
            current->left = open_paren;
            current_token++;

            Node *expr = malloc(sizeof(Node));
            expr = init_node(expr, current_token->value, STATEMENT);
            current->left->left = expr;
            current_token++;

            Node *close_paren = malloc(sizeof(Node));
            close_paren = init_node(close_paren, current_token->value, SEPARATORS);
            current->left->right = close_paren;
            current_token++;

            Node *semi = malloc(sizeof(Node));
            semi = init_node(semi, current_token->value, END_OF_STATEMENT);
            current->right = semi;
            break;
        }
        current_token++;
    }

    print_tree(root);

    return current_token;
}