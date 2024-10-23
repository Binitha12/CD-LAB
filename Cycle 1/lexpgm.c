#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_KEYWORDS 3

// List of keywords for the lexical analyzer
const char *keywords[MAX_KEYWORDS] = {"int", "return", "if"};

// Function to check if a string is a keyword
int isKeyword(const char *str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;  // It's a keyword
        }
    }
    return 0;  // Not a keyword
}

// Function to check if a character is an operator
int isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>') {
        return 1;  // It's an operator
    }
    return 0;  // Not an operator
}

// Function to recognize tokens from input string
void analyze(char *input) {
    int i = 0;

    while (input[i] != '\0') {
        // Skip whitespace
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // If it's a letter, it could be a keyword or an identifier
        if (isalpha(input[i])) {
            char buffer[100];
            int j = 0;

            // Capture the whole word (identifier/keyword)
            while (isalnum(input[i])) {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';  // Null terminate the string

            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
        }

        // If it's a digit, recognize it as a number
        else if (isdigit(input[i])) {
            char number[100];
            int j = 0;

            // Capture the full number (including decimals)
            while (isdigit(input[i]) || input[i] == '.') {
                number[j++] = input[i++];
            }
            number[j] = '\0';

            printf("Number: %s\n", number);
        }

        // If it's an operator
        else if (isOperator(input[i])) {
            printf("Operator: %c\n", input[i]);
            i++;  // Move to the next character
        }

        // Handle unrecognized characters
        else {
            printf("Unrecognized character: %c\n", input[i]);
            i++;
        }
    }
}

int main() {
    char input[100];

    // Get input from the user
    printf("Enter the input: ");
    fgets(input, 100, stdin);

    // Call lexical analyzer function
    analyze(input);

    return 0;
}
