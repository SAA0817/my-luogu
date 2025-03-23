#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 10005
#define LL long long
using namespace std;


int n;
char s[MAXN];
int a[MAXN];
int base = 131;

int hash(char c[])
{
	int len = strlen(c);
	LL ans = 1;
	for(int i = 0; i < len; i++) ans = ans * base + (LL)s[i];
	return ans & 0x3ffffffff;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", &s);
		a[i] = hash(s);
	}
	sort(a+1, a+n+1);
	int cnt = 1;
	for(int i = 2; i <= n; i++)
	    if(a[i] != a[i-1])
	        cnt++;
	printf("%d\n", cnt);
	return 0;
}
