#include <stdio.h>
#include <stdlib.h>


void getEclosure(int transition_table[100][26],int state,int closure[100],int vis[100])
{

if(vis[state]) return ;
vis[state]=1;
closure[state]=1;
int e='e'-'a';
if(transition_table[state][e]!=-1)
{
    getEclosure(transition_table,transition_table[state][e],closure,vis);
}

}

int main()
{

    int n;
    printf("Enter No of states ");
    scanf("%d",&n);
    int al=26;
    int transition_table[n][26];

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<26;j++)
        transition_table[i][j]=-1;
    }
    int t;
    int r,c;
    char ch;
    printf("Enter no of transitions");
    scanf("%d",&t);
    printf("Enter as from alphabet to");
    for(int i=0;i<t;i++)
    {
        scanf(" %d %c %d",&r,&ch,&c);
        transition_table[r][ch-'a']=c;
    }

//calculate e_closure for each state;

for(int i=0;i<n;i++)
{

int closure[100]={0};
int vis[100]={0};

getEclosure(transition_table,i,closure,vis);

printf("Eclosure of state { q%d }",i);
for(int j=0;j<n;j++)
{
    if(closure[j]!=0) printf("%d",j);
}
printf("\n");





}




}