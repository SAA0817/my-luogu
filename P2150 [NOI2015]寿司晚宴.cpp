#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define MAXN 505

using namespace std;

int n;
LL mod;
int p[11];
LL dp[MAXN][MAXN];
LL f1[MAXN][MAXN], f2[MAXN][MAXN];
LL ans;

struct Node{
	int big;
	int S;
}a[MAXN];

bool cmp(Node a, Node b)
{
	return a.big < b.big;
}

void init()
{
	p[1] = 2; p[2] = 3;
	p[3] = 5; p[4] = 7;
	p[5] = 11; p[6] = 13;
	p[7] = 17; p[8] = 19;
	for(int i = 2; i <= n; i++)
	{
		int t = i;
		for(int j = 8; j >= 1; j--)
		{
			a[i].S = a[i].S << 1;
			if(t % p[j] == 0)
		    {
		    	a[i].S += 1;
		    	while(t % p[j] == 0)
		    	    t = t / p[j];
		    }
		}
		if(t > 1) a[i].big = t;
	}
}

void copy()
{
	for(int i = 0; i <= 255; i++)
	    for(int j = 0; j <= 255; j++)
	    {
	    	f1[i][j] = dp[i][j];
	    	f2[i][j] = dp[i][j];
		}
}

int main()
{
	scanf("%d %lld", &n, &mod);
	init();
//	for(int i = 2; i <= n; i++)
//	    cout << a[i].S << " ";
	sort(a+2, a+n+1, cmp);
	dp[0][0] = 1;
	for(int i = 2; i <= n; i++)
	{
		//bool flag1, flag2;
		//先插big，big不变的话不插 
		//cout << a[i].big << " ";
		if(a[i].big != a[i-1].big || i == 2 || a[i].big == 0)   copy();
		//再插其他质因子 
		for(int j = 255; j >= 0; j--)
		    for(int k = 255; k >= 0; k--)
		    {
		    	//if(a[i].S & j && a[i].S & k) continue;
		    	if(j & k) continue;
		    	if(!(a[i].S & j))
		    	{
		    		//if(i == 4 && f1[j][k]) cout << (a[i].S|j) << " " << j << " " << k << endl;
					f2[j][a[i].S|k] += f2[j][k];
		    		f2[j][a[i].S|k] %= mod;
				}
				if(!(a[i].S & k))
				{
					//if(i == 4 && f2[j][k]) cout << (a[i].S|k) << " " << j << " " << k << endl;
					f1[a[i].S|j][k] += f1[j][k];
		    		f1[a[i].S|j][k] %= mod;
				}
		    }
		if(a[i].big != a[i+1].big || i == n || a[i].big == 0)
		    for(int j = 0; j <= 255; j++)
			    for(int k = 0; k <= 255; k++)
				{
					if(j & k) continue;
					dp[j][k] = (f1[j][k] + f2[j][k] + mod - dp[j][k]) % mod;
				}
				
//	for(int i = 0; i <= 255; i++)
//	    for(int j = 0; j <= 255; j++)
//	        if(!(i & j))
//	        {
//	        	//if(dp[i][j] != 0)cout << i <<" " << j <<" "<<dp[i][j]<<endl; 
//	        	ans += dp[i][j];
//				ans %= mod; 
//			}
//	cout << ans << endl;
//	ans = 0;
	}
	for(int i = 0; i <= 255; i++)
	    for(int j = 0; j <= 255; j++)
	        if(!(i & j))
	        {
	        	//if(dp[i][j] != 0)cout << i <<" " << j <<" "<<dp[i][j]<<endl; 
	        	ans += dp[i][j];
				ans %= mod; 
			}
	printf("%lld", ans);
	return 0;
}
