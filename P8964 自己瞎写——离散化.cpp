#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 100005

using namespace std;

int n;
int v[MAXN];
int rank[MAXN];
int p[MAXN];

int read()
{
	char c = getchar();
	int res = 0;
	int f = 1;
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

bool cmp(int a, int b)
{
	return v[a] < v[b];
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		v[i] = read();
		p[i] = i;
	}
	sort(p+1, p+n+1, cmp);
	for(int i = 1; i <= n; i++)
	    rank[p[i]] = i;
	for(int i = 1; i <= n; i++)
	    printf("%d ", rank[i]);
	return 0;
}
