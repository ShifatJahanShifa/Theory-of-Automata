#include<bits/stdc++.h>
using namespace std;

struct trans
{
    char f0[5];
    int n0,n1;
    char f1[5];
};

int main()
{
    freopen("nfa.txt","r",stdin);
    puts("welcome to nfa building");
    puts("enter the number of states");
    int stateNumber;
    scanf("%d",&stateNumber);
    getchar();
    struct trans delF[stateNumber];
    char states[stateNumber];
    puts("enter the states");
    for(int i=0; i<stateNumber; i++)
    {
        scanf("%c",&states[i]);
        getchar();
    }
    puts("enter the number of alphabet");
    int alphaNum;
    scanf("%d",&alphaNum);
    int alpha[alphaNum];
    for(int i=0; i<alphaNum; i++)
    {
        scanf("%d",&alpha[i]);
    }
    puts("start state: ");
    char startState;
    getchar();
    scanf("%c",&startState);
    puts("enter the number of final state");
    int finalNum;
    scanf("%d",&finalNum);
    getchar();
    puts("enter the final states");
    char finalState[finalNum];
    for(int i=0; i<finalNum; i++)
    {
        scanf("%c",&finalState[i]);
        getchar();
    }

    /// initialize
    for(int i=0; i<stateNumber; i++)
    {
        for(int j=0; j<5; j++)
        {
            delF[i].f0[j]='-';
            delF[i].f1[j]='-';
        }
    }

    puts("input the transition table");
    for(int i=0; i<stateNumber; i++)
    {
        puts("for 0: ");
        scanf("%d",&delF[i].n0);
        getchar();
        for(int j=0; j<delF[i].n0; j++)
        {
            char ch;
            scanf("%c",&ch);
            delF[i].f0[j]=ch;
        }
        puts("for 1: ");
        scanf("%d",&delF[i].n1);
        getchar();
        for(int j=0; j<delF[i].n1; j++)
        {
            char ch;
            scanf("%c",&ch);
            delF[i].f1[j]=ch;
        }
    }
    getchar();

    /// show the transition table
    puts("the table is:");
    for(int i=0; i<stateNumber; i++)
    {
        printf("%c : 0-{",(i+97));
        for(int j=0; j<delF[i].n0; j++)
        {
            cout<<delF[i].f0[j]<<",";
        }
        cout<<"} 1: {";
        for(int j=0; j<delF[i].n1; j++)
        {
            cout<<delF[i].f1[j]<<",";
        }
        puts("}");
    }
    puts("enter the string");
    string s;
    cin>>s;
    bool ok=false;

    /// processing
    char curS=startState,nowS;
    int cnt=0;
    for(int i=0; i<s.size(); i++)
    {
        char ch;
        ch=s[i];
        if(ch=='0')
        {
            curS=curS;
        }
        else
        {
            /// checking
            if((s.size()-i)>=3)
            {
                if(s[i]=='1' and s[i+1]=='1' and s[i+2]=='1')
                {
                    puts("f");
                    ok=true;
                }
            }
            if(!ok)
            {
                curS=curS;
            }
            if(ok and cnt!=3)
            {
                curS=curS+1;
                cnt++;
            }
            if(ok)
            {
                curS=curS;
            }
        }
    }
    if(curS==finalState[0])
        puts("accepted");
    else
        puts("not accepted");
}


//

