#include<cstdio>
#include<iostream>
#define mid ((l + r) / 2)
#define MAXN 100005

using namespace std;

int n, ans = 1;
int t[MAXN], b[MAXN], dp[MAXN];
char c;

int read()
{
	int res = 0;
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

int in(int num, int l, int r)
{
	if(l == r) return mid;
	if(num < dp[mid]) return in(num, l, mid);
	return in(num, mid+1, r);
}

int main()
{
	//freopen("testdata.in", "r", stdin);
	n = read();
	for(int i = 1; i <= n; i++)
	{
		int tmp = read();
		t[tmp] = i;
	}
	for(int i = 1; i <= n; i++)
	    b[i] = t[read()];
	for(int i = 1; i <= n; i++)
	    dp[i] = n+1;
	    
//	for(int i = 1; i <= n; i++)
//	    cout << b[i] << " ";
//	cout << endl;
	dp[1] = b[1];
	for(int i = 2; i <= n; i++)
	{
		if(b[i] > dp[ans])
		{
			ans++;
			dp[ans] = b[i];
			continue;
		}
		int t = in(b[i], 1, ans);
		dp[t] = min(dp[t], b[i]);
	}
//	for(int i = 1; i <= ans; i++)
//	    cout << dp[i] << " ";
//	cout << endl;
	cout << ans << endl;
	return 0;
}
