#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct Node {
    char *value;
    TokenType type;
    struct Node *right;
    struct Node *left;
} Node;

void print_tree(Node *root, int indenter, char *side);
void print_errors(char *message);
Node *init_node(Node *node, char *value, TokenType type);
Token *parse(Token *tokens);

#endif