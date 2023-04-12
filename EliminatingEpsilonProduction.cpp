#include<bits/stdc++.h>
using namespace std;

map<char,set<string>>result;
map<char,vector<string>>mp;
set<char>st;
int numberOfProduction;
set<string>take;
set<string>terminals;

void getString(string s,char j,char ch,int id)
{
    string res;
    cout<<s<<"rt\n";
    int mark;
    cout<<j<<"\n";
    cout<<s.size();
    int cnt=0;
    while(1)
    {
        mark=1;
        cnt++;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]==j and mark==1 and id==i)
            {
                puts("ht");
                mark=0;
                // continue;
            }
            else
            {
                cout<<s[i]<<"\n";
                res+=s[i];
                cout<<res<<"\n";
            }
        }
        cout<<res<<"&&\n";

        if(res!="")
            result[ch].insert(res);
        if(res==s)
            break;
        s.clear();
        s.assign(res);

        cout<<"* "<<s<<" *"<<res<<"\n";

        if(terminals.count(res))
            break;

        res.clear();

    }
}

void eliminatingEpsilon()
{
    for(auto it:mp)
    {
        char ch=it.first;
        cout<<"here "<<ch<<"\n";

        auto v=mp[ch];
        for(int i=0; i<v.size(); i++)
        {
            if(v[i]!="$")
                result[ch].insert(v[i]);
            for(int j=0; j<v[i].size(); j++) // a-> AAB
            {
                if(st.count(v[i][j]))
                {
                    getString(v[i],v[i][j],ch,j);
                }
            }
            for(auto it1=result[ch].begin(); it1!=result[ch].end(); it1++)
            {
                string f=*it1;
                for(int j=0; j<f.size(); j++) // a-> AAB
                {
                    if(st.count(f[j]))
                    {
                        getString(f,f[j],ch,j);
                    }
                }

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

void printR()
{
    for(auto it:mp)
    {
        if(it.second.size()!=0)
        {
            cout<<it.first<<" ->  ";
            char ch=it.first;
            for(auto it1=result[ch].begin(); it1!=result[ch].end(); it1++)
            {
                cout<<*it1<<" | ";
            }
            puts("");
        }
    }
}

int main()
{
    freopen("a11.txt","r",stdin);

    puts("input the number of production");
    cin>>numberOfProduction;

    terminals.insert("a");
    terminals.insert("b");
    terminals.insert("");

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
                s.clear();
            }
            else
            {
                s+=right[j];
                if(right[j]=='$')
                {
                    st.insert(left);
                }
            }
        }

        mp[left].push_back(s);
    }

    puts("the given grammar");
    print();

    //cout<<st.size();
    eliminatingEpsilon();

    puts("after removing nullable symbols");
    printR();
}
