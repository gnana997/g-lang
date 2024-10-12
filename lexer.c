#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print a token
// Arguments:
// - token: The token to be printed
// Returns: void
void print_token(Token token) {
    printf("TOKEN VALUE: ");
    printf("'");
    for (int i = 0; token.value[i] != '\0'; i++) {
        printf("%c", token.value[i]);
    }
    printf("'");

    switch (token.type) {
        case INT:
            printf(" TOKEN TYPE: INT\n");
            break;
        case KEYWORD:
            printf(" TOKEN TYPE: KEYWORD\n");
            break;
        case SEPARATOR:
            printf(" TOKEN TYPE: SEPARATOR\n");
            break;
        case END_OF_TOKENS:
            printf(" TOKEN TYPE: END_OF_TOKENS\n");
            break;
        case BEGINNING:
            printf(" TOKEN TYPE: BEGINNING\n");
            break;
    }
}

Token *generate_seperator(char *current, int *current_index) {
    Token *token = malloc(sizeof(Token));
    token->type = SEPARATOR;
    token->value = malloc(sizeof(char) * 2);
    token->value[0] = current[*current_index];
    token->value[1] = '\0';
    return token;
}

// Function to generate a number token
// Arguments:
// - current: The current position in the input string
// - current_index: The index of the current character in the input string
// Returns: A pointer to the generated number token
Token *generate_number(char *current, int *current_index) {
    Token *token = malloc(sizeof(Token));
    token->type = INT;

    char *value = malloc(sizeof(char) * 8);
    int value_index = 0;

    // Read digits and form the number token
    while (isdigit(current[*current_index]) && current[*current_index] != '\0') {
        if (!isdigit(current[*current_index])) {
            break;
        }
        value[value_index] = current[*current_index];
        value_index++;
        *current_index += 1;
    }

    value[value_index] = '\0';

    token->value = value;
    return token;
}

// Function to generate a keyword token
// Arguments:
// - current: The current position in the input string
// - current_index: The index of the current character in the input string
// Returns: A pointer to the generated keyword token
Token *generate_keyword(char *current, int *current_index) {
    Token *token = malloc(sizeof(Token));
    char *keyword = malloc(sizeof(char) * 8);

    int keyword_index = 0;
    // Read alphabetic characters and form the keyword token
    while (isalpha(current[*current_index]) && current[*current_index] != '\0') {
        keyword[keyword_index] = current[*current_index];
        keyword_index++;
        *current_index += 1;
    }

    keyword[keyword_index] = '\0';
    if (strcmp(keyword, "exit") == 0) {
        token->type = KEYWORD;
        token->value = "EXIT";
    }

    return token;
}

size_t tokens_index;

// Function to perform lexical analysis on the input file
// Arguments:
// - file: The input file to be analyzed
// Returns: A pointer to the array of generated tokens
Token *lexer(FILE *file) {
    int length;
    char *current = 0;

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    current = malloc(sizeof(char) * length);
    // Read the file into the buffer
    fread(current, 1, length, file);

    fclose(file);

    current[length + 1] = '\0';

    int current_index = 0;
    Token *tokens = malloc(sizeof(Token) * length);
    tokens_index = 0;

    // Loop through the buffer and generate tokens
    while (current[current_index] != '\0') {
        Token *token = malloc(sizeof(Token)); // Allocate memory for token
        if (current[current_index] == ';') {
            token = generate_seperator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (current[current_index] == '(') {
            token = generate_seperator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (current[current_index] == ')') {
            token = generate_seperator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (isdigit(current[current_index])) {
            token = generate_number(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        } else if (isalpha(current[current_index])) {
            token = generate_keyword(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        } else if (current[current_index] == ' ' || current[current_index] == '\t' || current[current_index] == '\n') {
            continue;
        } else {
            printf("Invalid character: %c\n", current[current_index]);
            exit(1);
        }
        free(token);
        current_index++;
    }

    // Mark the end of tokens
    tokens[tokens_index].value = NULL;
    tokens[tokens_index].type = END_OF_TOKENS;
    return tokens;
}