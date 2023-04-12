#include<bits/stdc++.h>
using namespace std;

const int Size=100;
int numberOfVariable;
set<char>variables;
int numberOfTerminal;
set<char>terminals;
int numberOfProduction;
map<char,vector<string>>mp;
set<char>st;
set<char>generates;

bool anyTerminal(char ch)
{
    auto v=mp[ch];

    for(int i=0; i<v.size(); i++)
    {
        bool ok=false;
        for(int j=0; j<v[i].size(); j++)
        {
            if(terminals.count(v[i][j]))
            {
                ok=true;
            }
            else if(ch!=v[i][j] and st.count(v[i][j])==0)
            {
                ok=anyTerminal(v[i][j]);
            }
            else if(ch==v[i][j]) {
                    ok=false;
                break;
            }
            else if(st.count(v[i][j])) return false;
        }
        if(ok) return true;
    }
    return false;
}

bool solve(char ch)   //A B
{
    vector<string>P=mp[ch];
    if(P.size()==0)
        return false;

    bool ok;
    for(int i=0; i<P.size(); i++)
    {
        string s=P[i];

        ok=false;
        for(int j=0; j<s.size(); j++)
        {
            if(variables.count(s[j]))
            {
                if(ch!=s[j])
                {
                    if(!solve(s[j]))
                    {
                        ok=false;
                        break;
                    }
                    else
                        ok=true;
                }
                else
                {
                    ok=anyTerminal(ch);
                    if(ok==false)
                       return false;
                }
            }
            else if(terminals.count(s[j]))
            {
                ok=true;
            }
        }
    }

    return ok;
}

void generating()
{
    for(auto it:mp)
    {
        vector<int>v;
        char ch=it.first;

        for(int i=0; i<it.second.size(); i++) // AB CA
        {
            bool ok=false;
            string s=it.second[i];

            for(int j=0; j<s.size(); j++)
            {
                if(generates.count(s[j])) ok=true;
                else if(variables.count(s[j]))
                {
                    if(ch!=s[j])
                    {
                        if(!solve(s[j]))
                        {
                            ok=false;
                            break;
                        }
                        else
                            ok=true;
                    }
                    else
                    {
                        st.insert(ch);
                        ok=anyTerminal(ch);
                        if(ok==false)
                            break;
                    }
                }
                else if(terminals.count(s[j]))
                {
                    ok=true;
                }
            }
            if(!ok)
            {
               // cout<<"$ "<<ch<<" "<<i<<"\n";
                v.push_back(i);
            }
        }

        auto it2=mp[ch].begin();
        for(int i=0; i<v.size(); i++)
        {
            it2=it2+v[i];
            mp[ch].erase(it2);
        }

        //if(mp[ch].size()) generates.insert(ch);
    }

}

bool check(char startSymbol,char ch)
{
    auto v=mp[startSymbol];

    for(int i=0; i<v.size(); i++)
    {
        for(int j=0; j<v[i].size(); j++)
        {
            if(ch==v[i][j])
            {
                return true;
            }
            else if(variables.count(v[i][j]) and startSymbol!=v[i][j])
                check(v[i][j],ch);
        }
    }
    return false;
}

void reachability(char startSymbol)
{
    for(auto it:mp)
    {
        char ch=it.first;
        if(ch!=startSymbol)
        {
            if(!check(startSymbol,ch))                          //A, s-B, b->C
            {
                mp[ch].clear();
            }
        }
    }
}


void print()
{
    for(auto it:mp)
    {
        if(it.second.size()!=0)
        {
            cout<<it.first<<" ->  ";
            for(int i=0; i<it.second.size(); i++)
            {
                cout<<it.second[i]<<" | ";
            }
            puts("");
        }
    }
}


int main()
{
    freopen("p3.txt","r",stdin);
    puts("enter the number of variables or non-terminals");
    cin>>numberOfVariable;

    puts("enter the variables");
    getchar();
    for(int i=0; i<numberOfVariable; i++)
    {
        char ch;
        cin>>ch;
        variables.insert(ch);
        getchar();
    }

    puts("enter the number of terminals");
    cin>>numberOfTerminal;

    puts("enter the terminals");
    getchar();
    for(int i=0; i<numberOfTerminal; i++)
    {
        char ch;
        cin>>ch;
        terminals.insert(ch);
        getchar();
    }

    puts("input the number of production");
    cin>>numberOfProduction;

    for(int i=0; i<numberOfProduction; i++)
    {
        char left;
        string right,s="";
        cin>>left;
        cin>>right;

        for(int j=0; j<right.size(); j++)
        {
            if(right[j]=='|')
            {
                mp[left].push_back(s);
                s.erase(s.begin(),s.end());
            }
            else
                s+=right[j];
        }

        mp[left].push_back(s);
    }

    puts("enter the start symbol");
    char startSymbol;
    cin>>startSymbol;

    puts("the given grammar");
    print();

    generating();
    puts("after removing non generating symbols");
    print();

    reachability(startSymbol);
    puts("after reachability test");
    print();
}
