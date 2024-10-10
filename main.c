#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN,
} SeperatorKind;

typedef enum {
    EXIT,
} KeywordKind;

typedef enum {
    INT,
} LiteralKind;

typedef struct {
    SeperatorKind type;
} TokenSeperator;

typedef struct {
    KeywordKind type;
} TokenKeyword;

typedef struct {
    LiteralKind type;
    int value;
} TokenLiteral;

TokenLiteral generateNumber(char current, FILE *file) {
    TokenLiteral token;
    token.type = INT;

    int value = 0;
    while(isdigit(current) && current != EOF) {
        value = value * 10 + (current - '0');
        current = fgetc(file);
    }
    token.value = value;
    ungetc(current, file);
    return token;
}

TokenKeyword *generateKeyword(char current, FILE *file) {
    TokenKeyword *token = malloc(sizeof(TokenKeyword));
    char *keyword = malloc(sizeof(char) * 4);
    int i = 0;

    while(isalpha(current) && current != EOF) {
        keyword[i] = current;
        i++;
        current = fgetc(file);
    }

    if (strcmp(keyword, "exit") == 0) {
        token->type = EXIT;
    }

    free(keyword);
    ungetc(current, file);
    return token;
}

void lexer(FILE *file) {
   char current = fgetc(file);
    while(current != EOF) {
        if (current == ';') {
            printf("SEMI\n");
        } else if (current == '(') {
            printf("OPEN_PAREN\n");
        } else if (current == ')') {
            printf("CLOSE_PAREN\n");
        } else if (isdigit(current)) {
            TokenLiteral test_token = generateNumber(current, file);
            printf("LITERAL %d\n", test_token.value);
        } else if (isalpha(current)) {
            TokenKeyword *test_token = generateKeyword(current, file);
            if (test_token->type == EXIT) {
                printf("EXIT\n");
            }
            free(test_token);
        }
        current = fgetc(file);
    } 
}

int main() {
    FILE *file;
    file = fopen("test.unn", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }

    lexer(file);
    fclose(file);
    return 0;
}
