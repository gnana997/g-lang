## g-lang

# Building compiler for my language

This project is a simple compiler for a custom language called g-lang. The compiler is written in C and includes a lexer to tokenize the input source code.

## Project Structure

- `build.sh`: Shell script to compile the project using `gcc`.
- `lexer.c`: Contains the lexer implementation that tokenizes the input source code.
- `main.c`: Contains the main function and token generation functions.
- `test.unn`: Sample input file for testing the lexer.

## Building the Project

To build the project, run the following command:

```sh
./build.sh
```
This will compile main.c and generate an executable named main.

## Running the Lexer
To run the lexer on the sample input file test.unn, use the following command:

```sh
./main
```
The lexer will read the test.unn file and print the tokens to the console.

## Token Types
The lexer recognizes the following token types:

- SEMI: Semicolon (;)
- OPEN_PAREN: Open parenthesis (()
- CLOSE_PAREN: Close parenthesis ())
- LITERAL: Integer literals
- KEYWORD: Keywords (currently only exit is supported)
- Functions
- lexer(FILE *file): Tokenizes the input file.
- generateNumber(char current, FILE *file): Generates a token for integer literals.
- generateKeyword(char current, FILE *file): Generates a token for keywords.
- tokenTypeToString(KeywordKind type): Converts a keyword token type to a string.
