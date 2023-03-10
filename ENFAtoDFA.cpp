#include<bits/stdc++.h>
using namespace std;

struct enfa
{
    int eNum;
    int num0;
    int num1;

    int statesE[50];
    int states0[50];
    int states1[50];
} ENFA[100];

struct dfa
{
    set<char>for0;
    set<char>for1;
    set<char>dfaS;
} DFA[100];

set<string>validity;

void makeDfa(string s);

vector<set<char>>vs(100);

int k;

int main()
{
    freopen("trins.txt","r",stdin);
    puts("enter the number of states");
    int stateNumber;
    cin>>stateNumber;
    getchar();

    puts("enter the states");
    char stateArr[stateNumber];
    for(int i=0; i<stateNumber; i++)
    {
        cin>>stateArr[i];
        getchar();
    }

    puts("enter the number of input symbol");
    int symbolNumber;
    cin>>symbolNumber;

    puts("enter the input symbol");
    int inputArr[symbolNumber];
    for(int i=0; i<symbolNumber; i++)
    {
        cin>>inputArr[i];
    }


    puts("enter the transition table");

    for(int j=0; j<stateNumber; j++)
    {
        cout<<"enter the number of states for epsilon for states ";
        printf("( %c ):\n",j+'a');

        cin>>ENFA[j].eNum;
        getchar();

        if(ENFA[j].eNum==0)
        {
            ENFA[j].statesE[0]='-';
        }
        else
        {
            puts("enter the states");
            char temp;
            for(int i=0; i<ENFA[j].eNum; i++)
            {
                cin>>temp;
                ENFA[j].statesE[i]=temp-'a';
                getchar();
            }
        }

        cout<<"enter the number of states for zero for states";
        printf("( %c ):\n",j+'a');

        cin>>ENFA[j].num0;
        getchar();

        if(ENFA[j].num0==0)
        {
            ENFA[j].states0[0]='-';
        }
        else
        {
            puts("enter the states");
            char temp;
            for(int i=0; i<ENFA[j].num0; i++)
            {
                cin>>temp;
                ENFA[j].states0[i]=temp-'a';
                getchar();
            }
        }

        cout<<"enter the number of states for one for states ";
        printf("( %c ):\n",j+'a');

        cin>>ENFA[j].num1;
        getchar();
        if(ENFA[j].num1==0)
        {
            ENFA[j].states1[0]='-';
        }
        else
        {

            puts("enter the states");
            char temp;
            for(int i=0; i<ENFA[j].num1; i++)
            {
                cin>>temp;
                ENFA[j].states1[i]=temp-'a';
                getchar();
            }
        }
    }


    /** the transition table for enfa **/
    puts("here is the transition table");
    for(int j=0; j<stateNumber; j++)
    {
        printf("%c    ",j+'a');

        cout<<"e-> {";
        for(int i=0; i<ENFA[j].eNum; i++)
        {
            printf("%c, ",ENFA[j].statesE[i]+'a');
        }
        cout<<"}    0-> {";

        for(int i=0; i<ENFA[j].num0; i++)
        {
            printf("%c, ",ENFA[j].states0[i]+'a');
        }
        cout<<"}    1-> {";

        for(int i=0; i<ENFA[j].num1; i++)
        {
            printf("%c, ",ENFA[j].states1[i]+'a');
        }
        cout<<"}\n";
    }
    puts("");


    /** part for epsilon **/

    /* for individual */
    for(int i=0; i<stateNumber; i++)
    {
        int loop=ENFA[i].eNum;
        char ch;
        int temp;
        for(int j=0; j<loop; j++)
        {
            temp=ENFA[i].statesE[j];
            ch=temp+'a';
            vs[i].insert(ch);
        }
        temp=i;
        ch=temp+'a';
        vs[i].insert(ch);
    }

    for(int i=0; i<stateNumber; i++)
    {
        printf("for %c,  ->",i+'a');
        for(auto it=vs[i].begin(); it!=vs[i].end(); it++)
        {
            cout<<*it<<" ";
        }
        puts("");
    }

    /* refining */
    for(int i=0; i<stateNumber; i++)
    {
        int loop=vs[i].size();
        char ch;
        int temp;
        for(auto it=vs[i].begin(); it!=vs[i].end(); it++)
        {
            temp=*it-'a';
            vs[i].insert(vs[temp].begin(),vs[temp].end());
        }
    }

    /* checking e closure */
    puts("here the e-closure");
    for(int i=0; i<stateNumber; i++)
    {
        printf("for %c,  ->{",i+'a');
        for(auto it=vs[i].begin(); it!=vs[i].end(); it++)
        {
            cout<<*it<<", ";
        }
        puts("}");
    }

    puts("");

    /** dfa constructing **/
    int stateDfa=pow(2,stateNumber);

   // DFA[0].dfaS.insert(vs[0].begin(),vs[0].end());

    string s;
    for(auto it=vs[0].begin(); it!=vs[0].end(); it++)
    {
        s+=*it;
    }
    validity.insert(s);

    k=0;

    makeDfa(s);

    puts("transition table for dfa");

    for(int i=0; i<k; i++)
    {
        cout<<"{ ";
        for(auto it=DFA[i].dfaS.begin(); it!=DFA[i].dfaS.end(); it++)
        {
            cout<<*it<<", ";
        }

        cout<<"}  0-> { ";

        for(auto it=DFA[i].for0.begin(); it!=DFA[i].for0.end(); it++)
        {
            cout<<*it<<", ";
        }

        cout<<"}  1-> { ";

        for(auto it=DFA[i].for1.begin(); it!=DFA[i].for1.end(); it++)
        {
            cout<<*it<<", ";
        }

        puts("}");
    }
    puts("");

}

void makeDfa(string s)
{
    string temp;
    string temp1;
    string hold;

    DFA[k].dfaS.insert(s.begin(),s.end());

    for(int i=0; i<s.size(); i++)
    {
        char c=s[i];
        int take=c-'a';

        for(int j=0; j<ENFA[take].num0; j++)
        {
            int take2=ENFA[take].states0[j];
            DFA[k].for0.insert(vs[take2].begin(),vs[take2].end());
        }

        for(int j=0; j<ENFA[take].num1; j++)
        {
            int take2=ENFA[take].states1[j];
            DFA[k].for1.insert(vs[take2].begin(),vs[take2].end());
        }
    }

    for(auto it=DFA[k].for0.begin(); it!=DFA[k].for0.end(); it++)
    {
        temp+=*it;
    }

    for(auto it=DFA[k].for1.begin(); it!=DFA[k].for1.end(); it++)
    {
        temp1+=*it;
    }
    k++;

    if(validity.count(temp)==0 )
    {
        validity.insert(temp);
        hold=temp;

        makeDfa(hold);
    }

    if(validity.count(temp1)==0 )
    {
        validity.insert(temp1);
        hold=temp1;

        makeDfa(hold);
    }
}
