#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 20

// Function to find FIRST of a given symbol
void findFirst(char grammar[MAX_RULES][MAX_SYMBOLS], char first[MAX_RULES][MAX_SYMBOLS], int n, char symbol) {
    for (int i = 0; i < n; i++) {
        if (grammar[i][0] == symbol) {
            for (int j = 3; j < strlen(grammar[i]); j++) {
                if (isupper(grammar[i][j])) {
                    findFirst(grammar, first, n, grammar[i][j]);
                } else {
                    first[symbol - 'A'][0] = grammar[i][j];
                    break;
                }
            }
        }
    }
}

// Function to find FOLLOW of a given symbol
void findFollow(char grammar[MAX_RULES][MAX_SYMBOLS], char follow[MAX_RULES][MAX_SYMBOLS], int n, char symbol) {
    for (int i = 0; i < n; i++) {
        for (int j = 3; j < strlen(grammar[i]); j++) {
            if (grammar[i][j] == symbol) {
                if (j + 1 < strlen(grammar[i])) {
                    if (islower(grammar[i][j + 1])) {
                        follow[symbol - 'A'][0] = grammar[i][j + 1];
                    } else {
                        findFollow(grammar, follow, n, grammar[i][j + 1]);
                    }
                } else if (grammar[i][0] != symbol) {
                    findFollow(grammar, follow, n, grammar[i][0]);
                }
            }
        }
    }
}

int main() {
    int n;
    char grammar[MAX_RULES][MAX_SYMBOLS];
    char first[MAX_RULES][MAX_SYMBOLS] = {{0}};
    char follow[MAX_RULES][MAX_SYMBOLS] = {{0}};

    // Input the number of rules and the grammar
    printf("Enter number of production rules: ");
    scanf("%d", &n);
    printf("Enter grammar in the format (e.g., A->aB or A->a):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", grammar[i]);
    }

    // Calculate First sets for each symbol
    for (int i = 0; i < n; i++) {
        findFirst(grammar, first, n, grammar[i][0]);
    }

    // Calculate Follow sets for each symbol
    for (int i = 0; i < n; i++) {
        findFollow(grammar, follow, n, grammar[i][0]);
    }

    // Output the First sets
    printf("\nFirst sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = {", grammar[i][0]);
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            if (first[grammar[i][0] - 'A'][j] != 0) {
                printf(" %c", first[grammar[i][0] - 'A'][j]);
            }
        }
        printf(" }\n");
    }

    // Output the Follow sets
    printf("\nFollow sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = {", grammar[i][0]);
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            if (follow[grammar[i][0] - 'A'][j] != 0) {
                printf(" %c", follow[grammar[i][0] - 'A'][j]);
            }
        }
        printf(" }\n");
    }

    return 0;
}
