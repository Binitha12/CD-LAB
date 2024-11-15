#include <stdio.h>
#include <string.h>

#define MAX 100

// Define precedence levels for operators
#define SHIFT 0
#define REDUCE 1
#define ACCEPT 2
#define ERROR 3

// Operator precedence table (simple version)
char precedenceTable[3][3] = {
    //  +    *    $
    { SHIFT, SHIFT, REDUCE }, // +
    { SHIFT, SHIFT, REDUCE }, // *
    { ACCEPT, ACCEPT, ACCEPT } // $
};

char operators[] = "+*$"; // List of operators
char stack[MAX];
int top = 0; // Top of the stack

// Function to get the precedence relation between two operators
int getPrecedence(char stackTop, char current) {
    int row = -1, col = -1;

    for (int i = 0; i < 3; i++) {
        if (operators[i] == stackTop) row = i;
        if (operators[i] == current) col = i;
    }

    if (row != -1 && col != -1) {
        return precedenceTable[row][col];
    }
    return ERROR; // Return ERROR if no relation found
}

// Function to parse the input string
void parse(char* input) {
    int i = 0; // Pointer for input string
    stack[top] = '$'; // Initialize stack with '$'

    printf("Stack\tInput\tAction\n");
    while (1) {
        // Print the stack and remaining input
        printf("%s\t", stack);
        for (int j = i; input[j] != '\0'; j++) printf("%c", input[j]);
        printf("\t");

        char stackTop = stack[top]; // Top of the stack
        char current = input[i];   // Current input character

        // Get precedence relation
        int relation = getPrecedence(stackTop, current);

        if (relation == SHIFT) {
            // Shift operation
            top++;
            stack[top] = current;
            i++;
            printf("Shift %c\n", current);
        } 
        else if (relation == REDUCE) {
            // Reduce operation: pop from stack and replace by 'E'
            if (top > 1) {
                stack[top - 1] = 'E'; // Replace with 'E' as a simplified result
                top--;
                printf("Reduce\n");
            }
            else {
                printf("Error\n");
                break;
            }
        } 
        else if (relation == ACCEPT) {
            // Check for acceptance condition
            if (stackTop == '$' && current == '\0' && top == 1 && stack[1] == 'E') {
                printf("Accepted\n");
                break;
            } else {
                printf("Error\n");
                break;
            }
        } 
        else {
            printf("Error\n");
            break;
        }
    }
}

int main() {
    char input[MAX];

    // User input: string should end with $
    printf("Enter the input string to parse (end with $): ");
    scanf("%s", input);
    strcat(input, "$"); // Add the end of string marker $

    parse(input);

    return 0;
}
