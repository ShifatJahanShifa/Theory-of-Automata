/* eliminating unit production for any grammar ( generalised version ) */

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

void put(char ch,char ch1)
{
    auto v=mp[ch1];
    for(int i=0; i<v.size(); i++)
    {
        string s=v[i];
        if(s.size()==1)
        {
            char ch2=s[0];
            put(ch1,ch2);
        }
        else
        mp[ch].push_back(s);
    }
}

void eliminatingUnitProduction()
{
    for(auto it:mp)
    {
        char ch=it.first;
        auto v=mp[ch];

        for(int i=0; i<v.size(); i++)
        {
            string s=v[i];
            if(s.size()==1 and variables.count(s[0]))
            {
                char ch1=s[0];
                put(ch,ch1);
            }
        }
    }
}

void lastScaning()
{
    for(auto it:mp)
    {
        char ch=it.first;
        auto v=mp[ch];

        for(int i=0; i<v.size(); i++)
        {
            string s=v[i];
            if(s.size()==1 and variables.count(s[0]))
            {
                auto it1=mp[ch].begin()+i;
                mp[ch].erase(it1);
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
    freopen("p2.txt","r",stdin);
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

    puts("before eliminating unit production");
    print();

    eliminatingUnitProduction();
    lastScaning();
    puts("\n\nafter eliminating unit production");
    print();
}
