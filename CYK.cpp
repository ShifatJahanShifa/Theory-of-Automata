#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define N 100
string table[N][N];
vector <pair<char,string>> production;
string input_string;

vector<string> get_curtesian_products(int i, int m, int n, int j){
    vector<string> prod;
    string a = table[i][m];
    string b = table[n][j];

    //null check
    if(a.length()==0 || b.length()==0)
        return prod;

    for(int i=0; i<a.length(); i++){
        for(int j=0; j<b.length(); j++){
            string temp_prod = "";
            temp_prod += a[i];
            temp_prod += b[j];
            prod.push_back(temp_prod);
        }
    }

    return prod;
}

set<char> find_prod(string str){
    set<char> t;
    for(int i=0; i<production.size(); i++){
        if(production[i].second == str){
            t.insert(production[i].first);
        }
    }
    return t;
}

void fill_table_index(int i, int j){
    vector <vector <string>> curtesian_products;
    for(int m=i; m<=j-1; m++){
       curtesian_products.push_back(get_curtesian_products(i,m,m+1,j));
    }

    //now take the acceptable products
    set<char> s;
    set<char> temp_s;
    for(int i=0; i<curtesian_products.size(); i++){
        for(int j=0; j<curtesian_products[i].size(); j++){
            string str = curtesian_products[i][j];
            temp_s = find_prod(str);
            for(auto itr: temp_s){
                s.insert(itr);
            }
        }
    }

    string temp_string = "";
    for(auto itr: s){
        temp_string += itr;
    }

    table[i][j] = temp_string;
}


void make_table(int n){
    // first make the base (eg. X11, X22, .... , Xnn)
    for(int i=1; i<=n; i++){
        string terminal = "";
        terminal += input_string[i-1];;
        string temp = "";
        for(int i=0; i<production.size(); i++){
            if(production[i].second == terminal){
                temp += production[i].first;
            }
        }
        table[i][i] = temp;
        temp.clear();
        terminal.clear();
    }

    // then others
    for(int i=2; i<=n; i++){
        int j = 1;
        for(int k=i; k<=n; k++){
            fill_table_index(j,k);
            j++;
        }
    }
}

void print_table(int n){
    cout<<"\nThe table is:\n";
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            string s = table[i][j];
            if(s.length() == 0)
                cout<<"null"<<" ";
            else
                cout<<s<<" ";
        }
        cout<<endl;
    }
}

void check_acceptance(char s, int n){
    string str = table[1][n];
    bool flag = false;
    for(int i=0; i<str.length(); i++){
        if(str[i] == s)
            flag = true;
    }

    if(flag)
        cout<<"\nAccepted!\n";
    else
        cout<<"\nRejected!\n";
}

int main(void){
    freopen("cyk.txt", "r", stdin);
    cout<<"Enter Productions in CNF(enter xxx to stop): \n";
    string str;
    cin>>str;
    while(str != "xxx"){
        char left = str[0];
        string temp_str;
        for(int i=2; i<str.length(); i++){
            if(str[i]=='|'){
                production.push_back(make_pair(left,temp_str));
                temp_str.clear();
            }
            else
                temp_str += str[i];
        }
        production.push_back(make_pair(left,temp_str));
        temp_str.clear();

        cin>>str;
    }

//print productions
    // for(int i=0; i<production.size(); i++){
    //     cout<<production[i].first<< "  "<<production[i].second<<endl;
    // }

    cout<<"\nEnter input string: ";
    cin>>input_string;
    int n = input_string.length();

    make_table(n);

    // all is okay just table valo vabe print korte hobe
    print_table(n);

    char start = production[0].first;
    check_acceptance(start, n);

    return 0;
}