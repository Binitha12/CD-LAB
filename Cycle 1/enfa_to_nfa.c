#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26

// Function to calculate ε-closure of a state
void epsilonClosure(int state, int arr[MAX_STATES][MAX_ALPHABET + 1], int closure[MAX_STATES], int visited[MAX_STATES]) {
    if (visited[state]) return;  // If already visited, return
    visited[state] = 1;          // Mark the state as visited
    closure[state] = 1;          // Add this state to its closure

    // Check ε-transitions (using 'e' as index 26)
    int epsilon_index = 'e' - 'a';  // Calculate the index for 'e'
    int next_state = arr[state][epsilon_index];
    while (next_state != -1) {  // While there are ε-transitions
        epsilonClosure(next_state, arr, closure, visited);
        next_state = arr[next_state][epsilon_index];  // Move to next ε-transition
    }
}

// Function to convert ε-NFA to NFA
void convertENFAtoNFA(int arr[MAX_STATES][MAX_ALPHABET + 1], int m, int nfa[MAX_STATES][MAX_ALPHABET], int nfaStates[]) {
    for (int i = 0; i < m; i++) {
        int closure[MAX_STATES] = {0};  // To store the ε-closure of the current state
        int visited[MAX_STATES] = {0};  // To track visited states during DFS

        // Calculate ε-closure for state i
        epsilonClosure(i, arr, closure, visited);

        // For each input character, find the reachable states
        for (int j = 0; j < MAX_ALPHABET; j++) {
            if (arr[i][j] != -1) {  // If there is a transition
                int next_state = arr[i][j];
                int closure_next[MAX_STATES] = {0};  // ε-closure of the next state
                int visited_next[MAX_STATES] = {0};
                epsilonClosure(next_state, arr, closure_next, visited_next);

                // Add all states in closure_next to nfa[i][j]
                for (int k = 0; k < MAX_STATES; k++) {
                    if (closure_next[k]) {
                        nfa[i][j] = k;
                        nfaStates[i] = 1;  // Mark that state i has transitions
                    }
                }
            }
        }
    }
}

int main() {
    int m;  // Number of states in ε-NFA
    printf("Enter the number of states in the ε-NFA: ");
    scanf("%d", &m);

    int arr[MAX_STATES][MAX_ALPHABET + 1];  // Transition table for ε-NFA (extra column for epsilon)
    
    // Initialize the transition table with -1 (no transitions)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= MAX_ALPHABET; j++) {
            arr[i][j] = -1;  // No transitions initially
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

    // NFA transition table
    int nfa[MAX_STATES][MAX_ALPHABET] = {0};  // NFA transition table
    int nfaStates[MAX_STATES] = {0};  // To track states with transitions

    // Convert ε-NFA to NFA
    convertENFAtoNFA(arr, m, nfa, nfaStates);

    // Print the NFA transitions
    printf("\nNFA Transitions:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < MAX_ALPHABET; j++) {
            if (nfaStates[i] && nfa[i][j]) {  // If state i has transitions
                printf("State %d -- %c --> State %d\n", i, 'a' + j, nfa[i][j]);
            }
        }
    }

    return 0;
}
