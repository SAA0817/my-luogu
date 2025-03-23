#include<iostream>
#include<cstdio>
#include<map>
#define MAXN 50005

using namespace std;

map<string, string> q;
string name, f;

string getfa(string s)
{
	if(s == q[s]) return s;
	return q[s] = getfa(q[s]);
}

int main()
{
    char c = getchar();
	while(c != '$')
	{
		cin >> name;
		if(c == '#')
		{
			f = name;
			if(q[name] == "") q[name] = name;
		}
		if(c == '+') q[name] = f;
		if(c == '?') cout << name << " " << getfa(name) << endl;
		cin >> c;
	}
	return 0;
}

