#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define ALPHABET_SIZE 26

// Function to compute epsilon-closure
void getEclosure(int table[10][10], int state, int closure[10], int vis[10]) {
    if (vis[state]) return;
    vis[state] = 1;
    closure[state] = 1;

    int e = 'e' - 'a';
    if (table[state][e] != -1) {
        getEclosure(table, table[state][e], closure, vis);
    }
}

// Convert ε-NFA to NFA
void enfa_to_nfa(int table[10][10], int n, int nfa[10][10]) {
    int closures[10][10] = {0};

    for (int i = 0; i < n; i++) {
        int vis[10] = {0};
        getEclosure(table, i, closures[i], vis);
    }

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 10; c++) {
            if (c == ('e' - 'a')) continue;
            for (int j = 0; j < n; j++) {
                if (closures[i][j] && table[j][c] != -1) {
                    for (int k = 0; k < n; k++) {
                        if (closures[table[j][c]][k]) {
                            nfa[i][c] = k;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    
    int n, t;
   int table[10][10];
   int nfa[10][10];
   for(int i=0;i<10;i++)
   {
    for(int j=0;j<10;j++)
    {
        table[i][j]=-1;
        nfa[i][j]=-1;
    }
   }
   
    printf("Enter the number of states and transitions: ");
    scanf("%d %d", &n, &t);

    printf("Enter transitions as 'from alphabet to':\n");
    for (int i = 0; i < t; i++) {
        int from, to;
        char ch;
        scanf("%d %c %d", &from, &ch, &to);
        table[from][ch - 'a'] = to;
    }

    enfa_to_nfa(table, n, nfa);

    printf("\nNFA Transition Table:\n");
    for (int i = 0; i < n; i++) {
        printf("q%d: ", i);
        for (int c = 0; c < 10; c++) {
            if (nfa[i][c] != -1) {
                printf("%c->q%d ", c + 'a', nfa[i][c]);
            }
        }
        printf("\n");
    }

    return 0;
}
