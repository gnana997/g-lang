#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("Error: correct syntax: %s <filename.unn>\n", argv[0]);
        exit(1);
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if (!file) {
        printf("Error: could not open file\n");
        exit(1);
    }

    Token *tokens = lexer(file);

    for (int i = 0; tokens[i].type != END_OF_TOKENS; i++) {
        print_token(tokens[i]);
    }

    parse(tokens);

}