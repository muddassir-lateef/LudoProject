#include<cstring>
#include<iostream>
using namespace std;
string strremove(char c,string& s)
{
    string x="";
    int n=s.length();
    bool rep=true;
    for(int i=0;i<n;i++)
    {
        if(c==s[i] && rep)
        {
            rep=false;
        }
        else
        {
            x+=s[i];
        }
    }
    return x;
}