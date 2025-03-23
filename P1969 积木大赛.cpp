#include<cstdio>
#include<iostream>
#define MAXN 100005
#define LL long long

using namespace std;

int h[MAXN], n;
LL ans, m;
char c;

LL read()
{
	LL res = 0;
	c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	    h[i] = read();
	for(int i = 1; i <= n; i++)
	{
		if(m >= h[i])
		{
			m = h[i];
			continue;
		}
		ans += h[i] - m;
		m = h[i];
	}
	cout << ans;
	return 0;
}
