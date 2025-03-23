#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<iostream>
#define LL long long
#define MAXN 105
#define INF 1000000005

using namespace std;

int n, s1, s2;
LL a[MAXN][3], b[MAXN][3];
int dp[1005 << 1][2];
int ans = INF;

LL read()
{
	LL res = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

void init()
{
	for(int i = 1; i <= s1 + s2; i++)
	{
		dp[i][1] = INF;
		dp[i][2] = INF;
	}
	dp[0][1] = 0;
	dp[0][2] = 0;
}

void pr()
{
	for(int i = 0; i <= s1 + s2; i++)
	{
		cout << i << " " << dp[i][1] << " " << dp[i][2] << endl;
	}
	cout << endl;
}

int main()
{
	n = read(); s1 = read(); s2 = read();
	init();
	
	for(int i = 1; i <= n; i++)
	{
		a[i][1] = read();
		a[i][2] = read();
		b[i][1] = read();
		b[i][2] = read();
	}
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = s1 + s2; j >= a[i][2]; j--)
			if(dp[j][1] > dp[j-a[i][2]][1] + a[i][1]) dp[j][1] = dp[j-a[i][2]][1] + a[i][1];
		pr();
	}
		
	for(int i = 1; i <= n; i++)
	{
		for(int j = s1 + s2; j >= b[i][2]; j--)
			if(dp[j][1] > dp[j-b[i][2]][2] + b[i][2]) dp[j][2] = dp[j-b[i][2]][2] + b[i][1];
		pr();
	}
		
	for(int i = s1; i <= s2 + s1; i++)
	    for(int j = s2 + s1 - i; j <= s2 + s1; j++)
	    {
	    	ans = min(ans, dp[i][1] + dp[j][2]);
		}
	cout << ans;
	return 0;
}
