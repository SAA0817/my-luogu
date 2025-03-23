#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 6005
#define INF MAXN * 5

using namespace std;

int n;
int a[MAXN], b[MAXN], c[MAXN];
int f[MAXN*5], pre[MAXN*5];
char ch;

int min(int a, int b)
{
	return a > b ? b : a;
}

int read()
{
	int res = 0;
	ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		res *= 10;
		res += ch - '0';
		ch = getchar();
	}
	return res;
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		a[i] = read();
		b[i] = read();
		c[i] = read();
	}
	
	for(int i = 1; i <= n; i++)
	{
		//前i件商品，1号用时j，2号用时f[j]
		for(int j = i*5; j >= 0; j--)
		{
			int t = f[j];
			f[j] = INF;
			if(a[i] && j-a[i] >= 0) f[j] = f[j-a[i]];
			if(b[i] && f[j] > t+b[i]) f[j] = t+b[i];
			if(c[i] && j-c[i] >= 0 && f[j] > f[j-c[i]]+c[i]) f[j] = f[j-c[i]]+c[i];
			//cout << j << " " << f[j] << endl;
		}
		//cout << endl;
	}
	int ans = INF;
	for(int j = 1; j <= n*5; j++)
		ans = min(ans, max(j, f[j]));
	    
	cout << ans;
	return 0;
}
