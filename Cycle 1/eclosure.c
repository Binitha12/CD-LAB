 #include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26

// Function to calculate ε-closure of a state
void epsilonClosure(int state, int arr[MAX_STATES][MAX_ALPHABET + 1], int closure[MAX_STATES], int visited[MAX_STATES]) {
    if (visited[state]) return;
    visited[state] = 1;  // Mark the state as visited
    closure[state] = 1;   // Add this state to its own closure

    // Check all ε-transitions (using 'e' => index 26)
    int epsilon_index = 'e' - 'a';
    if (arr[state][epsilon_index] != -1) {
        epsilonClosure(arr[state][epsilon_index], arr, closure, visited);
    }
}

int main() {
    int n = 26;  // Alphabet size (a-z + epsilon as 'e')
    int m;  // Number of states
    printf("Enter the number of states in the NFA: ");
    scanf("%d", &m);

    int arr[MAX_STATES][MAX_ALPHABET + 1];  // NFA transition table (extra column for epsilon)
    
    // Initialize the transition table with -1 (no transitions)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            arr[i][j] = -1;
        }
    }

    int transitions;
    printf("Enter the number of transitions: ");
    scanf("%d", &transitions);

    printf("Enter the transitions in the format: state alphabet state\n");
    for (int i = 0; i < transitions; i++) {
        int from_state, to_state;
        char alphabet;
        scanf("%d %c %d", &from_state, &alphabet, &to_state);
        arr[from_state][alphabet - 'a'] = to_state;  // Store transition (convert alphabet to index)
    }

    // Calculate ε-closure for each state
    for (int i = 0; i < m; i++) {
        int closure[MAX_STATES] = {0};  // To store the ε-closure of the current state
        int visited[MAX_STATES] = {0};  // To track visited states during DFS

        epsilonClosure(i, arr, closure, visited);

        // Print the ε-closure of the current state
        printf("ε-closure of state %d: { ", i);
        for (int j = 0; j < m; j++) {
            if (closure[j]) {
                printf("%d ", j);
            }
        }
        printf("}\n");
    }

    return 0;
}
