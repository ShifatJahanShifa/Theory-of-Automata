#include<bits/stdc++.h>
using namespace std;


int stateNumber;
int alphabetNumber;
int numOfFinalStates;
char finalStates[100];
int transitionTable[100][100];
char distinguishingTable[100][100];
set<int>stFinal;


int arr[100][100];
int check[100];
void put(int i)
{
    for(int j=0; j<stateNumber; j++)
    {
        if(arr[i][j]==1 and check[j]==-1)
        {
            check[j]=i;
            put(j);
        }
    }
}

void minimization()
{
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
        {
            if(stFinal.count(i) and stFinal.count(j)==0)
                distinguishingTable[i][j]='X';
            else if(stFinal.count(j) and stFinal.count(i)==0)
                distinguishingTable[i][j]='X';
            else
                distinguishingTable[i][j]='=';

        }
    }

    bool ok;
    while(1)
    {
        ok=false;
        for(int i=1; i<stateNumber; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(distinguishingTable[i][j]=='X')
                    continue;
                int p1,p2;
                p1=transitionTable[i][0];
                p2=transitionTable[j][0];

                if(distinguishingTable[p1][p2]=='X' or distinguishingTable[p2][p1]=='X')
                {
                    distinguishingTable[i][j]='X';

                    ok=true;
                    continue;
                }
                p1=transitionTable[i][1];
                p2=transitionTable[j][1];

                if(distinguishingTable[p1][p2]=='X' or distinguishingTable[p2][p1]=='X')
                {
                    distinguishingTable[i][j]='X';
                    ok=true;
                    continue;
                }
            }
        }
        if(!ok)
            break;
    }

    vector<vector<int>>equivalentStates(100);

    for(int i=0; i<=stateNumber; i++)
    {
        for(int j=0; j<=stateNumber; j++)
        {
            arr[i][j]=0;
        }
    }

    int k=0;
    puts("");
    for(int i=1; i<stateNumber; i++)
    {
        printf("%c ",i+'A');
        for(int j=0; j<i; j++)
        {
            cout<<distinguishingTable[i][j]<<" ";
            if(distinguishingTable[i][j]=='=')
            {
                equivalentStates[k].push_back(j);
                equivalentStates[k].push_back(i);
                k++;
                arr[i][j]=1;
                arr[j][i]=1;
            }
        }
        puts("");
    }

    cout<<"  ";
    for(int i=0;i<stateNumber-1;i++)
    {
        printf("%c ",i+'A');
    }

    puts("\nequivalent states are:");

    for(int i=0; i<stateNumber; i++)
    {
        for(int j=0; j<equivalentStates[i].size(); j++)
        {
            if(j+1==equivalentStates[i].size())
                printf("%c\n",equivalentStates[i][j]+'A');
            else
                printf("%c = ",equivalentStates[i][j]+'A');
        }
    }

    for(int i=0; i<stateNumber; i++)
        check[i]=-1;
    for(int i=0; i<stateNumber; i++)
    {
        if(check[i]==-1)
            check[i]=i;
        put(i);
    }

    map<int,vector<int>>mp;

    for(int i=0; i<stateNumber; i++)
    {
        mp[check[i]].push_back(i);
    }

    puts("Minimized DFA: ");
    for(auto it:mp)
    {
        for(int i=0; i<it.second.size(); i++)
        {
            printf("%c",it.second[i]+'A');
        }
        cout<<" : (0)-> ";

        int mark[stateNumber]={0};
        for(int i=0; i<it.second.size(); i++)
        {
            int t=it.second[i];
            int f;
            f=transitionTable[t][0];
            if(mark[f]==0)
            {
                printf("%c",transitionTable[t][0]+'A');
                mark[f]=1;
            }
        }

        cout<<"  (1)-> ";
        int mark1[stateNumber]={0};

        for(int i=0; i<it.second.size(); i++)
        {
            int t=it.second[i];
            int f;
            f=transitionTable[t][1];
            if(mark1[t]==0)
            {
                printf("%c",transitionTable[t][1]+'A');
                mark1[f]=1;
            }
        }
        puts("");
    }
}


int main()
{
    freopen("dfatable.txt","r",stdin);
    puts("enter the number of states");
    cin>>stateNumber;

    char states[stateNumber];
    getchar();
    puts("enter the states");
    for(int i=0; i<stateNumber; i++)
    {
        cin>>states[i];
        getchar();
    }

    puts("enter the number of alphabet");
    cin>>alphabetNumber;

    int alphabets[alphabetNumber];
    puts("enter the alphabets");
    for(int i=0; i<alphabetNumber; i++)
    {
        cin>>alphabets[i];
    }

    puts("enter the start symbol");
    getchar();
    char startSymbol;
    cin>>startSymbol;

    puts("enter the number of Final states");
    cin>>numOfFinalStates;

    puts("enter the final states");
    getchar();
    for(int i=0; i<numOfFinalStates; i++)
    {
        cin>>finalStates[i];
        char ch=finalStates[i];
        int t=ch-'A';
        stFinal.insert(t);
    }

    puts("enter the transition table");
    getchar();
    for(int i=0; i<stateNumber; i++)
    {
        for(int j=0; j<alphabetNumber; j++)
        {
            char ch;
            cin>>ch;
            transitionTable[i][j]=ch-'A';
            getchar();
        }
    }

    minimization();

}
