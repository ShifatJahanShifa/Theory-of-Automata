#include<bits/stdc++.h>
using namespace std;

struct trans
{
    char f0[5];
    int n0,n1;
    char f1[5];
};

struct DFA
{
    string St,s0,s1;
    bool ok;
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
            if(j+1==delF[i].n0)
                cout<<delF[i].f0[j];
            else
                cout<<delF[i].f0[j]<<",";
        }
        cout<<"} 1-{";
        for(int j=0; j<delF[i].n1; j++)
        {
            if(j+1==delF[i].n1)
                cout<<delF[i].f1[j];
            else
                cout<<delF[i].f1[j]<<",";
        }
        puts("}");
    }

    puts("enter the string");
    string s;
    cin>>s;
    bool ok=false;


    /// processing
    set<char>curS;
    curS.insert(startState);

    int cnt=0;
    for(int i=0; i<s.size(); i++)
    {
        cnt++;
        char ch;
        ch=s[i];

        if(ch=='0')
        {
            set<char>temp;
            set<char>deleted;
            for(auto it=curS.begin(); it!=curS.end(); it++)
            {
                char take=*it;
                int t=take-'a';
                bool p=true;

                for(int j=0; j<delF[t].n0; j++)
                {
                    temp.insert(delF[t].f0[j]);
                    p=false;
                }
                if(p)
                {
                    deleted.insert(take);
                }
            }

            curS.insert(temp.begin(),temp.end());

            for(auto it=deleted.begin();it!=deleted.end();it++)
            {
                char put=*it;
                curS.erase(put);
            }

            printf("for %c -> states are { ",ch);
            for(auto it=curS.begin(); it!=curS.end(); it++)
            {
                cout<<*it<<", ";
            }
            puts("}");
        }
        else
        {
            set<char>temp;
            set<char>deleted;
            for(auto it=curS.begin(); it!=curS.end(); it++)
            {
                char take=*it;
                int t=take-'a';
                bool p=true;
                for(int j=0; j<delF[t].n1; j++)
                {
                    temp.insert(delF[t].f1[j]);
                    p=false;
                }
                if(p)
                {
                    deleted.insert(take);
                }
            }

            curS.insert(temp.begin(),temp.end());

            for(auto it=deleted.begin();it!=deleted.end();it++)
            {
                char put=*it;
                curS.erase(put);
            }

            printf("for %c -> states are { ",ch);
            for(auto it=curS.begin(); it!=curS.end(); it++)
            {
                cout<<*it<<", ";
            }
            puts("}");
        }
    }

    if(curS.count(finalState[0])==0)
        puts("not accepted");
    else
    {
        puts("accepted");

        /* cout<<"("<<startState<<","<<s[0]<<")-->"<<res[0]<<"\n";
         for(int i=1;i<s.size();i++)
         {
             cout<<"("<<res[i-1]<<","<<s[i]<<")-->"<<res[i]<<"\n";
         }*/
        puts("");
        /// nfa to dfa transition
        struct DFA dfa[20];
        for(int i=0; i<20; i++)
        {
            dfa[i].ok=true;
        }

        set<string>fs;
        string t;
        t+=startState;
        dfa[0].St+=startState;
        fs.insert(t);

        for(int i=0; i<delF[0].n0; i++)
            dfa[0].s0+=delF[0].f0[i];

        for(int i=0; i<delF[0].n1; i++)
            dfa[0].s1+=delF[0].f1[i];


        string take;
        take+=dfa[0].s1;
        int k=1;
        int endV=1;
        while(endV)
        {
            string temp,temp1;
            dfa[k].St+=take;
            for(int j=0; j<take.size(); j++)
            {
                for(int i=0; i<delF[take[j]-'a'].n0; i++)
                {
                    temp1+=delF[take[j]-'a'].f0[i];
                }

                for(int i=0; i<delF[take[j]-'a'].n1; i++)
                {
                    temp+=delF[take[j]-'a'].f1[i];
                }

            }

            set<char>st(temp1.begin(),temp1.end());
            for(auto i=st.begin(); i!=st.end(); i++)
            {
                dfa[k].s0+=*i;
            }

            set<char>st1(temp.begin(),temp.end());
            for(auto i=st1.begin(); i!=st1.end(); i++)
            {
                dfa[k].s1+=*i;
            }

            endV=0;
            if(fs.count(dfa[k].s0)==0)
            {
                take.clear();
                take+=dfa[k].s0;
                endV=1;
                fs.insert(dfa[k].s0);
            }

            if(fs.count(dfa[k].s1)==0)
            {
                take.clear();
                take+=dfa[k].s1;
                endV=1;
                fs.insert(dfa[k].s1);
            }
            k++;
        }

        for(int i=0; i<stateNumber; i++)
        {
            string b;
            b+=(i+'a');
            if(fs.count(b)==0)
            {
                for(int j=0; j<delF[i].n0; j++)
                    dfa[k].s0+=delF[i].f0[j];

                for(int j=0; j<delF[i].n1; j++)
                    dfa[k].s1+=delF[i].f1[j];

                dfa[k].St+=b;
                k++;
            }
        }

        for(int i=0; i<k; i++)
            cout<<dfa[i].St<<"  : 0-{"<<dfa[i].s0<<"}   , 1-{"<<dfa[i].s1<<"}"<<"\n";
    }
}
