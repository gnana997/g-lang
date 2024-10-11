#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the types of tokens
typedef enum {
    INT,
    KEYWORD,
    SEPARATOR,
    END_OF_TOKENS,
} TokenType;

// Define the structure of a token
typedef struct {
    TokenType type;
    char *value;
} Token;

// Function to print a token
// Arguments:
// - token: The token to be printed
// Returns: void
void print_token(Token token) {
    printf("TOKEN VALUE: ");
    for (int i = 0; token.value[i] != '\0'; i++) {
        printf("%c", token.value[i]);
    }
    if (token.type == INT) {
        printf(" TOKEN TYPE: INT\n");
    }
    if (token.type == KEYWORD) {
        printf(" TOKEN TYPE: KEYWORD\n");
    }
    if (token.type == SEPARATOR) {
        printf(" TOKEN TYPE: SEPARATOR\n");
    }
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
    int dig = isdigit(current[*current_index]);

    printf("is digit: %d | is end of line: %d\n", dig,
                 current[*current_index] != '\0');

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
    char *buffer = 0;

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = malloc(sizeof(char) * length);

    // Read the file into the buffer
    fread(buffer, 1, length, file);
    fclose(file);

    buffer[length + 1] = '\0';
    char *current = malloc(sizeof(char) * length + 1);
    current = buffer;

    int current_index = 0;
    Token *tokens = malloc(sizeof(Token) * 1024);
    tokens_index = 0;

    // Loop through the buffer and generate tokens
    while (current[current_index] != '\0') {
        Token *token = malloc(sizeof(Token)); // Allocate memory for token
        printf("current index %d\n", current_index);
        if (current[current_index] == ';') {
            token->value = malloc(sizeof(char) * 2); // Allocate memory for value
            token->value[0] = current[current_index];
            token->value[1] = '\0';
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (current[current_index] == '(') {
            token->value = malloc(sizeof(char) * 2); // Allocate memory for value
            token->value[0] = current[current_index];
            token->value[1] = '\0';
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (current[current_index] == ')') {
            token->value = malloc(sizeof(char) * 2); // Allocate memory for value
            token->value[0] = current[current_index];
            token->value[1] = '\0';
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if (isdigit(current[current_index])) {
            token = generate_number(current, &current_index);
            printf("TOKEN VALUE: %s\n", token->value);
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        } else if (isalpha(current[current_index])) {
            token = generate_keyword(current, &current_index);
            print_token(*token);
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        }
        free(token);
        current_index++;
    }

    // Mark the end of tokens
    tokens[tokens_index].value = NULL;
    tokens[tokens_index].type = END_OF_TOKENS;
    return tokens;
}