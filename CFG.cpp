/* context free grammar for unambiguous grammar specified in the grammar2.txt file */

#include<bits/stdc++.h>
using namespace std;

set<char>variables;
set<char>terminals;
map<char,vector<string>>productions;
vector<string>leftMostDerivation;
int p=0,q=0;

int main()
{
    /** input of a grammar G=(V,T,Start,P) **/

    freopen("grammar2.txt","r",stdin);

    puts("enter the variables set");
    string variable;
    getline(cin,variable);

    /** initializing the variables set **/
    for(int i=0; i<variable.size(); i++)
    {
        if(variable[i]!=' ')
            variables.insert(variable[i]);
    }

    puts("enter the terminals set");
    string terminal;
    getline(cin,terminal);

    /** initializing the terminals set **/
    for(int i=0; i<terminal.size(); i++)
    {
        if(terminal[i]!=' ')
            terminals.insert(terminal[i]);
    }

    puts("enter the root");
    char startSymbol;
    cin>>startSymbol;
    getchar();

    /** enter the production rule **/
    for (int i = 0; i<3; i++)
    {
        string production;
        getline(cin,production);
        int sizeOfP=production.size();
        string substring;
        int track=6;
        while(track+1!=sizeOfP)
        {
            for(int j=track+1; j<sizeOfP; j++)
            {
                track=j;
                if(production[j]=='|')
                    break;
                substring+=production[j];
            }

            productions[production[2]].push_back(substring);
            substring.clear();
        }
    }

    freopen("words2.txt","r",stdin);

    puts("enter a word");
    string word;
    cin>>word;
    cout<<"given word is "<<word<<"\n";

    auto v=productions[startSymbol];

    for(int i=0; i<v.size(); i++)
    {
        leftMostDerivation.push_back(v[i]);
    }

    bool outer=false;

    for(int i=0; i<word.size(); i++)
    {
        char ch=word[i];
        char ch1=leftMostDerivation[p][q];

        if(ch1==ch)
        {
            continue;
        }
        else
        {
            auto v=productions[ch1];
            bool ok=false;

            for(int j=0; j<v.size(); j++)
            {
                if(v[j][0]==ch)
                {
                    ok=true;
                    string temp;

                    for(int k=0; k<leftMostDerivation[p].size(); k++)
                    {
                        if(leftMostDerivation[p][k]==ch1)
                            break;

                        temp+=leftMostDerivation[p][k];
                    }

                    for(int k=0; k<v[j].size(); k++)
                    {
                        temp+=v[j][k];
                    }

                    for(int k=q+1; k<leftMostDerivation[p].size(); k++)
                    {
                        temp+=leftMostDerivation[p][k];
                    }

                    leftMostDerivation.push_back(temp);
                    p++,q++;
                }
            }

            if(!ok)
            {
                if(terminals.count(ch))
                {
                    string replc;
                    replc+=leftMostDerivation[p].substr(0,q);

                    for(int j=q+1; j<leftMostDerivation[p].size(); j++)
                        replc+=leftMostDerivation[p][j];

                    leftMostDerivation.push_back(replc);
                    p++,q++;
                }
                else if(variables.count(ch)==0)
                {
                    outer=true;
                    break;
                }
            }
        }
    }

    string last;

    if(outer==false and (word.size()+1==leftMostDerivation[leftMostDerivation.size()-1].size()))
    {
        int start=leftMostDerivation.size();
        int endi=leftMostDerivation[start-1].size();

        for(int i=0; i<endi-1; i++)
            last+=leftMostDerivation[start-1][i];

        leftMostDerivation.push_back(last);
    }
    else
    {
        int start=leftMostDerivation.size();
        int endi=leftMostDerivation[start-1].size();

        for(int i=0; i<endi-3; i++)
            last+=leftMostDerivation[start-1][i];

        for(int i=endi-2;i<endi;i++)
            last+=leftMostDerivation[start-1][i];

        leftMostDerivation.push_back(last);
    }

    (last==word) ? puts("Status: Accepted") : puts("Status: Not Accepted");

    puts("here is the leftmost derivation: ");

    cout<<startSymbol<<" => "<<leftMostDerivation[0]<<"\n";

    for(int i=1; i<leftMostDerivation.size(); i++)
        cout<<"  => "<<leftMostDerivation[i]<<"\n";

}
