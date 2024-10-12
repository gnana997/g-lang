#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include <sys/_types/_null.h>
#include "lexer.h"

void print_tree(Node *root, int indenter, char *side) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < indenter; i++) {
        printf(" ");
    }
    
    printf("%s -> ", side);
    for (size_t i = 0; root->value[i] != '\0'; i++) {
        printf("%c", root->value[i]);
    }
    printf("\n");

    print_tree(root->left, indenter +1, "left");
    print_tree(root->right, indenter +1, "right");
}

void print_errors(char *message) {
    printf("Syntax Error: %s\n", message);
    exit(1);
}

Node *init_node(Node *node, char *value, TokenType type) {
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
    
    root = init_node(root, "PROGRAM", BEGINNING);
    
    Node *current = root;

    while(current_token->type != END_OF_TOKENS) {
        if (current == NULL) {
            break;
        }

        if (current == root) {
            //
        }

        switch (current_token->type) {
            case KEYWORD:
                if (strcmp(current_token->value, "EXIT") == 0) {
                    Node *exit_node = malloc(sizeof(Node));
                    exit_node = init_node(exit_node, current_token->value, KEYWORD);
                    root->right = exit_node;
                    current = exit_node;
                    current_token++;

                    if (current_token->type != END_OF_TOKENS && strcmp(current_token->value, "(") == 0) {
                        Node *open_paren = malloc(sizeof(Node));
                        open_paren = init_node(open_paren, current_token->value, SEPARATOR);
                        current->left = open_paren;
                        current_token++;
                        
                        if (current_token->type != END_OF_TOKENS && current_token->type == INT) {
                            Node *expr = malloc(sizeof(Node));
                            expr = init_node(expr, current_token->value, KEYWORD);
                            current->left->left = expr;
                            current_token++;

                            if (current_token->type != END_OF_TOKENS && strcmp(current_token->value, ")") == 0) {
                                Node *close_paren = malloc(sizeof(Node));
                                close_paren = init_node(close_paren, current_token->value, SEPARATOR);
                                current->left->right = close_paren;
                                current_token++;

                                if (current_token->type != END_OF_TOKENS && strcmp(current_token->value, ";") == 0) {
                                    Node *semi = malloc(sizeof(Node));
                                    semi = init_node(semi, current_token->value, END_OF_TOKENS);
                                    current->right = semi;
                                    current_token++;

                                } else {
                                    print_errors("Expected SEMICOLON");
                                    exit(1);
                                }
                            } else {
                                print_errors("Expected CLOSE PARAN");
                                exit(1);
                            }
                        } else {
                            print_errors("Expected INT");
                            exit(1);
                        }
                    } else {
                        print_errors("Expected OPEN PARAN");
                        exit(1);
                    }
                } else {
                    print_errors("Expected exit Keyword");
                    exit(1);
                }
                break;
                //
            case SEPARATOR:
                //
            case INT:
                //
            case END_OF_TOKENS:
                //
            case BEGINNING:
                //
            default:
                printf("Syntax Error: Unexpected token\n");
                exit(1);
        }
    }

    print_tree(root, 0, "root");

    return current_token;
}